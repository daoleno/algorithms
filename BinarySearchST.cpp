
// Symbol table implementation with binary search in an ordered array.

// usage: ./BinarySearchST < tinyST.txt
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
// ! bug 有重复的键值

#include <cassert>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class BinarySearchST {
 public:
  //  Initializes an empty symbol table.
  BinarySearchST() {
    keys.resize(1000);
    vals.resize(1000);
  }

  // Initializes an empty symbol table with the specified initial capacity.
  BinarySearchST(int capacity) {
    // keys.resize(capacity);
    // vals.resize(capacity);
  }

  int size() { return n; }
  int size(string lo, string hi) {
    if (lo.empty())
      throw std::invalid_argument("first argument to size() is null");
    if (hi.empty())
      throw std::invalid_argument("second argument to size() is null");

    if (lo > hi) return 0;
    if (contains(hi)) {
      return rank(hi) - rank(lo) + 1;
    } else {
      return rank(hi) - rank(lo);
    }
  }

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
    if (isEmpty()) return 0;
    int i = rank(key);
    if (i < n && keys[i] == key) {
      return vals[i];
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
      deleteItem(key);
      return;
    }

    int i = rank(key);

    cout << ">>>>>>>>>>>> key is already in table ~~~~~~~~~~ " << key;
    cout << ">>>>>>>>>>>>" << i << endl;
    // key is already in table
    if (i < n && keys[i] == key) {
      cout << "~~~~~~~~~~~~ key is already in table ~~~~~~~~~~ " << key << endl;
      cout << i << endl;

      vals[i] = val;
    }

    // insert new key-value pair
    // if (n == keys.size()) {
    //   resizeST(2 * keys.size());
    // }
    for (int j = n; j > i; j--) {
      keys[j] = keys[j - 1];
      vals[j] = vals[j - 1];
    }
    keys[i] = key;
    vals[i] = val;
    n++;

    assert(check());
  }

  // Removes the specified key and associated value from this symbol table (if
  // the key is in the symbol table)
  void deleteItem(string key) {
    if (key.empty()) {
      throw std::invalid_argument("argument to delete() is null");
    }
    if (isEmpty()) {
      return;
    }
    int i = rank(key);

    // key not in table;
    if (i == n || keys[i] != key) {
      return;
    }

    for (int j = i; j < n - 1; j++) {
      keys[j] = keys[j + 1];
      vals[j] = vals[j + 1];
    }
    n--;
    keys[n] = "";
    vals[n] = 0;

    // resize if 1/4 full
    // if (n > 0 && n < keys.size() / 4) {
    //   resizeST(keys.size() / 2);
    // }

    assert(check());
  }

  void deleteMin() {
    if (isEmpty()) {
      cerr << "Symbol table underflow error" << endl;
      exit(0);
    }
    deleteItem(min());
  }

  void deleteMax() {
    if (isEmpty()) {
      cerr << "Symbol table underflow error" << endl;
      exit(0);
    }
    deleteItem(max());
  }

  string min() {
    if (isEmpty()) {
      cerr << "called min() with empty symbol table" << endl;
      exit(0);
    }
    return keys[0];
  }
  string max() {
    if (isEmpty()) {
      cerr << "called max() with empty symbol table" << endl;
      exit(0);
    }
    return keys[n - 1];
  }

  // Return the kth smallest key in this symbol table.
  string select(int k) {
    if (k < 0 || k >= size()) {
      cerr << "called select() with invalid argument: " << k << endl;
      exit(0);
    }
    return keys[k];
  }
  // Returns the largest key in this symbol table less than or equal to key.
  string floor(string key) {
    if (key.empty()) {
      cerr << "argument to floor() is null" << key << endl;
    }
    int i = rank(key);
    if (i < n && keys[i] == key) {
      return keys[i];
    }
    if (i == 0) {
      return NULL;
    } else {
      return keys[i - 1];
    }
  }

  // Returns the smallest key in this symbol table greater than or equal to key.
  string ceiling(string key) {
    if (key.empty()) {
      cerr << "argument to ceiling() is null" << key << endl;
    }
    int i = rank(key);
    if (i == n) {
      return NULL;
    } else {
      return keys[i];
    }
  }

  //  Returns all keys in this symbol table as an Iterable.
  auto allKeys() { return allkeys(min(), max()); }

  deque<string> allkeys(string lo, string hi) {
    cout << "lo: " << lo << "  hi: " << hi << endl;
    if (lo.empty())
      throw std::invalid_argument("first argument to size() is null");
    if (hi.empty())
      throw std::invalid_argument("second argument to size() is null");

    deque<string> que;
    if (lo > hi) return que;
    for (int i = rank(lo); i < rank(hi); ++i) {
      que.push_back(keys[i]);
    }
    if (contains(hi)) {
      que.push_back(keys[rank(hi)]);
    }
    return que;
  }

 private:
  void resizeST(int capacity) {
    assert(capacity > n);
    keys.resize(capacity);
    vals.resize(capacity);
  }

  // Returns the number of keys in this symbol table strictly less than key
  int rank(string key) {
    if (key.empty()) {
      throw std::invalid_argument("argument to rank() is null");
    }

    int lo = 0, hi = n - 1;
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      if (key < keys[mid]) {
        hi = mid - 1;
      } else if (key > keys[mid]) {
        lo = mid + 1;
      } else {
        return mid;
      }
    }
    return lo;
  }

  bool check() { return isSorted() && rankCheck(); }

  // are the items in the array in ascending order?
  bool isSorted() {
    for (int i = 1; i < size(); i++) {
      if (keys[i] < keys[i - 1]) {
        return false;
      }
    }
    return true;
  }

  // check that rank(select(i)) = i
  bool rankCheck() {
    cout << "--------------" << endl;
    for (int i = 0; i < size(); i++) {
      cout << ">>>>>> " << endl;
      cout << ">>>>> rank >>>>> " << rank(select(i)) << endl;
      cout << ">>>>>   i  >>>>> " << i << endl;
      cout << ">>>>> select() >>>> " << select(i) << endl;
      if (i != rank(select(i))) {
        cerr << "fuck" << endl;
        return false;
      }
    }

    for (int i = 0; i < size(); i++) {
      if (keys[i] != select(rank(keys[i]))) {
        cerr << "suck:----" << endl;
        return false;
      }
    }
    return true;
  }

 public:
  // static int INIT_CAPACITY;

 private:
  vector<string> keys;
  vector<int> vals;
  int n = 0;
};
// int BinarySearchST::INIT_CAPACITY = 2;
int main() {
  BinarySearchST st;
  string key;
  for (int i = 0; cin >> key; ++i) {
    st.put(key, i);
  }
  cout << "###############################" << endl;
  for (auto s : st.allKeys()) {
    cout << s << " " << st.get(s) << endl;
  }
  return 0;
}