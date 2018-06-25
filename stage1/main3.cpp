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
    auto z = x*y;
    auto zp = Print(z);
    auto t1 = y-zp;
    auto t2 = zp/t1;
    auto t3 = zp+t2;
    cout << t3.eval({ {&x, pfloat(2)} , {&y, pfloat(4)} }) << endl; 
    //Print Operation : 8
	//6
    return 0;
}