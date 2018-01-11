// 接受一个整型参数N，返回不大于log2N的最大整数

#include <iostream>
using namespace std;

int pow(int base, int exp) {
  int res = base;
  for (int i = 1; i < exp; i++) {
    res *= base;
  }
  return res;
}
int lg(int N) {
  int i = 0;
  while (pow(2, i + 1) < N) {
    i++;
  }
  return i;
}

int main() {
  cout << "2^3: " << pow(2, 3) << endl;
  cout << "lg(10): " << lg(10) << endl;
}