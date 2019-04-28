#include <iostream>
#include <string>
using namespace std;

// slow version
// long fibonacci(int N) {
//   if (N == 0)
//     return 0;
//   if (N == 1)
//     return 1;
//   return fibonacci(N - 1) + fibonacci(N - 2);
// }

// fast version
long fibonacci(int N) {
  if (N == 0)
    return 0;
  if (N == 1)
    return 1;
  // save computed values
  long calculated[N];
  calculated[0] = 0;
  calculated[1] = 1;
  for (int i = 2; i <= N; ++i) {
    calculated[i] = calculated[i - 1] + calculated[i - 2];
  }
  return calculated[N];
}

int main() {
  for (int N = 0; N < 100; N++) {
    cout << N << " " << fibonacci(N) << endl;
  }
  return 0;
}