/*************************************************

Date: 20180517

Description: ������һЩ����

**************************************************/

#include "operation.h"
#include <iostream>

namespace ops {

Operation::Operation() :inNum(0), outNum(0), inputs(nullptr),
    outputs(nullptr), changed(false), data(nullptr) {}

Operation::~Operation() {
    //��������ƣ����һ���Ƿ��ͷ�inputs��outputs
}

//��ֵ�������˴�Ϊ����placeholder��ֵ
//���ǵ�plchd��second��ܿ�������ֵ����������newһ��
OpType* Operation::eval(const DataMap& plchd) {
    for (auto v : plchd) {
        v.first->setdata(v.second->clone());
    }
    return nullptr;
}

PlaceholderRoot::PlaceholderRoot() :hasData(false) {}

//����placeholder��ֵ��һ�㲻��Ҫ����
void PlaceholderRoot::setdata(OpType* input) {
    data = input;
    hasData = true;
}

OpType* PlaceholderRoot::eval(const DataMap& plchd) {
    if (!plchd.empty()) Operation::eval(plchd);    //����ǿգ�Ϊplaceholder��ֵ
    if (hasData) {
        return data;
    }
    else {
        std::cerr << "Error��Placeholderδ��ֵ��" << std::endl;
        return nullptr;
    }
}

PlaceholderRoot::~PlaceholderRoot() {}

PlaceholderFloat::~PlaceholderFloat() {}

OpType* PlaceholderFloat::eval(const DataMap& plchd) {
    return PlaceholderRoot::eval(plchd);
    //ֱ�ӵ��û��ຯ�����ɣ�Ϊ�˴���ͳһ�ԣ�������д��һ��
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

//���Ҫ�������ռ���
std::ostream& ops::operator<< (std::ostream& out, const ops::OpType* op) {
    return op->output(out);
}
