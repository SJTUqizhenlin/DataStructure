#include <iostream>
#include "HPint.h"

int main()
{
	HPint a, b;
	cin >> a >> b; // for "subtract", a should be greator or equal to b
	cout << a << endl;
	cout << b << endl;
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << a % b << endl;
	return 0;
}