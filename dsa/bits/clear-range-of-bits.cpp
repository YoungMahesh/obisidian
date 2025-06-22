#include <iostream>
using namespace std;


int clearRangeOfBits1(int num, int left, int right) {

	int all1s = -1;
	
	// left mask - 1s from start to until left-1, remaining 0s -> 11111111111000000000000
	// here left is index of bit from rightmost bit, so we will shift bits to left by left+1 (1 if left == 0, 2 if left == 1)
	int leftMask = all1s << left+1;

	// right mask - 1s from start until right, remaining 0s -> 000000000000000000000000011
	// here right represents the index of right-edge of section from righmost bit
	// we will use 2 steps:
	// 1. create rightMask0, by shifting 1s up until right: 1111111111111111111111111111100
	// 2. inverse rightMask0 to get rightMask: 000000000000000000000000000000011
	int rightMask0 = all1s << right;
	int rightMask = ~rightMask0;

	// create mask by merging left and right mask
	// 111111111111111111000000000000000000011
	int mask = leftMask | rightMask;


	// apply mask to number to clear bits
	return num & mask;
}

int clearRangeOfBits2(int num, int left, int right) {
	int all1s = -1;
	// left mask is 1s from start to left-1, remaining 0s -> 11111111111000000000000
	// here left is index of bit from rightmost bit, so we will shift bits of all1s to left by left+1 (1 if left == 0, 2 if left == 1)
	int leftMask = all1s << left+1;

	// rightMask is 1s from start to right, remaining 0s -> 000000000000000000000000011
	// here right represents the index of right-edge of section from righmost bit
	// if i is index of a bit from rightmost bit, considering all other bits are 0s, then just reducing 1 from than integer will make 
	// 	i) bit at 1 to 0  ii) all bits to the right of that to index(i) to 1
	// if we want to make bits starting from right+1 to 0 to 1, can create integer at 2^right-index - 1
	int rightMask = (1 << right) - 1;

	// create mask by merging left and right mask
	// 111111111111111111000000000000000000011
	int mask = leftMask | rightMask;

	// apply mask to number to clear bits
	return num & mask;
}

int main() {

	/* 			8421
	 *  15  1111
	 *
	 *  num    left   right   result    resultNum
	 *  15		  2				1			1001				9
	 *  15			3				1			0001				1
	 *  15			1				0			1100				12
	 *  15			3				0			0000				0
	 *  15			4				2			0011				3
	 * */


	int num = 15;
	int leftPositions[5] = {2,3,1,3,4};
	int rightPositions[5] = {1,1,0,0,2};
	int expected[5] = {9,1,12,0,3};

	for(int i=0; i<5; i++) {
		int result = clearRangeOfBits2(num, leftPositions[i], rightPositions[i]);
		if(result == expected[i])	cout << "true,";
		else cout << "false,";
	}
	
	return 0;
}
