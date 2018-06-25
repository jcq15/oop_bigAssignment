#ifndef CONSTANT
#include "Node.h"
#define CONSTANT
class Constant:public Node
{
private:
	Tensor eval(std::map<std::string,Tensor>&); 
	void Release(){} 
public:
	Constant(const Tensor& _t,const std::string& _nm=""):Node(_nm,new Tensor(_t)){}
	std::string Expr()
	{
		return std::string("Constant(")+name+")";
	}
	void Rely(std::set<std::string>& lib){}
};



#endif
