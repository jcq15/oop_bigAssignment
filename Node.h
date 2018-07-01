#ifndef NODE
#include <string>
#include <map>
#include <set>
#include "Tensor.h"
#define NODE

/*
class Node;
//stage2 add, using to fengzhuang gradiate
class Gradiate {
private:
    std::map<Node*, Node*>* grad;
public:
    Gt
    Node* operator[](Node* key) { return (*grad)[key]; }
};
*/

class Node {
protected:
    bool debug;
    std::string name;
    Tensor* value;
    int depends = 0;        //新增属性，描述输入节点个数
    bool prop = true;       //是否接受别人对他求导（比如">"就不接受）
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
    virtual void Rely(std::set<std::string>&) = 0;//依赖的输入节点 
    std::string PrintRely();
    virtual Tensor eval(std::map<std::string, Tensor>&) = 0;//求值 
    virtual void Release() = 0;//释放保存的值 
    virtual Tensor Eval(std::map<std::string, Tensor>&);//使用map 
    virtual Tensor Eval(const std::initializer_list<std::pair<std::string, Tensor>>&);//使用初始化列表 

    /**第二阶段新增**/
    int depend() const { return depends; }          //返回输入节点个数
    bool Prop() const { return prop; }              //RT
    virtual Node& derive(int index=0);              //求导数，index表示对哪个参数求导
    std::map<Node*, Node*>& grad();                 //梯度
    /*
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
    */
};

#endif
