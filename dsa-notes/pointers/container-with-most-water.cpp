#include <vector>
using namespace std;

// https://leetcode.com/problems/container-with-most-water
class Solution {
public:
  int maxArea(vector<int> &height) {
    int maxCapacity = 0;

    int leftIdx = 0;
    int rightIdx = height.size() - 1;

		while (leftIdx < rightIdx) {
			int leftHeight = height[leftIdx];
			int rightHeight = height[rightIdx];
			int minHeight = min(leftHeight, rightHeight);
			int currCapacity = minHeight * (rightIdx - leftIdx);
			maxCapacity = max(maxCapacity, currCapacity);
			if(leftHeight < rightHeight) {
				leftIdx += 1;
			} else if(rightHeight < leftHeight) {
				rightIdx -= 1;
			} else {
				leftIdx += 1;
				rightIdx -= 1;
			}
		}

    return maxCapacity;
  }
};
