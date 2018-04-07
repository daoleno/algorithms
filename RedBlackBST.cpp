// ! This program have bug
// TODE: To be normal

#include <deque>
#include <iostream>
#include <string>

using namespace std;

class RedBlackBST {
 private:
  class Node {
   public:
    Node(string k, int v, int n, bool color)
        : key(k), val(v), N(n), color(color) {}
    string key;
    int val;
    Node *left, *right;
    // 这棵子树中的结点总数
    int N;
    bool color;
  };

 private:
  Node *root = new Node("", 0, 1, BLACK);
  enum Color { RED = true, BLACK = false };

 public:
  int size() { return size(root); }
  int get(string key) { return get(root, key); }

  void put(string key, int val) {
    put(root, key, val);
    root->color = BLACK;
  }
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
  void deleteMin() {
    // 如果根节点的两个子结点都为黑，设置根结点为红
    if (!isRed(root->left) && !isRed(root->right)) {
      root->color = RED;
    }
    root = deleteMin(root);
  }
  void deleteMax() {
    if (!isRed(root->left) && !isRed(root->right)) {
      root->color = RED;
    }
    root = deleteMax(root);
  }
  void deleteNode(string key) {
    if (!isRed(root->left) && !isRed(root->right)) {
      root->color = RED;
    }
    root = deleteNode(root, key);
  }
  deque<string> keys() { return keys(min(), max()); }
  deque<string> keys(string lo, string hi) {
    deque<string> que;
    keys(root, que, lo, hi);
    return que;
  }

 private:
  bool isRed(Node *x) {
    if (x == nullptr) {
      return false;
    }
    return x->color = RED;
  }
  Node *rotateLeft(Node *h) {
    Node *x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = 1 + size(h->left) + size(h->right);
    return x;
  }
  Node *rotateRight(Node *h) {
    Node *x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = 1 + size(h->left) + size(h->right);
    return x;
  }
  void flipColors(Node *h) {
    h->color = RED;
    h->left->color = BLACK;
    h->right->color = BLACK;
  }
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
  // 查找 key, 找到则更新其值，否则为它新建一个结点
  Node *put(Node *x, string key, int val) {
    if (x == nullptr) {
      // 标准的插入操作，和父结点用红链接相连
      return new Node(key, val, 1, RED);
    }
    if (key < x->key) {
      x->left = put(x->left, key, val);
    } else if (key > x->key) {
      x->right = put(x->right, key, val);
    } else {
      x->val = val;
    }

    if (isRed(x->right) && !isRed(x->left)) {
      x = rotateLeft(x);
    }
    if (isRed(x->left) && isRed(x->left->left)) {
      x = rotateRight(x);
    }
    if (isRed(x->left) && isRed(x->right)) {
      flipColors(x);
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
  Node *deleteMin(Node *h) {
    if (h->left == nullptr) {
      return nullptr;
    }
    if (!isRed(h->left) && !isRed(h->left->left)) {
      h = moveRedLeft(h);
    }
    h->left = deleteMin(h->left);
    return balance(h);
  }
  Node *deleteMax(Node *h) {
    if (isRed(h->left)) {
      h = rotateRight(h);
    }

    if (h->right == nullptr) {
      return nullptr;
    }

    if (!isRed(h->right) && !isRed(h->right->left)) {
      h = moveRedRight(h);
    }

    h->right = deleteMax(h->right);

    return balance(h);
  }
  Node *deleteNode(Node *x, string key) {
    if (x == nullptr) {
      return nullptr;
    }
    if (key < x->key) {
      if (!isRed(x->left) && !isRed(x->left->left)) {
        x = moveRedLeft(x);
        ;
      }
      x->left = deleteNode(x->left, key);
    } else {
      if (isRed(x->left)) {
        x = rotateRight(x);
      }
      if (key == x->key && x->right == nullptr) {
        return nullptr;
      }
      if (!isRed(x->right) && !isRed(x->right->left)) {
        x = moveRedRight(x);
      }
      if (key == x->key) {
        Node *x = min(x->right);
        x->key = x->key;
        x->val = x->val;
        x->right = deleteMin(x->right);
      } else {
        x->right = deleteNode(x->right, key);
      }
    }
    return balance(x);
  }
  Node *moveRedLeft(Node *x) {
    flipColors(x);
    if (isRed(x->right->left)) {
      x->right = rotateRight(x->right);
      x = rotateLeft(x);
      flipColors(x);
    }
    return x;
  }
  Node *moveRedRight(Node *x) {
    flipColors(x);
    if (isRed(x->left->left)) {
      x->right = rotateRight(x->right);
      x = rotateRight(x);
      flipColors(x);
    }
    return x;
  }
  Node *balance(Node *x) {
    if (isRed(x->right)) {
      x = rotateLeft(x);
    }
    if (isRed(x->left) && isRed(x->left->left)) {
      x = rotateRight(x);
    }
    if (isRed(x->left) && isRed(x->right)) {
      flipColors(x);
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
};

int main() {
  RedBlackBST st;
  string key;
  for (int i = 0; cin >> key; ++i) {
    st.put(key, i);
  }
  for (auto s : st.keys()) {
    cout << s << " " << st.get(s) << endl;
  }
  return 0;
}