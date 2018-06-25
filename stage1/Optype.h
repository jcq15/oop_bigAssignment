#ifndef OPTYPE_H
#define OPTYPE_H

#include "Operation.h"
#include <map>
#include <iostream>

namespace ops{
class Operation;
class OpType {
protected:
    //流输出运算符不能用虚函数
    //所以用这个虚函数适配不同的具体类型，把数据塞进ostream里
    virtual std::ostream& output(std::ostream&) const = 0;
public:
    friend Operation;       //只用了其中一个函数而已
    //重载流输出运算，它不能是虚函数
    friend std::ostream& operator<< (std::ostream& out, const OpType* op);
    virtual ~OpType() = 0;
};

//这里必须声明一次
std::ostream& operator<< (std::ostream&, const OpType*);

/// float类型
class Op_float :public OpType {
protected:
    virtual std::ostream& output(std::ostream&) const override;
    float data;
public:
    Op_float();
    Op_float(const float);

    //重载操作符
    Op_float operator+(Op_float&);
    Op_float operator-(Op_float&);
    Op_float operator*(Op_float&);
    Op_float operator/(Op_float&);
};

//这个是将float转成Op_float指针的函数，参见main文件34行
Op_float* pfloat(const float);

}

#endif