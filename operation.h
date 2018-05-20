/*************************************************

Date: 20180517

Description: 定义了一些东西

**************************************************/
#ifndef OPERATION_H
#define OPERATION_H

#include <map>
#include <iostream>

namespace ops {
class PlaceholderRoot;
class OpType;
typedef std::map<ops::PlaceholderRoot*, ops::OpType*> DataMap;
/// 所有节点的抽象基类 
class Operation {
protected:
    int inNum, outNum;          //输入输出节点的个数
    Operation** inputs;         //输入节点
    Operation** outputs;        //输出节点
    bool changed;               //标记是否被改变（data的值是否是实际值）
    OpType* data;               //数据
public:
    /* Constructors and Distructor */
    Operation();
    Operation(const Operation&) = delete;
    virtual ~Operation();

    /* 接口 */
    //通过eval求值，以map形式输入placeholder的参数
    //这里给出的代码为所有的placeholder赋值，可作为派生类的公共代码使用
    virtual OpType* eval(const DataMap& = DataMap()) = 0;
};

/// 所有placeholder的抽象基类，派生出不同数据类型的placeholder
class PlaceholderRoot :public Operation { 
protected:
    bool hasData;                      //是否已经被赋值
    virtual void setdata(OpType*);     //设置placeholder的值
    friend OpType* Operation::eval(const DataMap&);
public:
    /* 构造与析构 */
    PlaceholderRoot();
    virtual ~PlaceholderRoot() = 0;

    /* 接口 */
    //eval，此处查找是否已赋值，是则返回，否则报错并返回空指针
    virtual OpType* eval(const DataMap& = {}) override;
};

/// float类的placeholder
class PlaceholderFloat :public PlaceholderRoot {
protected:
    
public:
    virtual ~PlaceholderFloat();
    /* 接口 */
    virtual OpType* eval(const DataMap&) override;
};

/// 类型的基类
class OpType {
protected:
    //所以要用这个虚函数适配不同的具体类型，把数据塞进ostream里
    virtual std::ostream& output(std::ostream&) const = 0;
    //clone函数，用于实现基类指针的“深拷贝”
    virtual OpType* clone() = 0;
    //为什么大家都把它声明成友元！
public:
    friend Operation;
    //重载流输出运算，它不能是虚函数
    friend std::ostream& operator<< (std::ostream& out, const ops::OpType* op);
    /* mark:需要以虚函数的形式重载流操作符 */
    virtual ~OpType() = 0;
};

/// float类型
class op_float :public OpType {
protected:
    virtual std::ostream& output(std::ostream&) const override;
    virtual OpType* clone() override;
public:
    op_float();
    op_float(const float);
    float data;
};


}

#endif