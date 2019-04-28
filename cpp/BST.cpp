// usage:
// ./BST < tinyST.txt
// A 8
// C 4
// E 12
// H 5
// L 11
// M 9
// P 10
// R 3
// S 0
// X 7
#include <deque>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class BST {
 private:
  class Node {
   public:
    Node(string k, int v, int n) : key(k), val(v), N(n) {}
    string key;
    int val;
    // 指向子树的链接
    Node *left, *right;
    // 以该结点为根的子树中的结点总数
    int N;
  };

 public:
  ~BST() { delete root; }

 public:
  int size() { return size(root); }
  int get(string key) { return get(root, key); }
  void put(string key, int val) { put(root, key, val); }
  string min() { return min(root)->key; }
  string max() { return max(root)->key; }
  // 向上取整
  string floor(string key) {
    Node *x = floor(root, key);
    if (x == nullptr) {
      return "";
    }
    return x->key;
  }
  // 向下取整
  string ceiling(string key) {
    Node *x = ceiling(root, key);
    if (x == nullptr) {
      return "";
    }
    return x->key;
  }
  // 返回排名为 k 的结点
  string select(int k) { return select(root, k)->key; }
  int rank(string key) { return rank(key, root); }
  void deleteMin() { root = deleteMin(root); }
  void deleteNode(string key) { root = deleteNode(root, key); }
  deque<string> keys() { return keys(min(), max()); }
  deque<string> keys(string lo, string hi) {
    deque<string> que;
    keys(root, que, lo, hi);
    return que;
  }

 private:
  int size(Node *x) {
    if (x == nullptr) {
      return 0;
    } else {
      return x->N;
    }
  }
  // 在以 x 为根节点的子树中查找并返回 key 所对应的值
  // 如果找不到则返回 0;
  int get(Node *x, string key) {
    if (x == nullptr) {
      return 0;
    }
    if (key < x->key) {
      return get(x->left, key);
    } else if (key > x->key) {
      return get(x->right, key);
    } else {
      return x->val;
    }
  }
  // 如果 key 存在于以 x 为根节点的子树中则更新它的值
  // 否则将 (key, val) 键值对插入到该子树中
  Node *put(Node *x, string key, int val) {
    if (x == nullptr) {
      return new Node(key, val, 1);
    }
    if (key < x->key) {
      x->left = put(x->left, key, val);
    } else if (key > x->key) {
      x->right = put(x->right, key, val);
    } else {
      x->val = val;
    }
    x->N = size(x->left) + size(x->right) + 1;
    return x;
  }
  Node *min(Node *x) {
    if (x->left == nullptr) {
      return x;
    }
    return min(x->left);
  }
  Node *max(Node *x) {
    if (x->right == nullptr) {
      return x;
    }
    return max(x->right);
  }
  Node *floor(Node *x, string key) {
    if (x == nullptr) {
      return nullptr;
    }
    if (key == x->key) {
      return x;
    }
    if (key < x->key) {
      return floor(x->left, key);
    }
    // floor(key) `可能` 存在于右子树中
    Node *t = floor(x->right, key);
    if (t != nullptr) {
      return t;
    } else {
      return x;
    }
  }
  Node *ceiling(Node *x, string key) {
    if (x == nullptr) {
      return nullptr;
    }
    if (key == x->key) {
      return x;
    }
    if (key > x->key) {
      return ceiling(x->right, key);
    }
    // floor(key) `可能` 存在于左子树中
    Node *t = ceiling(x->left, key);
    if (t != nullptr) {
      return t;
    } else {
      return x;
    }
  }
  Node *select(Node *x, int k) {
    if (x == nullptr) {
      return select(x->left, k);
    }
    int t = size(x->left);
    if (t > k) {
      return select(x->left, k);
    } else if (t < k) {
      return select(x->right, k - t - 1);
    } else {
      return x;
    }
  }
  // 返回以 x 为根节点的子树中小于 x.key 的键的数量
  int rank(string key, Node *x) {
    if (x == nullptr) {
      return 0;
    }
    if (key < x->key) {
      return rank(key, x->left);
    } else if (key > x->key) {
      return 1 + size(x->left) + rank(key, x->right);
    } else {
      return size(x->left);
    }
  }
  Node *deleteMin(Node *x) {
    if (x->left == nullptr) {
      return x->right;
    }
    x->left = deleteMin(x->left);
    x->N = size(x->left) + size(x->right) + 1;
    return x;
  }
  Node *deleteNode(Node *x, string key) {
    if (x == nullptr) {
      return nullptr;
    }
    if (key < x->key) {
      x->left = deleteNode(x->left, key);
    } else if (key > x->key) {
      x->right = deleteNode(x->right, key);
    } else {
      if (x->right == nullptr) {
        return x->left;
      }
      if (x->left == nullptr) {
        return x->right;
      }
      Node *t = x;
      x = min(t->right);
      x->right = deleteMin(t->right);
      x->left = t->left;
    }
    x->N = size(x->left) + size(x->right) + 1;
    return x;
  }
  void keys(Node *x, deque<string> &que, string lo, string hi) {
    if (x == nullptr) {
      return;
    }
    if (lo < x->key) {
      keys(x->left, que, lo, hi);
    }
    if (lo <= x->key && x->key <= hi) {
      que.push_back(x->key);
    }
    if (hi > x->key) {
      keys(x->right, que, lo, hi);
    }
  }

 private:
  // 二叉查找树的根节点
  Node *root = new Node("", 0, 0);
};

int main() {
  BST st;
  string key;
  for (int i = 0; cin >> key; ++i) {
    st.put(key, i);
  }
  for (auto s : st.keys()) {
    cout << s << " " << st.get(s) << endl;
  }
  return 0;
}