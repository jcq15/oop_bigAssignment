#include "Meow.h" 
#include <bits/stdc++.h> 
int main() {
	auto x = Placeholder("x");
	auto y = Placeholder("y");
	auto z = Constant(3, "z");
	auto t = y + z;
	auto res = t * (x + y);
	std::cout << res.Eval({{"x", 1}, {"y", 2}}).Print() << '\n';
	std::cout << res.Eval({{"x", 1}, {"y", 0}}).Print() << '\n';
	std::cout << t.Eval({{"y", 2}}).Print() << '\n';
	std::cout <<  res.Eval({{"y", 2}}).Print() << 'n';
}
