#include "Constant.h"

Tensor Constant::eval(std::map<std::string,Tensor>&Inputs) {
	if(debug)
	{
		std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
		std::cout<<value->Print()<<'\n';
	}	
	return *value;
}

