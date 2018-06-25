#include "Optype.h"
#include <iostream>

namespace ops{
OpType::~OpType() {}

Op_float::Op_float() :data(0) {}

Op_float::Op_float(const float num) : data(num) {}

std::ostream& Op_float::output(std::ostream& out) const {
    out << data;
    return out;
}

Op_float* pfloat(const float data) {
    Op_float* p = new Op_float(data);
    return p;
}

Op_float Op_float::operator+(Op_float& op) {
    Op_float ans(data + op.data);
    return ans;
}
Op_float Op_float::operator-(Op_float& op) {
    Op_float ans(data - op.data);
    return ans;
}
Op_float Op_float::operator*(Op_float& op) {
    Op_float ans(data * op.data);
    return ans;
}
Op_float Op_float::operator/(Op_float& op) {
    Op_float ans(data / op.data);
    return ans;
}

}