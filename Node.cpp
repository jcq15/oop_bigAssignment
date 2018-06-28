#include "Node.h" 
#include "Constant.h"
#include "SingleOperator.h"
#include "DoubleOperator.h"

std::string Node::PrintRely()
{
	std::string ans=name+" rely on:\n";
	std::set<std::string> lib;
	lib.clear();
	Rely(lib);
	if(lib.empty())ans+="\tNOTHING\n";
	for(auto it=lib.cbegin();it!=lib.cend();it++) 
		ans+="\t"+*it+"\n";
	return ans;
}

Tensor Node::Eval(std::map<std::string,Tensor>&Inputs)
{
	Tensor ans=eval(Inputs);
	Release();
	return ans;
}

Tensor Node::Eval(const std::initializer_list<std::pair<std::string,Tensor>>& il)
{
	std::map<std::string,Tensor> Inputs;
	for(auto it=il.begin();it!=il.end();it++)
	{
		if(Inputs.find(it->first)!=Inputs.end())
			throw std::invalid_argument("Error : Redeclaration in inputs!");
		Inputs[it->first]=it->second;
	}
	return Eval(Inputs);
}

/**�ڶ��׶�����**/

Node& Node::derive(int index) {
    throw std::logic_error("Error : Cannot derive a node which has no input!");
}
//���ݶȵĸ�������1��������map��������
void addMap(std::map<Node*, Node*>*m, Node* hot, Node* hot_temp, int index) {
    auto it = m->find(hot);             //������û��
    if (it == m->end()) {               //Ҫ��û��
        Node* temp = new Mul(*(*m)[hot_temp], hot_temp->derive(index));
        m->insert(std::pair<Node*, Node*>(hot, temp));
        //�ҾͰ���ٺٺ�
    }
    else {                              //Ҫ����
        Node* temp = new Add(*it->first, *(it->second) * hot_temp->derive(index));
        it->second = temp;
        //�һ�Ҫ����ٺٺ�
    }
}
//���ݶȵĸ�������2�����ڵݹ�
void grader(std::map<Node*, Node*>*gradient, Node* hot) {
    if (hot->depend() == 0) return;         //�ݹ��
    if (hot->depend() == 1) {
        SingleOperator* hot_temp = dynamic_cast<SingleOperator*>(hot);
        hot = hot_temp->getA();             //����
        addMap(gradient, hot, hot_temp, 1);    //����ȥ
        grader(gradient, hot);              //�ݹ�
        return;
    }
    if (hot->depend() == 2) {
        DoubleOperator* hot_temp = dynamic_cast<DoubleOperator*>(hot);
        hot = hot_temp->getA();             //����
        addMap(gradient, hot, hot_temp, 1);    //����ȥ
        grader(gradient, hot);
        hot = hot_temp->getB();             //�Һ���
        addMap(gradient, hot, hot_temp, 2);    //����ȥ
        grader(gradient, hot);
        return;
    }
}
std::map<Node*, Node*>& Node::grad() {
    Node* hot = this;   //��ǰ���ڼ���Ľڵ�
    auto gradient = new std::map<Node*, Node*>({ { this,new Constant(1) } });     //���Լ��ĵ����ǳ���1
    grader(gradient, hot);      //��ʼ�ݹ�
    return *gradient;
}
