#include <iostream>
using namespace std;


int clearLastIBits(int num, int i) {
	// get a integer whose all bits are 1, -1 or ~0 have all bits 1 
	int num1 = -1;

	// shift num1 to left by i, so we can clear out last i digits
	// now, we have a mask whose last i digits are 0 and remaining digits 1
	int mask = (num1 << i);

	// now, making &mask to num, will retain 1s and 0s on left-side, but clear last i digits as mask have last i digits with value 0
	return num & mask;
}

int main() {

	/*     		16 8 4 2 1
	 * 15 			 1 1 1 1 
	 * 
	 * num		lastI			result
	 * 15				1					14
	 * 15				2					12
	 * 15				3					8
	 * 15				4					0
	 * 15				5					0 
	 * */

	int num = 15;
	int counts[5] = {1,2,3,4,5};
	int expected[5] = {14, 12, 8, 0, 0};

	for(int i=0; i<5; i++) {
		int result = clearLastIBits(num, counts[i]);
		if(result == expected[i])	cout << "true,";
		else cout << "false,";
	}

	return 0;
}
