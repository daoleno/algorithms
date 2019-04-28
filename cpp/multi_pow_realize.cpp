#include <string>
#include <iostream>

using namespace std;

// result: a*b
// int mystery(int a, int b) {
//     if (b == 0) return 0;
//     if (b % 2 ==0) return mystery(a+a, b/2);
//     return mystery(a+a, b/2) + a;
// }

// result: a^b
int mystery(int a, int b) {
    if (b == 0) return 1;
    if (b % 2 ==0) return mystery(a*a, b/2);
    return mystery(a*a, b/2) * a;
}
int main() {
    cout << mystery(2, 25) << endl;
    cout << "-----------" << endl;
    cout << mystery(3, 11);
}
