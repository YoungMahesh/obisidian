#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

vector<char> findCommonChars(vector<string> &words) {

  unordered_set<char> commonChars(words[0].begin(), words[0].end());

  for (int i = 0; i < words.size(); i++) {
    unordered_set<char> currentChars;

    for (char letter1 : words[i]) {
      if (commonChars.count(letter1) > 0) {
        currentChars.insert(letter1);
      }
    }
    commonChars = currentChars;
  }

  vector<char> result;
  for (char c : commonChars) {
    result.push_back(c);
  }
  return result;
}

int main() {
  vector<string> words = {"bella", "label", "roller"};
  vector<char> commonChars = findCommonChars(words);

  for (char c : commonChars) {
    cout << c << " ";
  }
  cout << endl;

  return 0;
}
