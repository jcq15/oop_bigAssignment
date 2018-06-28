#ifndef DOUBLEOPERATOR
#include "Node.h"
#define DOUBLEOPERATOR  

class DoubleOperator :public Node {
protected:
    Node *a, *b;
    virtual void Judge(const Tensor&, const Tensor&) const = 0;
    virtual Tensor eval(std::map<std::string, Tensor>&) = 0;
    void Release();
public:
    DoubleOperator(Node &_a, Node &_b, const std::string& _nm = "")
        :Node(_nm), a(&_a), b(&_b) {
        depends = 2;
    }
    DoubleOperator(const DoubleOperator &t) = default;
    DoubleOperator(DoubleOperator &&t) :Node(t.name, t.value) {
        a = t.a;b = t.b;
        debug = t.debug;
        t.a = t.b = nullptr;
        t.value = nullptr;
        depends = 2;
    }
    void Rely(std::set<std::string>& lib) {
        a->Rely(lib);
        b->Rely(lib);
    }

    Node* getA() const { return a; }
    Node* getB() const { return b; }
};

class Add :public DoubleOperator {
private:
    void Judge(const Tensor&, const Tensor&) const override;
    Tensor eval(std::map<std::string, Tensor>&) override;
public:
    Add(Node &_a, Node &_b, const std::string& _nm = "") 
        :DoubleOperator(_a, _b, _nm) {}
    
    Add(const Add &t) = default;

    Add(Add &&t) :DoubleOperator(std::forward<DoubleOperator>(t)) {}    //完美转发，妙啊

    std::string Expr() {
        return "(" + a->Expr() + "+" + b->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Sub :public DoubleOperator {
private:
    void Judge(const Tensor&, const Tensor&) const override;
    Tensor eval(std::map<std::string, Tensor>&) override;
public:
    Sub(Node &_a, Node &_b, const std::string& _nm = "")
        :DoubleOperator(_a, _b, _nm) {}

    Sub(const Sub &t) = default;

    Sub(Sub &&t) :DoubleOperator(std::forward<DoubleOperator>(t)) {}    //完美转发，妙啊

    std::string Expr() {
        return "(" + a->Expr() + "-" + b->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Mul :public DoubleOperator {
private:
    void Judge(const Tensor&, const Tensor&) const override;
    Tensor eval(std::map<std::string, Tensor>&) override;
public:
    Mul(Node &_a, Node &_b, const std::string& _nm = "")
        :DoubleOperator(_a, _b, _nm) {}
    Mul(const Mul &t) = default;
    Mul(Mul &&t) :DoubleOperator(std::forward<DoubleOperator>(t)) {}    //完美转发，妙啊

    std::string Expr() {
        return "(" + a->Expr() + "*" + b->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Div :public DoubleOperator {
private:
    void Judge(const Tensor&, const Tensor&) const override;
    Tensor eval(std::map<std::string, Tensor>& Inputs) override;
public:
    Div(Node &_a, Node &_b, const std::string& _nm = "")
        :DoubleOperator(_a, _b, _nm) {}

    Div(const Div &t) = default;

    Div(Div &&t) :DoubleOperator(std::forward<DoubleOperator>(t)) {}    //完美转发，妙啊

    std::string Expr() {
        return "(" + a->Expr() + "/" + b->Expr() + ")";
    }

    Node& derive(int index) override;
};

class Pow :public DoubleOperator {
private:
    void Judge(const Tensor&, const Tensor&) const override;
    Tensor eval(std::map<std::string, Tensor>&) override;
public:
    Pow(Node &_a, Node &_b, const std::string& _nm = "")
        :DoubleOperator(_a, _b, _nm) {}

    Pow(const Pow &t) = default;

    Pow(Pow &&t) :DoubleOperator(std::forward<DoubleOperator>(t)) {}    //完美转发，妙啊

    std::string Expr() {
        return "(" + a->Expr() + "^" + b->Expr() + ")";
    }

    Node& derive(int index) override;
};

inline Add& operator +(Node& A, Node& B) {
    Add* tmp = new Add(A, B);
    return *tmp;
}

inline Sub& operator -(Node& A, Node& B) {
    Sub* tmp = new Sub(A, B);
    return *tmp;
}

inline Mul& operator *(Node& A, Node& B) {
    Mul* tmp = new Mul(A, B);
    return *tmp;
}

inline Div& operator /(Node& A, Node& B) {
    Div* tmp = new Div(A, B);
    return *tmp;
}

inline Pow& operator ^(Node& A, Node& B) {
    Pow* tmp = new Pow(A, B);
    return *tmp;
}
#endif
