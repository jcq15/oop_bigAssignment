#include "Placeholder.h" 

Tensor Placeholder::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		if(Inputs.find(name)==Inputs.end())
			throw std::domain_error("Error : Your inputs lack of the value of "+name);
		if(Inputs[name].Type()!=ismat||(ismat&&(Inputs[name].N()!=n||Inputs[name].M()!=m)))
			throw std::invalid_argument("Error : Try to input"+Inputs[name].PrintType()+" to Placeholder("+PrintType()+")!");
		value=new Tensor(Inputs[name]);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Placeholder::Rely(std::set<std::string>& lib)
{
	std::string ans="";
	if(ismat)
		ans=name+"(Matrix"+std::to_string(n)+"*"+std::to_string(m)+")";
	else
		ans=name+"(Number)";
	lib.insert(ans);
}

std::string Placeholder::PrintType()const
{
	if(ismat)
		return "Matrix("+std::to_string(n)+"*"+std::to_string(m)+")";
	else 
		return "Number";
}
