
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
// S 0

template <typename Key, typename Value> class SequentialSearchST {

  /**
   * Initializes an empty symbol table.
   */
public:
  SequentialSearchST() {}

  int size() { return n; }

  bool isEmpty() { return size() == 0; }

  bool contains(Key key) {}

  Value get(Key key) {}
  void put(Key key, Value val) {
    if (key == null)
      throw new IllegalArgumentException("first argument to put() is null");
    if (val == null) {
      delete (key);
      return;
    }

    for (Node x = first; x != null; x = x.next) {
      if (key.equals(x.key)) {
        x.val = val;
        return;
      }
    }
    first = new Node(key, val, first);
    n++;
  }

  void delete (Key key) {}

  // delete key in linked list beginning at Node x
  // warning: function call stack too large if table is large
private:
  Node delete (Node x, Key key) {}

  // a helper linked list data type
private:
  class Node {

  public:
    Node(Key key, Value val, Node next) : key(key), val(val), next(next) {}

  private:
    Key key;
    Value val;
    Node next;
  };

private:
  int n;      // number of key-value pairs
  Node first; // the linked list of key-value pairs
};