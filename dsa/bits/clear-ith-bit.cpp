#include <iostream>
using namespace std;

int clearIthBit(int num, int i) {

	// create 1 at ith position
	int mask = (1 << i);

	// inverse all digits of mask, so we can retain 1s while applying mask with &, except for ith position
	int mask2 = ~mask;

	// apply &mask2 where all digits are 1 except for ith position
	return num & mask2;
}

int main() {

	/* num    i     result
	 *  5     0      4
	 *  5     1      5
	 *  5     2      1
	 *  5     3      5
	 *  4     0      4
	 *  4     1      4
	 *  4     2      0
	 *  4     3      4
	 */


	int nums[8] = {5, 5, 5, 5, 4, 4, 4, 4};
	int positions[8] = {0,1,2,3,0,1,2,3};
	int expected[8] = {4,5,1,5,4,4,0,4};

	for(int i=0; i<8; i++) {
		int result = clearIthBit(nums[i], positions[i]);
		if (result == expected[i]) {
			cout << "true,";
		} else {
			cout << "false,";
		}
	}


	return 0;
}






