#include "Meow.h"
#include <iostream>
//#include <bits/stdc++.h> 
int main() 
{
	auto x = Placeholder("x");
	auto y = Placeholder("y");
	auto z = Constant(3, "z");
    auto u = Pow(y, z, "u");
    auto t = Add(x, u, "t");
	//std::cout << t.Eval({{"x", 6}, {"y", 2}}).Print() << std::endl;
    auto t2 = Ln(t, "t2");
    auto shit = t2.grad();
    for (auto i : shit) {
        std::cout << i.first->Name() << i.second->Eval({ { "x", 6 },{ "y", 2 } }).Print() << std::endl;
    }
    std::cout<<(z>=3.2);
    int a;
    std::cin >> a;
}
