#ifndef DOUBLEOPERATOR
#include "Node.h"
#define DOUBLEOPERATOR  
class Add:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&)const; 
	Tensor eval(std::map<std::string,Tensor>&);
	void Release(); 
public:
	Add(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Add(const Add &t)=default;
	
	Add(Add &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"+"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	
};

class Sub:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor& ,const Tensor& );
	Tensor eval(std::map<std::string,Tensor>&);
	void Release();
public:
	Sub(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Sub(const Sub &t)=default;
	
	Sub(Sub &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()	
	{
		return "("+a->Expr()+"-"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
	
};

class Mul:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor& ,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>&);
	void Release();
public:
	Mul(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	Mul(const Mul &t)=default;
	Mul(Mul &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"*"+b->Expr()+")";
	}
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};
class Div:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>& Inputs);
	void Release();
public:
	Div(Node &_a,Node &_b,const std::string& _nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Div(const Div &t)=default;
	
	Div(Div &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"/"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

class Pow:public Node
{
private:
	Node *a,*b;
	void Judge(const Tensor&,const Tensor&);
	Tensor eval(std::map<std::string,Tensor>&);
	void Release();
public:
	Pow(Node &_a,Node &_b,const std::string &_nm=""):Node(_nm),a(&_a),b(&_b){}
	
	Pow(const Pow &t)=default;
	
	Pow(Pow &&t):Node(t.name,t.value)
	{
		a=t.a;b=t.b;
		debug=t.debug;
		t.a=t.b=nullptr;
		t.value=nullptr;
	}
	
	std::string Expr()
	{
		return "("+a->Expr()+"^"+b->Expr()+")";
	}
	
	void Rely(std::set<std::string>& lib)
	{
		a->Rely(lib);
		b->Rely(lib);
	}
};

inline Add& operator +(Node& A,Node& B)
{
	Add* tmp=new Add(A,B);
	return *tmp;
} 

inline Sub& operator -(Node& A,Node& B)
{
	Sub* tmp=new Sub(A,B);
	return *tmp;
}

inline Mul& operator *(Node& A,Node& B)
{
	Mul* tmp=new Mul(A,B);
	return *tmp;
}

inline Div& operator /(Node& A,Node& B)
{
	Div* tmp=new Div(A,B);
	return *tmp;
}

inline Pow& operator ^(Node& A,Node& B)
{
	Pow* tmp=new Pow(A,B);
	return *tmp;
}
#endif
