#include <iostream>
using namespace std;


int replaceBits(int a, int b, int leftIdx, int rightIdx) {

	// we can replace bits of a from leftIdx to rightIdx with bits of b, with following steps:
	// 1. create mask which have bits of b
	// 	i) shift bits of b by rightIdx
	// 2. apply that mask with OR on a
	
	int mask = b << rightIdx;
	cout << "mask: " << mask << endl;

	return (a | mask);
}

int main() {

	/* 			 64 32 16 8 4 2 1			values
	 * 32		 0	 1  0 0 0 0 0			bits
	 * 					 5  4 3 2 1	0			indices
	 *
	 * numA   numB  	   a         b       left      right 	    result         resultNum
	 *  32  	 5	     100000     101       2          0   	    100101             37
	 *  32  	 5	     100000     101       3          1   	    101010             42
	 *  32  	 5	     100000     101       4          2   	    110100             52
	 *  32  	 5	     100000     101       5          3   	    101000             40
	 *  32  	 5	     100000     101       6          4   	   1010100             80
	 * */

	int numA = 32;
	int numB = 5;
	int leftIndices[5] = {2,3,4,5,6};
	int rightIndices[5] = {0,1,2,3,4};
	int expected[5] = {37,42,52,40,80};

	for(int i=0; i<5; i++) {
		int result = replaceBits(numA, numB, leftIndices[i], rightIndices[i]);
		if(result == expected[i]) cout << "true,";
		else cout << "false,";
	}

	return 0;
}
