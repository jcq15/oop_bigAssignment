/*************************************************

Date: 20180517

Description: ¶¨ÒåÁËÒ»Ð©¶«Î÷

**************************************************/

#include "Operation.h"
#include "Optype.h"
#include <iostream>

namespace ops {

Operation::Operation() :outputs(), changed(false), data(nullptr) {
    input[0] = nullptr;
    input[1] = nullptr;
}
Operation::~Operation() {
    if(!outputs.empty()){
        std::cout << "Error" << std::endl;
        return;
    }
    for(int i=0; i<=1; i++){
        if(!input[i])continue;
        for(auto iter = input[i]->outputs.begin(); iter!=input[i]->outputs.end() ;iter++){
            if(*iter==this){
                input[i]->outputs.erase(iter);
                break;
            }
        }
    }
    return;
}

void Operation::_set_outputs_(Operation* op) {
    outputs.push_back(op);
}

void Operation::setChanged(){
    if(changed)return;
    changed = true;
    for(auto iter = outputs.begin(); iter!=outputs.end() ;iter++){//标记他后面的节点
        Operation* p = *iter;
        p->setChanged();
    }
}
OpType* Operation::eval(const DataMap& plchd){
    for (auto v : plchd) {
        v.first->setdata(v.second);
    }
    return data;
}

OpType* ConstantRoot::eval(const DataMap& plchd){
    return Operation::eval(plchd);
}

ConstantFloat::ConstantFloat() {}
ConstantFloat::ConstantFloat(const float f){
    data = pfloat(f);
}
OpType* ConstantFloat::eval(const DataMap& plchd){
    return Operation::eval(plchd);
}

AddFloat ConstantFloat::operator+(ConstantFloat& op) {
    AddFloat ans(*this, op);
    return ans;
}
MinusFloat ConstantFloat::operator-(ConstantFloat& op) {
    MinusFloat ans(*this, op);
    return ans;
}
MulFloat ConstantFloat::operator*(ConstantFloat& op) {
    MulFloat ans(*this, op);
    return ans;
}
DivFloat ConstantFloat::operator/(ConstantFloat& op) {
    DivFloat ans(*this, op);
    return ans;
}


void PlaceholderRoot::setdata(OpType* input) {
    data = input;
    setChanged();
    changed = false;
}
OpType* PlaceholderRoot::eval(const DataMap& plchd){
    return Operation::eval(plchd);
}

OpType* PlaceholderFloat::eval(const DataMap& plchd){
    return Operation::eval(plchd);
}

ParameterRoot::ParameterRoot() {}
void ParameterRoot::set(OpType* input) {
    *data = *input;
    setChanged();   //把它的输出的changed设为true，但他自己的是false
    changed = false;
    return;
}
void ParameterFloat::add(float input) {
    data = new Op_float(*static_cast<Op_float*>(data) + *pfloat(input));
    setChanged();
    changed = false;
    return;
}
void ParameterFloat::minus(float input) {
    data = new Op_float(*static_cast<Op_float*>(data) - *pfloat(input));
    setChanged();
    changed = false;
    return;
}
void ParameterFloat::multiply(float input) {
    data = new Op_float(*static_cast<Op_float*>(data) * *pfloat(input));
    setChanged();
    changed = false;
    return;
}
void ParameterFloat::divide(float input) {
    data = new Op_float(*static_cast<Op_float*>(data) / *pfloat(input));
    setChanged();
    changed = false;
    return;
}
OpType* ParameterRoot::eval(const DataMap& plchd) {
    return Operation::eval(plchd);
}

OpType* ParameterFloat::eval(const DataMap& plchd) {
    return Operation::eval(plchd);
}
ParameterFloat::ParameterFloat() :ParameterRoot(),ConstantFloat() {}
ParameterFloat::ParameterFloat(const float f) : ParameterRoot() {
    data = pfloat(f);
}

/// 四则运算
AddFloat::AddFloat(Operation& a, Operation& b) {
    changed = true;
    input[0] = &a, input[1] = &b;
    a._set_outputs_(this);      //给他们添加输出
    b._set_outputs_(this);
}

OpType* AddFloat::eval(const DataMap& plchd) {
    Operation::eval(plchd);
    if (!changed) return data;      //如果数据正确，直接输出
    data = new Op_float(*static_cast<Op_float*>(input[0]->eval())
        + *static_cast<Op_float*>(input[1]->eval()));
    changed = false;
    return data;
}

MinusFloat::MinusFloat(Operation& a, Operation& b) {
    changed = true;
    input[0] = &a, input[1] = &b;
    a._set_outputs_(this);      //给他们添加输出
    b._set_outputs_(this);
}

OpType* MinusFloat::eval(const DataMap& plchd) {
    Operation::eval(plchd);
    if (!changed) return data;      //如果数据正确，直接输出
    data = new Op_float(*static_cast<Op_float*>(input[0]->eval())
        - *static_cast<Op_float*>(input[1]->eval()));
    changed = false;
    return data;
}

MulFloat::MulFloat(Operation& a, Operation& b) {
    changed = true;
    input[0] = &a, input[1] = &b;
    a._set_outputs_(this);      //给他们添加输出
    b._set_outputs_(this);
}

OpType* MulFloat::eval(const DataMap& plchd) {
    Operation::eval(plchd);
    if (!changed) return data;      //如果数据正确，直接输出
    data = new Op_float(*static_cast<Op_float*>(input[0]->eval())
        * *static_cast<Op_float*>(input[1]->eval()));
    changed = false;
    return data;
}

DivFloat::DivFloat(Operation& a, Operation& b) {
    changed = true;
    input[0] = &a, input[1] = &b;
    a._set_outputs_(this);      //给他们添加输出
    b._set_outputs_(this);
}

OpType* DivFloat::eval(const DataMap& plchd) {
    Operation::eval(plchd);
    if (!changed) return data;      //如果数据正确，直接输出
    data = new Op_float(*static_cast<Op_float*>(input[0]->eval())
        / *static_cast<Op_float*>(input[1]->eval()));
    changed = false;
    return data;
}

/*template <class T>
T& print(T& op) {
    std::cout << op.eval();
    return op;
}*/

}

// 重载流输出
std::ostream& ops::operator<< (std::ostream& out, const ops::OpType* op) {
    return op->output(out);
}
