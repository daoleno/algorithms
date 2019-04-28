#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// union find
class UF {
public:
  UF(int N) : cnt(N) {
    id.resize(N);
    sz.resize(N);
    for (int i = 0; i < N; ++i) {
      id[i] = i;
      sz[i] = 1;
    }
  }
  int count() { return cnt; }
  bool connected(int p, int q) { return find(p) == find(q); }

  // // quick-find version
  // int find(int p) { return id[p]; }
  // void slowUnion(int p, int q) {
  //   int pID = find(p);
  //   int qID = find(q);
  //   // p 和 q 处在相同的分量之中
  //   if (qID == pID)
  //     return;
  //   // 将 p 的分量重命名为 q 的名称
  //   for (int i; i < id.size(); ++i) {
  //     if (id[i] == pID) {
  //       id[i] = qID;
  //     }
  //   }
  //   cnt--;
  // }

  // quick-union version
  int find(int p) {
    // 跟踪链接
    while (p != id[p]) {
      p = id[p];
    }
    return p;
  }
  // void quickUnion(int p, int q) {
  //   int pRoot = find(p);
  //   int qRoot = find(q);
  //   if (pRoot == qRoot)
  //     return;
  //   id[pRoot] = qRoot;
  //   cnt--;
  // }

  void weightedQuickUnion(int p, int q) {
    int pRoot = find(p);
    int qRoot = find(q);
    if (pRoot == qRoot)
      return;
    // 将小树根节点连接到大树根节点
    if (sz[pRoot] < sz[qRoot]) {
      id[pRoot] = qRoot;
      sz[qRoot] += sz[pRoot];
    } else {
      id[qRoot] = pRoot;
      sz[pRoot] += sz[qRoot];
    }
    cnt--;
  }

private:
  vector<int> id; // 父链接数组(quick union)
  vector<int> sz; // 各个节点对应的分量的大小
  int cnt;        // 连通分量的数量
};

// usage: ./uf < data/tinyUF.txt
int main() {
  int N;
  cin >> N;
  UF uf(N);

  int p, q;
  while (cin >> p >> q) {
    if (uf.connected(p, q))
      continue;
    uf.weightedQuickUnion(p, q);
    cout << p << " " << q << endl;
  }

  cout << uf.count() << " components" << endl;

  return 0;
}
