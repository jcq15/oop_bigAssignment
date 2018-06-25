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
	virtual void Rely(std::set<std::string>&)=0;//依赖的输入节点 
	std::string PrintRely();
	virtual Tensor eval(std::map<std::string,Tensor>&)=0;//求值 
	virtual void Release()=0;//释放保存的值 
	Tensor Eval(std::map<std::string,Tensor>&);//使用map 
	Tensor Eval(const std::initializer_list<std::pair<std::string,Tensor>>&);//使用初始化列表 
};
#endif
