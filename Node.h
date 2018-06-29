#ifndef NODE
#include <string>
#include <map>
#include <set>
#include "Tensor.h"
#define NODE

class Node {
protected:
    bool debug;
    std::string name;
    Tensor* value;
    int depends = 0;        //�������ԣ���������ڵ����
public:
    Node(const std::string& _name, Tensor* _t = nullptr) :debug(false), name(_name), value(_t) {}

    Node(const Node& t) :debug(t.debug), name(t.name), value(nullptr), depends(t.depends) {
        if (t.value != nullptr)
            value = new Tensor(*(t.value));
    }

    Node(Node&& t) :debug(t.debug), name(t.name), value(t.value) {
        t.value = nullptr;
    }

    ~Node() {
        if (value != nullptr)delete value;
    }

    void Debug() {
        debug = true;
    }

    void NDebug() {
        debug = false;
    }

    std::string Name() const { return name; }

    std::string PrintExpr() {
        return name + " = " + Expr() + "\n";
    }

    virtual std::string Expr() = 0;
    virtual void Rely(std::set<std::string>&) = 0;//����������ڵ� 
    std::string PrintRely();
    virtual Tensor eval(std::map<std::string, Tensor>&) = 0;//��ֵ 
    virtual void Release() = 0;//�ͷű����ֵ 
    Tensor Eval(std::map<std::string, Tensor>&);//ʹ��map 
    Tensor Eval(const std::initializer_list<std::pair<std::string, Tensor>>&);//ʹ�ó�ʼ���б� 

    /**�ڶ��׶�����**/
    int depend() const { return depends; }        //��������ڵ����
    virtual Node& derive(int index=0); //������index��ʾ���ĸ������󵼣�0�Լ���1a��2b
    std::map<Node*, Node*>& grad();                //�ݶ�

    friend bool operator ==(const Node&, const Node&);
    friend bool operator >(const Node&, const Node&);
    friend bool operator <(const Node&, const Node&);
    friend bool operator >=(const Node&, const Node&);
    friend bool operator <=(const Node&, const Node&);
    friend bool operator ==(const Node&a, const Tensor&b){return *a.value==b;}
    friend bool operator >(const Node&a, const Tensor&b){return *a.value>b;}
    friend bool operator <(const Node&a, const Tensor&b){return *a.value<b;}
    friend bool operator >=(const Node&a, const Tensor&b){return *a.value>=b;}
    friend bool operator <=(const Node&a, const Tensor&b){return *a.value<=b;}
    friend bool operator ==(const Tensor&a, const Node&b){return a==*b.value;}
    friend bool operator >(const Tensor&a, const Node&b){return a>*b.value;}
    friend bool operator <(const Tensor&a, const Node&b){return a<*b.value;}
    friend bool operator >=(const Tensor&a, const Node&b){return a>=*b.value;}
    friend bool operator <=(const Tensor&a, const Node&b){return a<=*b.value;}
};

#endif
