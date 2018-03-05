#include <iostream>
#include <vector>

using namespace std;

// union find
class UF {
public:
  UF(int N) : cnt(N) {
    for (int i = 0; i < N; ++i) {
      id[i] = i;
    }
  }
  int count() { return cnt; }
  bool connected(int p, int q) { return find(p) == find(q); }
  int find(int p) { return id[p]; }
  void slowUnion(int p, int q) {
    int pID = find(p);
    int qID = find(q);
    // p 和 q 处在相同的分量之中
    if (qID == pID)
      return;

    // 将 p 的分量重命名为 q 的名称
    for (int i; i < id.size(); ++i) {
      if (id[i] == pID) {
        id[i] = qID;
      }
    }
    cnt--;
  }

private:
  vector<int> id;
  int cnt;
};
