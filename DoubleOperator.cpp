#include "DoubleOperator.h" 
void Add::Judge(const Tensor& A,const Tensor& B)const
{
	if(A.Type()!=B.Type()||(A.Type()&&(A.N()!=B.N()||A.M()!=B.M())))
		throw std::invalid_argument("Error : Add node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Add::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A+B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Add::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Sub
void Sub::Judge(const Tensor& A,const Tensor& B) 
{
	if(A.Type()!=B.Type()||(A.Type()&&(A.N()!=B.N()||A.M()!=B.M())))
		throw std::invalid_argument("Error : Sub node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Sub::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A-B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}		
	}
	return *value;
}

void Sub::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Mul
void Mul::Judge(const Tensor& A,const Tensor& B) 
{
	if(A.Type()&&B.Type()&&A.M()!=B.N())
		throw std::invalid_argument("Error : Mul node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Mul::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A*B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Mul::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
//Div
void Div::Judge(const Tensor& A,const Tensor& B) 
{
	if(B.Type())
		throw std::invalid_argument("Error : Div node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Div::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A/B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Div::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
//Pow
void Pow::Judge(const Tensor& A,const Tensor& B) 
{
	if(B.Type())
		throw std::invalid_argument("Error : Pow node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Pow::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(pow(A,B));
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Pow::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
