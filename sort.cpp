#include <iostream>
#include <string>
#include <vector>

// usage: ./sort < data/tiny.txt
//        ./sort < data/words3.txt

using namespace std;

class Selection {
public:
  void sort(vector<string> &a) {
    for (int i = 0; i < a.size(); ++i) {
      int min = i;
      // 选择最小的元素
      for (int j = i + 1; j < a.size(); ++j) {
        if (less(a[j], a[min])) {
          min = j;
        }
      }
      exch(a, i, min);
    }
  }
  void show(vector<string> a) {
    for (auto i : a) {
      cout << i << " ";
    }
    cout << endl;
  }

private:
  bool less(string i, string j) { return i < j; }
  void exch(vector<string> &a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
  }
};

class Insertion {
public:
  void sort(vector<string> &a) {
    for (int i = 0; i < a.size(); ++i) {
      // 向左遍历，遇到大的交换，小的退出
      for (int j = i; j > 0; --j) {
        if (less(a[j], a[j - 1])) {
          exch(a, j, j - 1);
        } else {
          break;
        }
      }
    }
  }
  void show(vector<string> a) {
    for (auto i : a) {
      cout << i << " ";
    }
    cout << endl;
  }

private:
  bool less(string i, string j) { return i < j; }
  void exch(vector<string> &a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
  }
};

class Shell {
public:
  void sort(vector<string> &a) {
    // 间隔为 h 的数组元素是有序的
    int h = 1;
    int len = a.size();
    while (h < len / 3) {
      // 1, 4, 13, 40, 121 ...
      h = 3 * h + 1;
    }
    while (h >= 1) {
      // 将数组变为 h 有序
      for (int i = h; i < len; ++i) {
        // 建立间隔为 i 的递增序列
        for (int j = i; j > 0; j -= h) {
          if (less(a[j], a[j - h])) {
            exch(a, j, j - h);
          } else {
            break;
          }
        }
      }
      h = h / 3;
    }
  }
  void show(vector<string> a) {
    for (auto i : a) {
      cout << i << " ";
    }
    cout << endl;
  }

private:
  bool less(string i, string j) { return i < j; }
  void exch(vector<string> &a, int i, int j) {
    string temp = a[i];
    a[i] = a[j];
    a[j] = temp;
  }
};

int main() {
  vector<string> vec;
  string buf;
  while (cin >> buf) {
    vec.push_back(buf);
  }

  // Selection s;
  // Insertion s;
  Shell s;
  s.sort(vec);
  s.show(vec);

  return 0;
}
