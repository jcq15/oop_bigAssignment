#include "Meow.h" 
#include <bits/stdc++.h> 
int main() {
	auto x = Placeholder("x");
	auto y = Variable(1); 
	auto res = x + y;
	std::cout << res.Eval({{"x", 1}}).Print() << '\n';
	y.Set(2);
	std::cout << res.Eval({{"x", 1}}).Print() << '\n';
	y.Add(1);
	std::cout << res.Eval({{"x", 1}}).Print() << '\n';
	y.Sub(1);
	std::cout << res.Eval({{"x", 1}}).Print() << '\n';
	y.Mul(3);
	std::cout << res.Eval({{"x", 1}}).Print() << '\n';
	y.Div(3);
	std::cout << res.Eval({{"x", 1}}).Print() << '\n';
}
