#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include "operation.h"

using namespace std;
using namespace ops;

/**
class a {
public:
    int aa;
    a() :aa(1024){}
    friend ostream& operator << (ostream& out, const a&);
};

ostream& operator << (ostream& out, const a* wow) {
    out << wow->aa << endl;
    return out;
}


void test(const vector<int>& test) {
    int a = test[0];
    cout << "ok!" << a << endl;
}
**/

int main() {
    //a* aha = new a;
    //cout << aha;
    
    PlaceholderFloat op;

    //auto* a = { {&op,&op_float(2.5)} };
    cout << op.eval(a);

    int aaa;
    cin >> aaa;
    return 0;
}