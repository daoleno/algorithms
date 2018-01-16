#include <iostream>
#include <string>
using namespace std;

// slow version
long fibonacci(int N) {
  if (N == 0)
    return 0;
  if (N == 1)
    return 1;
  return fibonacci(N - 1) + fibonacci(N - 2);
}

int main() {
  int res;
  for (int N = 0; N < 100; N++) {
    cout << N << " " << fibonacci(N) << endl;;
  }
  return 0;
}