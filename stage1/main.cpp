#include <iostream>
#include <map>
#include "Operation.h"
#include "Optype.h"

using namespace std;
using namespace ops;

//测试的时候请将文件名改为main.cpp, 或自行修改Makefile

int main() {

    auto x = new PlaceholderFloat();
    auto y = new ConstantFloat(1.5);
    auto z = new AddFloat(*x, *y);
    cout << z->eval({ {x, pfloat(2)} }) << endl;  //3.5

    //delete y;  //会输出Error:还有以这个节点为输入的节点

    delete z;
    delete y;   //必须先删除z再删y

    return 0;
}