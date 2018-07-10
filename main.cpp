#include "Meow.h"
#include <iostream>
//#include <bits/stdc++.h> 
using namespace std;

//Bind、Assert、Compare
void test1() {
    cout << "---test1---" << endl;
    auto x = Placeholder("x");
    auto y = Placeholder("y");
    auto t = x + y;
    auto as = Assert(y < x + *new Constant(2));
    auto res = Bind(t, as);
    cout << res.Eval({ { "x",1 },{ "y",2 } }).Print() << endl;
    // << 0
    cout << res.Eval({ { "x",1 },{ "y",4 } }).Print() << endl;
    // << Error: Assertion failed
    //cout << res.Eval({ { "x",1 },{ "y",-1 } }).Print() << endl;
    // << Error: Assertion failed
}

//derive
void test2() {
    cout << "---test2---" << endl;
    auto x = Placeholder("x");
    auto y = Placeholder("y");
    auto z = Constant(3, "z");
    auto t1 = Mul(x, z, "t1");
    auto u = Pow(y, t1, "u");
    auto t = Add(x, u, "t");
    auto t2 = Ln(t, "t2");
    auto judge = x > y;         //test compare node
    auto wow = t2.grad();
    for (auto i : wow) {
        std::cout << i.first->Name() << ' ' << 
            i.second->Eval({ { "x", 6 },{ "y", 2 } }).Print() << std::endl;
    }
}

//Newton
//牛顿迭代法求x^5+3x^3+2x^2+x+1的根
void test3() {
    cout << "---test3---" << endl;
    auto x0 = Variable(-1, "x0");
    auto c1 = Constant(1, "c1");
    auto c2 = Constant(2, "c2");
    auto c3 = Constant(3, "c3");
    auto p2 = PowC(x0, 2, "p2");
    auto p3 = PowC(x0, 3, "p3");
    auto p5 = PowC(x0, 5, "p5");
    auto f = p5 + c3*p3 + c2*p2 + x0 + c1;
    auto f1 = f.grad()[&x0];//f对x0的导数
    auto t = f / (*f1);
    auto newx = x0 - t;

    cout << f1->Eval({}).Value() << endl;
    int times = 100;//迭代次数
    for (int i = 0; i<times; i++) {
        x0.Set(newx.Eval({}));
        cout << x0.Eval({}).Value() << endl;
    }
}

//SingleOperator
void test4() {
    cout << "---test4---" << endl;
    auto x = Placeholder("x");
    auto y = Placeholder("y");
    auto z = Constant(3, "z");
    auto sz = Sin(z);
    auto ly = Ln(y);
    auto t = sz + ly;
    auto ex = Exp(x);
    auto res = t * ex;
    cout << res.Eval({ { "x",1 },{ "y",2 } }).Print() << endl;
    // << 2.267773338904851
    cout << res.Eval({ { "x",1 },{ "y",-1 } }).Print() << endl;
    // << Error: log operator’s input must be positive
    cout << t.Eval({ {"y",1} }).Print();
    // << 0.8342671886198125
    cout << endl;
}

//矩阵的Constant Placeholder Variable和相关运算
void test5() {
    cout << "---test5---" << endl;
    double a[2][3] = { { 1,2,3 },{ 4,5,6 } };
    double b[3][1] = { { 1 },{ 3 },{ 5 } };
    double c[2][1] = { { 3 },{ 2 } };

    double*pa[2] = { &a[0][0],&a[1][0] };
    double**ppa = &pa[0];
    auto ta = Tensor(2, 3, ppa);
    auto A = Constant(ta);

    double*pb[3] = { &b[0][0],&b[1][0],&b[2][0] };
    double**ppb = &pb[0];
    auto tb = Tensor(3, 1, ppb);

    auto B = Placeholder(3, 1, "B");

    double*pc[2] = { &c[0][0],&c[1][0] };
    double**ppc = &pc[0];
    auto tc = Tensor(2, 1, ppc);
    auto C = Variable(tc);

    auto D = A*B + C;
    auto D2 = Transpose(D);//转置
    cout << D2.Eval({ { "B",tb } }).Print() << endl;//{25,51}
}

int main() {
    try{
        test1();
    }
    catch(std::exception& e) {
        cerr << e.what() << endl;
    }
    try {
        test2();
    }
    catch (std::exception& e) {
        cerr << e.what() << endl;
    }
    try {
        test3();
    }
    catch (std::exception& e) {
        cerr << e.what() << endl;
    }
    try {
        test4();
    }
    catch (std::exception& e) {
        cerr << e.what() << endl;
    }
    try {
        test5();
    }
    catch (std::exception& e) {
        cerr << e.what() << endl;
    }

    int a;
    std::cin >> a;
}
