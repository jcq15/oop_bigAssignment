#include "SingleOperator.h" 
#include "DoubleOperator.h"
#include "Constant.h"

Tensor SingleOperator::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		value=calc(A);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

Tensor* Quadratic::calc(const Tensor& A)
{
	if(!(A.Type()))
		throw std::invalid_argument("Error : Quadratic_Cost node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") !");
	return new Tensor(A.Quadratic_Cost());
}

Tensor* Sigmoid::calc(const Tensor& A)
{
	Tensor *tmp=new Tensor(A);
	tmp->Sigmoid();
	return tmp;
}

Tensor* Transpose::calc(const Tensor& A)
{
	if(!A.Type())
		throw std::invalid_argument("Error : Transpose node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") !");
	Tensor *tmp=new Tensor(A.M(),A.N());
	tmp->Transpose(A);
	return tmp;
}

/**第二阶段新增**/
Node& Exp::derive(int index) {
    if(index != 1) 
        throw std::invalid_argument("Error : derive argument error! Only accept 1! ");
    Exp* ans = new Exp(*a);
    return *ans;
}

Node& Ln::derive(int index) {
    if (index != 1)
        throw std::invalid_argument("Error : derive argument error! Only accept 1! ");
    Pow* ans = new Pow(*a, *new Constant(-1));
    return *ans;
}

Node& Sin::derive(int index) {
    if (index != 1)
        throw std::invalid_argument("Error : derive argument error! Only accept 1! ");
    Cos* ans = new Cos(*a);
    return *ans;
}

Node& Cos::derive(int index) {
    if (index != 1)
        throw std::invalid_argument("Error : derive argument error! Only accept 1! ");
    Sin* ans = new Sin((*a)*(*new Constant(-1)));
    return *ans;
}

Node& Tan::derive(int index) {
    if (index != 1)
        throw std::invalid_argument("Error : derive argument error! Only accept 1! ");
    Cos* ans = new Cos(*a);
    Pow* ans2 = new Pow(*ans, *new Constant(-2));
    return *ans2;
}

Node& Asin::derive(int index) {
    if (index != 1)
        throw std::invalid_argument("Error : derive argument error! Only accept 1! ");
    Cos* ans = new Cos(*this);
    Pow* ans2 = new Pow(*ans, *new Constant(-1));
    return *ans2;
}

Node& Acos::derive(int index) {
    if (index != 1)
        throw std::invalid_argument("Error : derive argument error! Only accept 1! ");
    Sin* ans = new Sin(*this * *new Constant(-1));
    Pow* ans2 = new Pow(*ans, *new Constant(-1));
    return *ans2;
}

Node& Atan::derive(int index) {
    if (index != 1)
        throw std::invalid_argument("Error : derive argument error! Only accept 1! ");
    Pow* ans = new Pow(*a, *new Constant(2));
    Add* ans1 = new Add(*ans, *new Constant(1));
    Pow* ans2 = new Pow(*ans1, *new Constant(-1));
    return *ans2;
}