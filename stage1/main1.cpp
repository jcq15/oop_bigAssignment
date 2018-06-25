#include <iostream>
#include <map>
#include "Operation.h"
#include "Optype.h"

using namespace std;
using namespace ops;

//测试的时候请将文件名改为main.cpp, 或自行修改Makefile

int main() {

    auto x = PlaceholderFloat();
    auto y = PlaceholderFloat();
    auto z = ConstantFloat(3);
    auto t1 = x+y;
    auto t2 = y/z;
    auto res = t1*t2;
    cout << res.eval({ {&x, pfloat(1)} , {&y, pfloat(2)} }) << endl; //2
    cout << res.eval({ {&x, pfloat(3)} , {&y, pfloat(1)} }) << endl; //1.333333
    cout << res.eval({ {&x, pfloat(4)} , {&y, pfloat(5)} }) << endl; //15

    return 0;
}