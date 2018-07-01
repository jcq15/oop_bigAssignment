#include "Meow.h"
#include <iostream>
//#include <bits/stdc++.h> 
using namespace std;

int main() {
    auto x = Placeholder("x");
    auto y = Placeholder("y");
    auto t = x + y;
    auto as = Assert(y < x + *new Constant(2));
    //auto t1 = Bind(t, as);
    auto res = Bind(t, as);
    cout << res.Eval({ { "x",1 },{ "y",2 } }).Print() << endl;
    // << 0
    cout << res.Eval({ { "x",1 },{ "y",4 } }).Print() << endl;
	// << Error: Assertion failed
    cout << res.Eval({ { "x",1 },{ "y",-1 } }).Print() << endl;
    // << Error: Assertion failed

    /*
	auto x = Placeholder("x");
	auto y = Placeholder("y");
    auto t = x + y;
    auto t1 = Assert(y > x);
    cout << t1.Eval({ { "x",1 },{ "y",2 } }).Print() << endl;   //0
    cout << t1.Eval({ { "x",3 },{ "y",2 } }).Print() << endl;  //error 
    */

    /*Çóµ¼²âÊÔ
	auto z = Constant(3, "z");
    auto u = Pow(y, z, "u");
    auto t = Add(x, u, "t");
    
	//std::cout << t.Eval({{"x", 6}, {"y", 2}}).Print() << std::endl;
    auto t2 = Ln(t, "t2");
    auto shit = t2.grad();
    for (auto i : shit) {
        std::cout << i.first->Name() << i.second->Eval({ { "x", 6 },{ "y", 2 } }).Print() << std::endl;
    }
    auto m = (z>z);
    std::cout<<m.eval().print();
    */

    int a;
    std::cin >> a;
}
