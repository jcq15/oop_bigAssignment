#include <iostream>
#include <map>
#include "Operation.h"
#include "Optype.h"

using namespace std;
using namespace ops;

//���Ե�ʱ���뽫�ļ�����Ϊmain.cpp, �������޸�Makefile

int main() {

    auto x = new PlaceholderFloat();
    auto y = new ConstantFloat(1.5);
    auto z = new AddFloat(*x, *y);
    cout << z->eval({ {x, pfloat(2)} }) << endl;  //3.5

    //delete y;  //�����Error:����������ڵ�Ϊ����Ľڵ�

    delete z;
    delete y;   //������ɾ��z��ɾy

    return 0;
}