#include <vector>
using namespace std;

// https://leetcode.com/problems/can-place-flowers/
class Solution {
public:
  bool canPlaceFlowers(vector<int> &flowerbed, int n) {
    // 1. put flowers at empty place by following no-adjacent-flowers rule until n(extra-flowers) becomes 0

    // first place
    if ((flowerbed.size() == 1 && flowerbed[0] == 0) || (flowerbed.size() > 1 && flowerbed[0] == 0 && flowerbed[1] == 0)) {
      flowerbed[0] = 1;
      n -= 1;
    }

    // middle places
    for (int i = 1; i < flowerbed.size() - 1; i++) {
      if (n <= 0)
        return true;
      if (flowerbed[i - 1] == 0 && flowerbed[i] == 0 && flowerbed[i + 1] == 0) {
        flowerbed[i] = 1;
        n -= 1;
      }
    }

    // last place
    int lastIdx = flowerbed.size() - 1;
    if (lastIdx >= 1 && flowerbed[lastIdx - 1] == 0 && flowerbed[lastIdx] == 0) {
      flowerbed[lastIdx] = 1;
      n -= 1;
    }

    return n <= 0;
  }
};
