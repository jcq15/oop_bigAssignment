#include "Meow.h" 
#include <bits/stdc++.h> 
int main() 
{
	auto x = Placeholder(3, 3, "x");
	auto y = Placeholder("y");
	auto z = Constant(3, "z");
	auto v = Variable(3, 3, "v");
	auto t = x + (v ^ y);
	double **M1 = new double* [3];
	M1[0] = new double [3]{10, 0, 0};
	M1[1] = new double [3]{0, 10, 0};
	M1[2] = new double [3]{0, 0, 10};
	Tensor a(3, 3, M1);
	v.Set(a);
	v.Add(a);
	std::cout << t.Eval({{"x", a}, {"y", 2}}).Print();
	auto t2 = Ln(t);
	t.Debug();
	std::cout << t2.Eval({{"x", a}, {"y", 2}}).Print();
	std::cout << t2.PrintRely();
	std::cout << t2.PrintExpr();
}
