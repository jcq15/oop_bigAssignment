/*************************************************

Date: 20180517

Description: ������һЩ����

**************************************************/
#ifndef OPERATION_H
#define OPERATION_H

#include <map>
#include <iostream>

namespace ops {
class PlaceholderRoot;
class OpType;
typedef std::map<ops::PlaceholderRoot*, ops::OpType*> DataMap;
/// ���нڵ�ĳ������ 
class Operation {
protected:
    int inNum, outNum;          //��������ڵ�ĸ���
    Operation** inputs;         //����ڵ�
    Operation** outputs;        //����ڵ�
    bool changed;               //����Ƿ񱻸ı䣨data��ֵ�Ƿ���ʵ��ֵ��
    OpType* data;               //����
public:
    /* Constructors and Distructor */
    Operation();
    Operation(const Operation&) = delete;
    virtual ~Operation();

    /* �ӿ� */
    //ͨ��eval��ֵ����map��ʽ����placeholder�Ĳ���
    //��������Ĵ���Ϊ���е�placeholder��ֵ������Ϊ������Ĺ�������ʹ��
    virtual OpType* eval(const DataMap& = DataMap()) = 0;
};

/// ����placeholder�ĳ�����࣬��������ͬ�������͵�placeholder
class PlaceholderRoot :public Operation { 
protected:
    bool hasData;                      //�Ƿ��Ѿ�����ֵ
    virtual void setdata(OpType*);     //����placeholder��ֵ
    friend OpType* Operation::eval(const DataMap&);
public:
    /* ���������� */
    PlaceholderRoot();
    virtual ~PlaceholderRoot() = 0;

    /* �ӿ� */
    //eval���˴������Ƿ��Ѹ�ֵ�����򷵻أ����򱨴����ؿ�ָ��
    virtual OpType* eval(const DataMap& = {}) override;
};

/// float���placeholder
class PlaceholderFloat :public PlaceholderRoot {
protected:
    
public:
    virtual ~PlaceholderFloat();
    /* �ӿ� */
    virtual OpType* eval(const DataMap&) override;
};

/// ���͵Ļ���
class OpType {
protected:
    //����Ҫ������麯�����䲻ͬ�ľ������ͣ�����������ostream��
    virtual std::ostream& output(std::ostream&) const = 0;
    //clone����������ʵ�ֻ���ָ��ġ������
    virtual OpType* clone() = 0;
    //Ϊʲô��Ҷ�������������Ԫ��
public:
    friend Operation;
    //������������㣬���������麯��
    friend std::ostream& operator<< (std::ostream& out, const ops::OpType* op);
    /* mark:��Ҫ���麯������ʽ������������ */
    virtual ~OpType() = 0;
};

/// float����
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