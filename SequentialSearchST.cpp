
//  Symbol table implementation with sequential search in an
//  unordered linked list of key-value pairs.

// usage: ./SequentialSearchST < tiny.txt
// L 11
// P 10
// M 9
// X 7
// H 5
// C 4
// R 3
// A 8
// E 12
// // S 0

// ! too dirty
// TODO: refactory

#include <deque>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

using namespace std;

class SequentialSearchST {
 private:
  // a helper linked list data type
  class Node {
   public:
    Node(string k, int v, Node *n) : key(k), val(v), next(n) {}

    //  private:
    string key;
    int val;
    Node *next;
  };

 private:
  int n;                  // number of key-value pairs
  Node *first = nullptr;  // the linked list of key-value pairs
 private:
  // delete key in linked list beginning at Node x
  // warning: function call stack too large if table is large
  Node *deleteLList(Node *x, string key) {
    if (x == nullptr) {
      return nullptr;
    }
    if (key == x->key) {
      n--;
      return x->next;
    }
    x->next = deleteLList(x->next, key);
    return x;
  }

 public:
  //  Initializes an empty symbol table.
  SequentialSearchST() {}
  ~SequentialSearchST() {
    if (first != nullptr) {
      delete first;
    }
  }

  int size() { return n; }

  bool isEmpty() { return size() == 0; }

  // Returns true if this symbol table contains the specified key.
  bool contains(string key) {
    if (key.empty()) {
      throw std::invalid_argument("argument to contains() is null");
    }
    return get(key) != 0;
  }

  // Returns the value associated with the given key in this symbol table.
  int get(string key) {
    if (key.empty()) {
      throw std::invalid_argument("argument to get() is null");
    }
    for (Node *x = first; x != nullptr; x = x->next) {
      if (key == x->key) {
        return x->val;
      }
    }
    return 0;
  }

  // Inserts the specified key-value pair into the symbol table, overwriting the
  // old value with the new value if the symbol table already contains the
  // specified key. Deletes the specified key (and its associated value) from
  // this symbol table if the specified value is 0.
  void put(string key, int val) {
    if (key.empty()) {
      throw std::invalid_argument("argument to put() is null");
    }
    // val 为 0，删除键值
    if (val == 0) {
      deleteLList(key);
      return;
    }
    for (Node *x = first; x != nullptr; x = x->next) {
      if (key == x->key) {
        x->val = val;
        return;
      }
    }
    // ! Attention
    first = new Node(key, val, first);
    n++;
  }

  void deleteLList(string key) {
    if (key.empty()) {
      throw std::invalid_argument("argument to delete() is null");
    }
    first = deleteLList(first, key);
  }

  // Returns all keys in the symbol table as an Iterable.
  // To iterate over all of the keys in the symbol table named st,
  // use the foreach notation.
  auto keys() {
    deque<string> keys;
    for (Node *x = first; x != nullptr; x = x->next) {
      keys.push_back(x->key);
    }
    return keys;
  }
};

int main() {
  SequentialSearchST st;
  string key;
  for (int i = 0; cin >> key; ++i) {
    st.put(key, i);
  }
  for (auto s : st.keys()) {
    cout << s << " " << st.get(s) << endl;
  }
  return 0;
}