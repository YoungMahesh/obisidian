#include <iostream>
using namespace std;

int getIthBit(int num, int i) {
	// create a integer who have 1 at ith position and zero at all other positions
	int mask = (1 << i); 

	// once we make num&mask, all other digits of the result except for ith position will become zero
	// now, if ith position have 1, the result will have 1 at ith postion else 0 at the ith position
	return (num & mask) > 0 ? 1 : 0;
}

int main() {
	int num = 5;
	int i;
	cin >> i;
	cout << getIthBit(num,i) << endl;

	return 0;
}
