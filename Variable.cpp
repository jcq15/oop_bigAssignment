#include "Variable.h" 

Tensor Variable::eval(std::map<std::string,Tensor>&Inputs)
{
	if(debug)
	{
		std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
		std::cout<<value->Print()<<'\n';
	}	
	return *value;
}

void Variable::Set(const Tensor& t)
{
	if(t.Type()!=value->Type()||(t.Type()&&(t.N()!=value->N()||t.M()!=value->M())))
		throw std::invalid_argument("Error : Try to set a variable(" +value->PrintType()+") with Tensor("+t.PrintType()+")!");
	(*value)=t;
}

void Variable::Add(const Tensor& t)
{
	if(t.Type()!=value->Type()||(t.Type()&&(t.N()!=value->N()||t.M()!=value->M())))
		throw std::invalid_argument("Error : Try to Add a variable(" +value->PrintType()+") with Tensor("+t.PrintType()+")!");
	(*value)+=t;
}

void Variable::Sub(const Tensor& t)
{
	if(t.Type()!=value->Type()||(t.Type()&&(t.N()!=value->N()||t.M()!=value->M())))
		throw std::invalid_argument("Error : Try to Sub a variable(" +value->PrintType()+") with Tensor("+t.PrintType()+")!");
	(*value)-=t;
}

void Variable::Mul(const Tensor& t)
{
	if((!value->Type()&&t.Type())||(t.Type()&&(t.N()!=t.M()||t.N()!=value->M())))
		throw std::invalid_argument("Error : Try to Mul a variable(" +value->PrintType()+") with Tensor("+t.PrintType()+")!");
	(*value)*=t;
}

void Variable::Div(const Tensor &t)
{
	if(t.Type())
		throw std::invalid_argument("Error : Try to Div a variable(" +value->PrintType()+") with Tensor("+t.PrintType()+")!");
	(*value)/=t;
}
