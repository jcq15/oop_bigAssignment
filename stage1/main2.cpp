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
    auto res = y-zp;
    cout << res.eval({ {&x, pfloat(4)} , {&y, pfloat(2.5)} }) << endl; 
    cout << res.eval({ {&x, pfloat(3)} , {&y, pfloat(7)} }) << endl; 
    //Print Operation : 10
	//-7.5
	//Print Operation : 21
	//-14

    return 0;
}