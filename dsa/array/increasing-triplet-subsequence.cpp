#include <vector>
using namespace std;

// Hi Mr Van, I will deploy block-bonez staking to testnet on Monday and to mainnet on Tuesday

class Solution {
public:
  bool increasingTriplet(vector<int> &nums) {
    int count = 1;
    int currHighest = nums[0];

    vector<int> lowestUntil(nums.size(), 0);
    lowestUntil[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] < lowestUntil[i - 1]) {
        lowestUntil[i] = nums[i];
      } else {
        lowestUntil[i] = lowestUntil[i - 1];
      }
    }

    vector<int> highestUntil(nums.size(), 0);
    int lastIdx = nums.size() - 1;
    highestUntil[lastIdx] = nums[lastIdx];
    for (int i = lastIdx - 1; i >= 0; i--) {
      if (nums[i] > highestUntil[i + 1]) {
        highestUntil[i] = nums[i];
      } else {
        highestUntil[i] = highestUntil[i + 1];
      }
    }

    for (int i = 1; i < nums.size() - 1; i++) {
      if (nums[i] > lowestUntil[i - 1] && nums[i] < highestUntil[i + 1]) {
        return true;
      }
    }
    return false;
  }
};
