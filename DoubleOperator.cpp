#include "DoubleOperator.h" 
#include "Constant.h"
#include "SingleOperator.h"

void DoubleOperator::Release() {
    a->Release();
    b->Release();
    if (value != nullptr) {
        delete value;
        value = nullptr;
    }
}

void Add::Judge(const Tensor& A, const Tensor& B)const {
    if (A.Type() != B.Type() || (A.Type() && (A.N() != B.N() || A.M() != B.M())))
        throw std::invalid_argument("Error : Add node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Add::eval(std::map<std::string, Tensor>& Inputs) {
    if (value == nullptr) {
        Tensor A = a->eval(Inputs);
        Tensor B = b->eval(Inputs);
        Judge(A, B);
        value = new Tensor(A + B);
        if (debug) {
            std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
            std::cout << value->Print() << '\n';
        }
    }
    return *value;
}

//Sub
void Sub::Judge(const Tensor& A, const Tensor& B) const{
    if (A.Type() != B.Type() || (A.Type() && (A.N() != B.N() || A.M() != B.M())))
        throw std::invalid_argument("Error : Sub node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Sub::eval(std::map<std::string, Tensor>& Inputs) {
    if (value == nullptr) {
        Tensor A = a->eval(Inputs);
        Tensor B = b->eval(Inputs);
        Judge(A, B);
        value = new Tensor(A - B);
        if (debug) {
            std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
            std::cout << value->Print() << '\n';
        }
    }
    return *value;
}

//Mul
void Mul::Judge(const Tensor& A, const Tensor& B) const{
    if (A.Type() && B.Type() && A.M() != B.N())
        throw std::invalid_argument("Error : Mul node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Mul::eval(std::map<std::string, Tensor>& Inputs) {
    if (value == nullptr) {
        Tensor A = a->eval(Inputs);
        Tensor B = b->eval(Inputs);
        Judge(A, B);
        value = new Tensor(A*B);
        if (debug) {
            std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
            std::cout << value->Print() << '\n';
        }
    }
    return *value;
}

//Div
void Div::Judge(const Tensor& A, const Tensor& B) const{
    if (B.Type())
        throw std::invalid_argument("Error : Div node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Div::eval(std::map<std::string, Tensor>& Inputs) {
    if (value == nullptr) {
        Tensor A = a->eval(Inputs);
        Tensor B = b->eval(Inputs);
        Judge(A, B);
        value = new Tensor(A / B);
        if (debug) {
            std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
            std::cout << value->Print() << '\n';
        }
    }
    return *value;
}

//Pow
void Pow::Judge(const Tensor& A, const Tensor& B) const{
    if (B.Type())
        throw std::invalid_argument("Error : Pow node \"" + name + "\" try to get value from " + a->Name() + "(" + A.PrintType() + ") and " + b->Name() + "(" + B.PrintType() + ") !");
}

Tensor Pow::eval(std::map<std::string, Tensor>& Inputs) {
    if (value == nullptr) {
        Tensor A = a->eval(Inputs);
        Tensor B = b->eval(Inputs);
        Judge(A, B);
        value = new Tensor(pow(A, B));
        if (debug) {
            std::cout << "Print Operator:" << name << "(" << value->PrintType() << ")=" << Expr() << '\n';
            std::cout << value->Print() << '\n';
        }
    }
    return *value;
}

/**第二阶段新增**/

Node& Add::derive(int index) {
    if (index != 1 && index != 2)
        throw std::invalid_argument("Error : derive argument error! Accept 1 or 2! ");
    Constant* ans = new Constant(1);
    return *ans;
}

Node& Sub::derive(int index) {
    Constant* ans;
    if (index == 1) {
        ans = new Constant(1);
    }
    else if (index == 2) {
        ans = new Constant(-1);
    }
    else {
        throw std::invalid_argument("Error : derive argument error! Accept 1 or 2! ");
    }
    return *ans;
}

Node& Mul::derive(int index) {
    if (index == 1) {
        return *b;
    }
    else if (index == 2) {
        return *a;
    }
    else {
        throw std::invalid_argument("Error : derive argument error! Accept 1 or 2! ");
    }
}

Node& Div::derive(int index) {
    if (index == 1) {
        Div* ans = new Div(*(new Constant(1)), *b);
        return *b;
    }
    else if (index == 2) {
        Pow* ans1 = new Pow(*b, *(new Constant(-2)));
        Mul* ans2 = new Mul(*a, *ans1);
        return *ans2;
    }
    else {
        throw std::invalid_argument("Error : derive argument error! Accept 1 or 2! ");
    }
}

Node& Pow::derive(int index) {
    if (index == 1) {
        Pow* ans1 = new Pow(*a, *b - *new Constant(1));
        Mul* ans2 = new Mul(*ans1, *b);
        return *ans2;
    }
    else if (index == 2) {
        //if(*a>0)
        Mul* ans = new Mul(*this, *new Ln(*a));
        return *ans;
    }
    else {
        throw std::invalid_argument("Error : derive argument error! Accept 1 or 2! ");
    }
}