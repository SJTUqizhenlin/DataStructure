#include <iostream>
#include "SPtree.h"

using namespace std;

int main()
{
	SPtree T;
	for (int i = 1000; i < 2000; i++)
		T.insert(i);
	T.showDep();

	//for (int i = 1000; i < 1100; i++)
	//{
	//	T.Delete(i, i);
	//	T.showDep();
	//}

	//T.Delete(1000, 1100);
	//T.showDep();



	//for (int i = 1010; i > 1000; i--)
	//	T.find(i);
	//T.showDep();

	for (int i = 1000; i < 1010; i++)
		T.find(i);
	T.showDep();

	return 0;
}