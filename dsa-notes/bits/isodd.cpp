#include<iostream>
using namespace std;

// cin = character in, cout = character out
int main(){
	int x;
	cin >> x; 

	// when we use & with any number e.g. 11111011&00000001 => 1, all digit positions except rightmost becomes 0 because 0&1=00, 0&0==0
	// every odd number binary representation have, 1 at the rightmost position, and every even number have 0
	// hence odd-number&1 == 1, even-number&1 == 0
	if(x&1) {
		cout << "Odd";
	} else  {
		cout << "Even";
	}

	return 0;
}
