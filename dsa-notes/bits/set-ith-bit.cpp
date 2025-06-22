#include <iostream>
using namespace std;

int setIthBit(int num, int i) {
	int mask = (1 << i);

	return (num | mask);
}


int main() {


	/*      8421
	 *  5    101
	 *  4    100
	 *
	 * num    position    result
	 *  5       0     			5
	 *  5				1						7
	 *  5				2						5
	 *  5				3					 13
	 *  4				0						5
	 *  4				1						6
	 *  4				2						4
	 *  5				3 				 12
	 * */

	int nums[8] = {5,5,5,5,4,4,4,4};
	int positions[8]={0,1,2,3,0,1,2,3};
	int expected[8]={5,7,5,13,5,6,4,12};

	for(int i=0; i<8; i++) {
		int result = setIthBit(nums[i], positions[i]);
		if(result == expected[i]) {
			cout << "true,";
		}else {
			cout << "false,";
		}
	}
	return 0;
}
