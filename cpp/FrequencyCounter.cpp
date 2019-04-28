
/* Read in a list of words from standard input and print out
the most frequently occurring word that has length greater than
a given threshold.

% ./FrequencyCounter 1 < tinyTale.txt
it 10

% ./FrequencyCounter 8 < tale.txt
business 122

% ./FrequencyCounter 10 < leipzig1M.txt`
government 24763 */

/* Reads in a command-line integer and sequence of words from
standard input and prints out a word (whose length exceeds
the threshold) that occurs most frequently to standard output.
It also prints out the number of words whose length exceeds
the threshold and the number of distinct such words. */

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  int distinct = 0, words = 0;
  string threshold = argv[1];
  int minlen = stoi(threshold);

  ST<string, int> st;

  // compute frequency counts
  string key;
  while (cin >> key) {
    if (key.length() < minlen)
      continue;
    words++;
    if (st.contains(key)) {
      st.put(key, st.get(key) + 1);
    } else {
      st.put(key, 1);
      distinct++;
    }
  }

  // find a key with the highest frequency count
  string max = "";
  st.put(max, 0);
  for (auto word : st.keys()) {
    if (st.get(word) > st.get(max))
      max = word;
  }

  cout << max << " " << st.get(max)) << endl;
  cout << "distinct = " << distinct << endl;
  cout << "words    = " << words << endl;
}