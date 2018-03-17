#include <algorithm>
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

class Merge {
public:
  void sort(vector<string> &a) { sort(a, 0, a.size() - 1); }

  void show(vector<string> a) {
    for (auto i : a) {
      cout << i << " ";
    }
    cout << endl;
  }

private:
  // vector<string> aux;
  bool less(string i, string j) { return i < j; }
  void merge(vector<string> &a, int lo, int mid, int hi) {
    // 将 a[lo..mid] 和 a[mid+1..hi] 归并
    int i = lo, j = mid + 1;
    vector<string> aux(a);

    // 从辅助数组 aux 向 结果数组 a 中放数据
    for (int k = lo; k <= hi; ++k) {
      if (i > mid) {
        // 左半边用尽（取右边的元素）
        a[k] = aux[j++];
      } else if (j > hi) {
        // 右半边用尽（取左边的元素）
        a[k] = aux[i++];
      } else if (less(aux[j], aux[i])) {
        // 右半边的当前元素小于左半边的当前元素（取右边的元素）
        a[k] = aux[j++];
      } else {
        // 左半边的当前元素小于右半边的当前元素（取左边的元素）
        a[k] = aux[i++];
      }
    }
  }
  void sort(vector<string> &a, int lo, int hi) {
    if (hi <= lo)
      return;
    int mid = lo + (hi - lo) / 2;
    // 将左半边排序
    sort(a, lo, mid);
    // 将右半边排序
    sort(a, mid + 1, hi);
    // 归并结果
    merge(a, lo, mid, hi);
  }
};

class MergeBU {
public:
  void sort(vector<string> &a) {
    int N = a.size();
    // sz 子数组大小
    for (int sz = 1; sz < N; sz = sz + sz) {
      // lo 子数组索引
      for (int lo = 0; lo < N - sz; lo += sz + sz) {
        merge(a, lo, lo + sz - 1, min(lo + sz + sz - 1, N - 1));
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
  void merge(vector<string> &a, int lo, int mid, int hi) {
    // 将 a[lo..mid] 和 a[mid+1..hi] 归并
    int i = lo, j = mid + 1;
    // 每次都会创建辅助vector，可以设为成员变量以提高性能
    vector<string> aux(a);

    // 从辅助数组 aux 向 结果数组 a 中放数据
    for (int k = lo; k <= hi; ++k) {
      if (i > mid) {
        // 左半边用尽（取右边的元素）
        a[k] = aux[j++];
      } else if (j > hi) {
        // 右半边用尽（取左边的元素）
        a[k] = aux[i++];
      } else if (less(aux[j], aux[i])) {
        // 右半边的当前元素小于左半边的当前元素（取右边的元素）
        a[k] = aux[j++];
      } else {
        // 左半边的当前元素小于右半边的当前元素（取左边的元素）
        a[k] = aux[i++];
      }
    }
  }
};

class Quick {
public:
  void sort(vector<string> &a) {
    // 消除对输入的依赖（利于预测算法的运行实践）
    random_shuffle(a.begin(), a.end());
    sort(a, 0, a.size() - 1);
  }

  void show(vector<string> a) {
    for (auto i : a) {
      cout << i << " ";
    }
    cout << endl;
  }

private:
  void sort(vector<string> &a, int lo, int hi) {
    // Method 1
    // if (hi <= lo) {
    //   return;
    // }
    
    // Method 2
    // 对于小数组，切换成插入排序
    Insertion ins;
    // 转换参数 M 的最佳值和系统相关。建议：5 ~ 15
    int M = 7;
    if (hi <= lo + M) {
      ins.sort(a);
      return;
    }
    int j = partition(a, lo, hi);
    // 将左半部分 a[lo .. j-1] 排序
    sort(a, lo, j - 1);
    // 将右半部分 a[j+1 .. hi] 排序
    sort(a, j + 1, hi);
  }
  int partition(vector<string> &a, int lo, int hi) {
    // 左右扫描指针
    int i = lo, j = hi + 1;
    // 切分元素
    string v = a[lo];
    while (true) {
      // 扫描左右，检查扫描是否结束并交换元素
      while (less(a[++i], v)) {
        if (i == hi)
          break;
      }
      while (less(v, a[--j])) {
        if (j == lo)
          break;
      }
      if (i >= j) {
        break;
      }
      exch(a, i, j);
    }
    exch(a, lo, j);
    return j;
  }
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
  // Shell s;
  // Merge s;
  // MergeBU s;
  Quick s;
  s.sort(vec);
  s.show(vec);

  return 0;
}
