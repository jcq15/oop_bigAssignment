/*************************************************

Date: 20180517

Description: 定义了一些东西

**************************************************/

#include "operation.h"
#include <iostream>

namespace ops {

Operation::Operation() :inNum(0), outNum(0), inputs(nullptr),
    outputs(nullptr), changed(false), data(nullptr) {}

Operation::~Operation() {
    //这里待完善，检测一下是否释放inputs，outputs
}

//求值函数，此处为所有placeholder赋值
//考虑到plchd的second项很可能是右值，这里重新new一个
OpType* Operation::eval(const DataMap& plchd) {
    for (auto v : plchd) {
        v.first->setdata(v.second->clone());
    }
    return nullptr;
}

PlaceholderRoot::PlaceholderRoot() :hasData(false) {}

//设置placeholder的值，一般不需要重载
void PlaceholderRoot::setdata(OpType* input) {
    data = input;
    hasData = true;
}

OpType* PlaceholderRoot::eval(const DataMap& plchd) {
    if (!plchd.empty()) Operation::eval(plchd);    //如果非空，为placeholder赋值
    if (hasData) {
        return data;
    }
    else {
        std::cerr << "Error！Placeholder未赋值！" << std::endl;
        return nullptr;
    }
}

PlaceholderRoot::~PlaceholderRoot() {}

PlaceholderFloat::~PlaceholderFloat() {}

OpType* PlaceholderFloat::eval(const DataMap& plchd) {
    return PlaceholderRoot::eval(plchd);
    //直接调用基类函数即可，为了代码统一性，还是重写了一下
}



OpType* op_float::clone() {
    op_float* newOp = new op_float(*this);
    return newOp;
}

OpType::~OpType() {}

op_float::op_float() :data(0) {}

op_float::op_float(const float num) : data(num) {}

std::ostream& op_float::output(std::ostream& out) const {
    out << data;
    return out;
}

op_float* p_float(const float data) {
    op_float* p = new op_float(data);
    return p;
}

}

//这个要在命名空间外
std::ostream& ops::operator<< (std::ostream& out, const ops::OpType* op) {
    return op->output(out);
}
