// 接受一个整型数组 a[] 和一个整数 M 为参数并返回一个大小为 M 的数组，其中第 i
// 个元素的值为整数 i 在参数数组中出现的次数。
// ?? 如果 a[] 中的值均在 0 到
// M-1，返回数组中所有元素之和应该和 a.length 相等
#include <iostream>
#include <vector>
using namespace std;

auto histogram(vector<int> a, const int M) -> vector<int> {
  vector<int> res(M);
  for (int i = 0; i < a.size(); ++i) {
    res[a[i]]++;
  }
  return res;
}

int main() {
  vector<int> a = {2, 3, 2, 4, 5, 4, 4, 3, 2};
  int M = 5;
  vector<int> b = histogram(a, M);
  for (auto v : b) {
    cout << v << endl;
  }
}