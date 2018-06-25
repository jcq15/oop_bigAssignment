#include "Meow.h" 
#include <bits/stdc++.h> 
int main() {
	auto x = Placeholder("x");
	auto t = x; 
	t.Debug();
	auto y = Constant(1, "y");
	auto a0 = t + y;
	auto a1 = t + a0;
	auto a2 = t + a1;
	std::cout << a2.Eval({{"x", 1}}).Print() << '\n';
}
