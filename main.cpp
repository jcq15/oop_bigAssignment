#include <iostream>
#include <map>
#include "operation.h"

using namespace std;
using namespace ops;

/**
//这是和这个项目没啥关系的测试代码，请无视
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
    PlaceholderFloat op;

    cout << op.eval({ {&op,p_float(2.5)} });

    char fuck;
    cin >> fuck;
    return 0;
}