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

//DataMap用来给placeholder赋值，使用方法请参考示例代码
typedef std::map<ops::PlaceholderRoot*, ops::OpType*> DataMap;

/// 所有节点的抽象基类
class Operation {
protected:
    Operation* input[2];                //输入节点（0或1或2个）
    std::list<Operation*> outputs;      //输出节点
    bool changed;                       //标记data是否最新
    OpType* data;                       //数据
    void setChanged();                  //修改和他相关的节点的changed属性
public:
    Operation();
    virtual ~Operation() = 0;
    void _set_outputs_(Operation*);     //添加输出

    //这里提供了公共代码：为placeholder赋值
    virtual OpType* eval(const DataMap& plchd = DataMap()) = 0;
};

/// 所有Constant的抽象基类
class ConstantRoot :public virtual Operation{
public:
	virtual OpType* eval(const DataMap& plchd = DataMap()) override = 0;
};

class ConstantFloat :public virtual ConstantRoot{
public:
    ConstantFloat();
	ConstantFloat(const float);
	OpType* eval(const DataMap& plchd = DataMap()) override;

    //四则运算
    AddFloat operator+(ConstantFloat&);
    MinusFloat operator-(ConstantFloat&);
    MulFloat operator*(ConstantFloat&);
    DivFloat operator/(ConstantFloat&);
};

/// 所有Placeholder类的抽象基类
class PlaceholderRoot :public virtual ConstantRoot { 
protected:
    virtual void setdata(OpType*);     //ÉèÖÃplaceholderµÄÖµ
    friend OpType* Operation::eval(const DataMap& plchd = DataMap());
public:
    virtual OpType* eval(const DataMap& plchd = DataMap()) override = 0;
};

class PlaceholderFloat :public virtual PlaceholderRoot, public ConstantFloat {
public:
    OpType* eval(const DataMap& plchd = DataMap()) override;
};

/// parameter的抽象基类
class ParameterRoot :public virtual ConstantRoot {
public:
    ParameterRoot();
    virtual void set(OpType*);
    virtual OpType* eval(const DataMap& plchd = DataMap()) = 0;
};

class ParameterFloat :public virtual ParameterRoot, public ConstantFloat {
public:
    void set(float);
    void add(float);
    void minus(float);
    void multiply(float);
    void divide(float);

    ParameterFloat();
    ParameterFloat(const float);

    virtual OpType* eval(const DataMap& plchd = DataMap()) override;

};

/// 四则运算
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

/// print节点
class Print :public ConstantFloat{
public:
    Print(Operation&);
    OpType* eval(const DataMap& plchd = DataMap());
};

}

#endif