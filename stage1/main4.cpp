#include <iostream>
#include <map>
#include "Operation.h"
#include "Optype.h"

using namespace std;
using namespace ops;

//���Ե�ʱ���뽫�ļ�����Ϊmain.cpp, �������޸�Makefile

int main() {

    auto x = PlaceholderFloat();
    auto y = ParameterFloat();
    auto z = ParameterFloat(2);
    y.set(2.3);
    y.multiply(3);
    cout << y.eval() << endl;    //6.9
    auto t = y/z;
    z.add(1);
    z.minus(1.5);
    z.divide(-2);
    auto res = t*x;
    cout << res.eval({ {&x, pfloat(2)} }) << endl;  //-18.4

    return 0;
}