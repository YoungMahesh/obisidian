#include <vector>
using namespace std;

// https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/
class Solution {
public:
  vector<bool> kidsWithCandies(vector<int> &candies, int extraCandies) {

    // 1. note down highest number candies any single kid have
    int highestCandies = 0;
    for (int i = 0; i < candies.size(); i++) {
      if (candies[i] > highestCandies)
        highestCandies = candies[i];
    }

    // 2. iterate through array, give extraCandies to each kid and check if sum >= highest-number-candies, note down true else false
    vector<bool> possibilities(candies.size(), false);
    for (int i = 0; i < candies.size(); i++) {
      if (candies[i] + extraCandies >= highestCandies)
        possibilities[i] = true;
    }

    return possibilities;
  }
};

int main() {
  Solution solution;
}
