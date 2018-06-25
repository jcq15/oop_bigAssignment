#ifndef PLACEHOLDER
#include "Node.h"
#define PLACEHOLDER

class Placeholder:public Node
{
private:
	int n,m;
	bool ismat;
	Tensor eval(std::map<std::string,Tensor>&);
	
	void Release()
	{
		if(value!=nullptr)
		{
			delete value;
			value=nullptr;
		}
	}
public:
	Placeholder(const std::string& _nm):Node(_nm),n(0),m(0),ismat(false){}
	Placeholder(const int& _n,const int& _m,const std::string& _nm):Node(_nm),n(_n),m(_m),ismat(true){}
	void Rely(std::set<std::string>& lib);
	std::string Expr(){return name;}
	std::string PrintType()const;
	

//	using Node::Eval;
};


#endif
