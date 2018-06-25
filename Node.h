#ifndef NODE
#include <string>
#include <map>
#include <set>
#include "Tensor.h"
#define NODE

class Node
{
protected:
	bool debug;
	std::string name;
	Tensor* value;
public:
	Node(const std::string& _name,Tensor* _t=nullptr):debug(false),name(_name),value(_t){}
	
	Node(const Node& t):debug(t.debug),name(t.name),value(nullptr)
	{
		if(t.value!=nullptr)
			value=new Tensor(*(t.value));
	}
	
	Node(Node&& t):debug(t.debug),name(t.name),value(t.value)
	{
		t.value=nullptr;
	}
	
	~Node()
	{
		if(value!=nullptr)delete value;
	}
	
	void Debug()
	{
		debug=true;
	}
	
	void NDebug()
	{
		debug=false;
	}
	
	std::string Name(){return name;}
	
	std::string PrintExpr()
	{
		return name+" = "+Expr()+"\n";
	}
	
	virtual std::string Expr()=0;
	virtual void Rely(std::set<std::string>&)=0;//����������ڵ� 
	std::string PrintRely();
	virtual Tensor eval(std::map<std::string,Tensor>&)=0;//��ֵ 
	virtual void Release()=0;//�ͷű����ֵ 
	Tensor Eval(std::map<std::string,Tensor>&);//ʹ��map 
	Tensor Eval(const std::initializer_list<std::pair<std::string,Tensor>>&);//ʹ�ó�ʼ���б� 
};
#endif
