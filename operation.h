/*************************************************

Date: 20180517

Description: ������дһЩ����

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
//DataMap��Ϊplaceholder��ֵʱʹ�õģ�����д���ǣ�
//{ {<�ڵ�1�ĵ�ַ>, pfloat(<������ֵ>)}, {����} }�����Ǹ�map��
typedef std::map<ops::PlaceholderRoot*, ops::OpType*> DataMap;

/// ���нڵ�ĳ������ 
class Operation {
protected:
    Operation* input[2];          //����ڵ�
    std::list<Operation*> outputs;  //����ڵ�
    bool changed;               //����Ƿ񱻸ı䣨data��ֵ�Ƿ���ʵ��ֵ��
    OpType* data;               //����
    void setChanged();          //���������֮��Ľڵ㣬���ݱ��޸���
public:
    Operation();
    virtual ~Operation() = 0;
    void _set_outputs_(Operation*);     //�������Ľӿ�

    //ͨ��eval��ֵ����map��ʽ����placeholder�Ĳ���
    //��������Ĵ���Ϊ���е�placeholder��ֵ������Ϊ������Ĺ�������ʹ��
    virtual OpType* eval(const DataMap& plchd = DataMap()) = 0;
};

///�����ڵ�ĳ������
class ConstantRoot :public virtual Operation{
public:
	virtual OpType* eval(const DataMap& plchd = DataMap()) override = 0;
};

///float���͵ĳ����ڵ�0
class ConstantFloat :public virtual ConstantRoot{
public:
    ConstantFloat();
	ConstantFloat(const float);
	OpType* eval(const DataMap& plchd = DataMap()) override;

    //���ز�����
    AddFloat operator+(ConstantFloat&);
    MinusFloat operator-(ConstantFloat&);
    MulFloat operator*(ConstantFloat&);
    DivFloat operator/(ConstantFloat&);
};


/// ����placeholder�ĳ�����࣬�̳���ConstantRoot�������������������͵�placeholder
class PlaceholderRoot :public virtual ConstantRoot { 
protected:
    virtual void setdata(OpType*);     //����placeholder��ֵ
    friend OpType* Operation::eval(const DataMap& plchd = DataMap());
public:
    /* �ӿ� */
    //eval���˴������Ƿ��Ѹ�ֵ�����򷵻أ����򱨴����ؿ�ָ��
    virtual OpType* eval(const DataMap& plchd = DataMap()) override = 0;
};

/// float���placeholder
class PlaceholderFloat :public virtual PlaceholderRoot, public ConstantFloat {
public:
    OpType* eval(const DataMap& plchd = DataMap()) override;
};

/// parameter�Ļ���
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

/// ����ֵ��float������
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