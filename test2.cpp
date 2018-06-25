#include "Meow.h" 
#include <bits/stdc++.h> 
int main() {
	auto x = Placeholder("x");
	auto y = Placeholder("y");
	auto z = Placeholder("z");
	auto t = x + y; 
	t.Debug();
	auto res = t + z;
	std::cout << res.Eval({{"x", 1}, {"y", 3}, {"z", 2}}).Print() << '\n';
	std::cout << res.Eval({{"x", 1}, {"y", 2}, {"z", 3}}).Print() << '\n';
}
