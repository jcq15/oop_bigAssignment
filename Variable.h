#ifndef VARIABLE
#include "Node.h"
#define VARIABLE
class Variable:public Node
{
private:
	Tensor eval(std::map<std::string,Tensor>&);
	void Release(){}
public:
	Variable(const Tensor& _t,const std::string& _nm=""):Node(_nm,new Tensor(_t)){}
	Variable(const std::string& _nm=""):Node(_nm,new Tensor()){}
	Variable(const int& n,const int& m,const std::string& _nm=""):Node(_nm,new Tensor(n,m)){}
	
	std::string Expr()
	{
		return std::string("Variable(")+name+")";
	}
	
	void Rely(std::set<std::string>& lib){}
	void Set(const Tensor& t);
	void Add(const Tensor& t);
	void Sub(const Tensor& t);
	void Mul(const Tensor& t);
	void Div(const Tensor &t);
	Variable& operator +=(const Tensor &t){Add(t);return *this;}
	Variable& operator -=(const Tensor &t){Sub(t);return *this;}
	Variable& operator *=(const Tensor &t){Mul(t);return *this;}
	Variable& operator /=(const Tensor &t){Div(t);return *this;}
	
	Tensor Value(){return *value;}
};

#endif
