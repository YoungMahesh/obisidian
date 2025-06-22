#include <string>
#include <vector>
using namespace std;

// https://leetcode.com/problems/reverse-words-in-a-string
class Solution {
public:
  string reverseWords(string s) {
    // 1. store all words in a vector
    vector<string> words;
    vector<char> currWord;
    for (char c : s) {
      if (c == ' ') { // we use '' for character and "" for string in cpp
        if (currWord.size() > 0) {
          string tempStr(currWord.begin(), currWord.end());
          words.push_back(tempStr);
          currWord = {};
        }
      } else {
        currWord.push_back(c);
      }
    }
    if (currWord.size() > 0) { // put last word to words-vector
      string tempStr(currWord.begin(), currWord.end());
      words.push_back(tempStr);
    }

    // 2. create a new string by putting words in reverse order
    vector<char> reverseChars;
    for (int i = words.size() - 1; i >= 0; i--) {
      for (int j = 0; j < words[i].size(); j++) {
        reverseChars.push_back(words[i][j]);
      }
      reverseChars.push_back(' '); // add space after every word;
    }
    reverseChars.pop_back(); // remove space after last word;

    string reverseStr(reverseChars.begin(), reverseChars.end());
    return reverseStr;
  }
};
