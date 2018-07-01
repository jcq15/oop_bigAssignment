#ifndef SINGLEOPERATOR
#include "Node.h"
#define SINGLEOPERATOR
class SingleOperator :public Node {
protected:
    Node *a;
    virtual Tensor* calc(const Tensor&) = 0;
    Tensor eval(std::map<std::string, Tensor>&);
    void Release() {
        a->Release();
        if (value != nullptr) {
            delete value;
            value = nullptr;
        }
    }
public:
    SingleOperator(const std::string& _nm, Node &_a) :Node(_nm), a(&_a) {
        depends = 1;
    }
    void Rely(std::set<std::string>& lib) { a->Rely(lib); }
    Node* getA() const { return a; }
};

class Exp :public SingleOperator {
private:
    Tensor* calc(const Tensor& A) { return new Tensor(exp(A)); }
public:
    Exp(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "exp(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Ln :public SingleOperator {
private:
    Tensor* calc(const Tensor& A) { return new Tensor(ln(A)); }
public:
    Ln(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "ln(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Sin :public SingleOperator {
private:
    Tensor* calc(const Tensor& A) { return new Tensor(sin(A)); }
public:
    Sin(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "sin(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Cos :public SingleOperator {
private:
    Tensor* calc(const Tensor& A) { return new Tensor(cos(A)); }
public:
    Cos(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "cos(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Tan :public SingleOperator {
private:
    Tensor* calc(const Tensor& A) { return new Tensor(tan(A)); }
public:
    Tan(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "tan(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Asin :public SingleOperator {
private:
    Tensor* calc(const Tensor& A) { return new Tensor(asin(A)); }
public:
    Asin(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "asin(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Acos :public SingleOperator {
private:
    Tensor* calc(const Tensor& A) { return new Tensor(acos(A)); }
public:
    Acos(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "acos(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Atan :public SingleOperator {
private:
    Tensor* calc(const Tensor& A) { return new Tensor(atan(A)); }
public:
    Atan(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "atan(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Quadratic :public SingleOperator {
private:
    Tensor* calc(const Tensor& A);
public:
    Quadratic(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "Quadratic_Cost(" + a->Expr() + ")";
    }
};

class Sigmoid :public SingleOperator {
private:
    Tensor* calc(const Tensor& A);
public:
    Sigmoid(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {}

    std::string Expr() {
        return "Sigmoid(" + a->Expr() + ")";
    }
};

class Transpose :public SingleOperator {
private:
    Tensor* calc(const Tensor& A);
public:
    Transpose(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {
        prop = false;
    }

    std::string Expr() {
        return "(" + a->Expr() + ")^T";
    }

    //Node& Transpose::derive(int index) override;
};

class PowC :public SingleOperator {
private:
    double c;
    Tensor* calc(const Tensor& A)override { return new Tensor(pow(A, c)); }
public:
    PowC(Node &_a, double _c, const std::string& _nm = "") :SingleOperator(_nm, _a), c(_c) {}

    double C() { return c; }

    std::string Expr() {
        std::string pc = std::to_string(c);
        return "(" + a->Expr() + "^" + pc + ")";
    }

    Node& derive(int index) override;
};

class Assert: public SingleOperator{
private:
    Tensor* calc(const Tensor& A);
public:
    Assert(Node &_a, const std::string& _nm = "") :SingleOperator(_nm, _a) {
        prop = false;    //cannot derive it
    }
    std::string Expr() {
        return "assert(" + a->Expr() + ")";
    }

    Node& derive(int index) override;
};

/**µÚ¶þ½×¶ÎÐÂÔö**/

#endif
