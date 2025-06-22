#include <iostream>
using namespace std;

int setIthBit(int num, int position) {
	int mask = (1 << position);
	return (num | mask);
}

int clearIthBit(int num, int position) {
	int mask = (1 << position);
	int mask2 = ~mask;
	return (num & mask2);
}

int main() {
	/* 				8421
	 * 5			0101
	 * 4			0100
	 *
	 * num		position		bit		 result
	 * 5			0						0				4
	 * 5			0						1				5
	 * 5			1						0				5
	 * 5			1						1				7
	 * 5			2						0				1
	 * 5			2						1				5
	 * 5			3						0				5
	 * 5			3						1			 13
	 * */

	int num = 5;
	int positions[8] = {0,0,1,1,2,2,3,3};
	int bits[8] = {0,1,0,1,0,1,0,1};
	int expected[8] = {4,5,5,7,1,5,5,13};

	for(int i=0; i<8; i++) {
		if(bits[i] == 1) {
			int result = setIthBit(num, positions[i]);
			if(result == expected[i]) cout << "true,";
			else cout << "false,";
		}else if(bits[i] == 0) {
			int result = clearIthBit(num, positions[i]);
			if (result == expected[i]) cout << "true,";
			else cout << "false,";
		} else {
			cout << "wrong number";
		}
	}
}
