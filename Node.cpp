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

/**第二阶段新增**/

Node& Node::derive(int index) {
    throw std::logic_error("Error : Cannot derive a node which has no input!");
}
//求梯度的辅助函数1，用于往map里塞东西
void addMap(std::map<Node*, Node*>*m, Node* hot, Node* hot_temp, int index) {
    auto it = m->find(hot);             //看看有没有
    if (it == m->end()) {               //要是没有
        Node* temp = new Mul(*(*m)[hot_temp], hot_temp->derive(index));
        m->insert(std::pair<Node*, Node*>(hot, temp));
        //我就把你嘿嘿嘿
    }
    else {                              //要是有
        Node* temp = new Add(*it->first, *(it->second) * hot_temp->derive(index));
        it->second = temp;
        //我还要把你嘿嘿嘿
    }
}
//求梯度的辅助函数2，用于递归
void grader(std::map<Node*, Node*>*gradient, Node* hot) {
    if (hot->depend() == 0) return;         //递归基
    if (hot->depend() == 1) {
        SingleOperator* hot_temp = dynamic_cast<SingleOperator*>(hot);
        hot = hot_temp->getA();             //孩子
        addMap(gradient, hot, hot_temp, 1);    //塞进去
        grader(gradient, hot);              //递归
        return;
    }
    if (hot->depend() == 2) {
        DoubleOperator* hot_temp = dynamic_cast<DoubleOperator*>(hot);
        hot = hot_temp->getA();             //左孩子
        addMap(gradient, hot, hot_temp, 1);    //塞进去
        grader(gradient, hot);
        hot = hot_temp->getB();             //右孩子
        addMap(gradient, hot, hot_temp, 2);    //塞进去
        grader(gradient, hot);
        return;
    }
}
std::map<Node*, Node*>& Node::grad() {
    Node* hot = this;   //当前正在计算的节点
    auto gradient = new std::map<Node*, Node*>({ { this,new Constant(1) } });     //对自己的导数是常数1
    grader(gradient, hot);      //开始递归
    return *gradient;
}
