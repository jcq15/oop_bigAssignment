/*************************************************

Date: 20180517

Description: 在这里写一些描述

**************************************************/
#ifndef OPERATION_H
#define OPERATION_H

#include "Optype.h"
#include <map>
#include <iostream>
#include <list>

namespace ops {
class PlaceholderRoot;
class OpType;
class AddFloat;
class MinusFloat;
class MulFloat;
class DivFloat;
//DataMap是为placeholder赋值时使用的，具体写法是：
//{ {<节点1的地址>, pfloat(<具体数值>)}, {……} }（这是个map）
typedef std::map<ops::PlaceholderRoot*, ops::OpType*> DataMap;

/// 所有节点的抽象基类 
class Operation {
protected:
    Operation* input[2];          //输入节点
    std::list<Operation*> outputs;  //输出节点
    bool changed;               //标记是否被改变（data的值是否是实际值）
    OpType* data;               //数据
    void setChanged();          //标记它和它之后的节点，数据被修改了
public:
    Operation();
    virtual ~Operation() = 0;
    void _set_outputs_(Operation*);     //添加输出的接口

    //通过eval求值，以map形式输入placeholder的参数
    //这里给出的代码为所有的placeholder赋值，可作为派生类的公共代码使用
    virtual OpType* eval(const DataMap& plchd = DataMap()) = 0;
};

///常数节点的抽象基类
class ConstantRoot :public virtual Operation{
public:
	virtual OpType* eval(const DataMap& plchd = DataMap()) override = 0;
};

///float类型的常数节点0
class ConstantFloat :public virtual ConstantRoot{
public:
    ConstantFloat();
	ConstantFloat(const float);
	OpType* eval(const DataMap& plchd = DataMap()) override;

    //重载操作符
    AddFloat operator+(ConstantFloat&);
    MinusFloat operator-(ConstantFloat&);
    MulFloat operator*(ConstantFloat&);
    DivFloat operator/(ConstantFloat&);
};


/// 所有placeholder的抽象基类，继承自ConstantRoot，派生出具体数据类型的placeholder
class PlaceholderRoot :public virtual ConstantRoot { 
protected:
    virtual void setdata(OpType*);     //设置placeholder的值
    friend OpType* Operation::eval(const DataMap& plchd = DataMap());
public:
    /* 接口 */
    //eval，此处查找是否已赋值，是则返回，否则报错并返回空指针
    virtual OpType* eval(const DataMap& plchd = DataMap()) override = 0;
};

/// float类的placeholder
class PlaceholderFloat :public virtual PlaceholderRoot, public ConstantFloat {
public:
    OpType* eval(const DataMap& plchd = DataMap()) override;
};

/// parameter的基类
class ParameterRoot :public virtual ConstantRoot {
public:
    ParameterRoot();
    virtual void set(OpType*);
    virtual OpType* eval(const DataMap& plchd = DataMap()) = 0;
};

class ParameterFloat :public virtual ParameterRoot, public ConstantFloat {
public:
    void add(float);
    void minus(float);
    void multiply(float);
    void divide(float);

    ParameterFloat();
    ParameterFloat(const float);
    //~ParameterFloat();

    virtual OpType* eval(const DataMap& plchd = DataMap()) override;

};

/// 返回值是float的运算
class AddFloat :public ConstantFloat {
public:
    AddFloat(Operation&, Operation&);
    OpType* eval(const DataMap& plchd = DataMap()) override;
};
class MinusFloat :public ConstantFloat {
public:
    MinusFloat(Operation&, Operation&);
    OpType* eval(const DataMap& plchd = DataMap()) override;
};
class MulFloat :public ConstantFloat {
public:
    MulFloat(Operation&, Operation&);
    OpType* eval(const DataMap& plchd = DataMap()) override;
};
class DivFloat :public ConstantFloat {
public:
    DivFloat(Operation&, Operation&);
    OpType* eval(const DataMap& plchd = DataMap()) override;
};

/// print
template <class T>
T& print(T& op){
    std::cout << op.eval() << std::endl;
    return op;
}

}

#endif