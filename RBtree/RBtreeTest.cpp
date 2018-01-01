#include <iostream>
#include <string>
#include "RBtree.h"

using namespace std;

int main()
{
	RBtree T;
	string s = "qizhenlin";
	for (int i = 1; i < 1000; i++)
		T.Ins_kv(i, s);
	T.Show_All();
	for (int i = 301; i < 700; i++)
		T.Del_k(i);
	T.Show_All();
	for (int i = 200; i < 400; i++)
	{
		RBtreeNode* f = T.Find(i);
		if (f != nullptr) cout << f->val << " ";
		else cout << "NOT FOUND!" << " ";
	}
	cout << endl;
	return 0;
}