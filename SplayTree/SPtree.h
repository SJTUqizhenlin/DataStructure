#ifndef SPTREE_H
#define SPTREE_H

#include "SPnode.h"
#include <stack>
using namespace std;

class SPtree;

class SPtree
{
private:
	SPnode* Root;
	void rotate(SPnode* n);
	void splay(SPnode* n, SPnode* tar);
	SPnode* rootPred();
	SPnode* rootSucc();
	int cal_maxdepth(SPnode* root);
public:
	SPtree();
	SPnode* find(int key);
	void insert(int key);
	SPnode* findKth(int k);
	void Delete(int low, int high);
	void showAll();
	void showDep();
};

SPtree::SPtree()
{
	this->Root = nullptr;
}

void SPtree::rotate(SPnode* n)
{
	SPnode* grand = n->p->p;
	if (n->isRightKid())
	{
		n->p->linkTo(1, n->chd[0]);
		n->linkTo(0, n->p);
	}
	else
	{
		n->p->linkTo(0, n->chd[1]);
		n->linkTo(1, n->p);
	}
	n->p->update();
	if (grand != nullptr)
		grand->linkTo(grand->chd[1] == n->p, n);
	else
	{
		n->p = nullptr;
		this->Root = n;
	}
}

void SPtree::splay(SPnode* n, SPnode* tar)
{
	while (n->p != tar && n->p->p != tar)
	{
		if (n->isRightKid() == n->p->isRightKid())
		{
			rotate(n->p);
			rotate(n);
		}
		else
		{
			rotate(n);
			rotate(n);
		}
	}
	if (n->p != tar) rotate(n);
	n->update();
}

SPnode* SPtree::rootPred()
{
	SPnode* res = this->Root->chd[0];
	if (res == nullptr) return nullptr;
	while (res->chd[1] != nullptr)
		res = res->chd[1];
	splay(res, nullptr);
	return res;
}

SPnode* SPtree::rootSucc()
{
	SPnode* res = this->Root->chd[1];
	if (res == nullptr) return nullptr;
	while (res->chd[0] != nullptr)
		res = res->chd[0];
	splay(res, nullptr);
	return res;
}

SPnode* SPtree::find(int key)
{
	SPnode* res = this->Root;
	while (res != nullptr && res->key != key)
		res = res->chd[key > res->key];
	if (res != nullptr) splay(res, nullptr);
	return res;
}

void SPtree::insert(int key)
{
	if (find(key) != nullptr) return;
	if (this->Root == nullptr)
	{
		this->Root = new SPnode(key);
		return;
	}
	SPnode* n = this->Root;
	SPnode* n1 = nullptr;
	while (n != nullptr)
	{
		n1 = n;
		n = n->chd[key > n->key];
	}
	n = new SPnode(key);
	n1->linkTo(key > n1->key, n);
	splay(n, nullptr);
}

SPnode* SPtree::findKth(int k)
{
	if (this->Root == nullptr)
		return nullptr;
	SPnode* res = this->Root;
	while ((res->chd[0] ? res->chd[0]->size : 0) != k - 1)
	{
		if (res->chd[0] == nullptr)
		{
			k -= 1;
			res = res->chd[1];
		}
		else
		{
			if (res->chd[0]->size >= k) res = res->chd[0];
			else
			{
				k -= (res->chd[0]->size + 1);
				res = res->chd[1];
			}
		}
	}
	if (res != nullptr) splay(res, nullptr);
	return res;
}

void SPtree::Delete(int low, int high)
{
	if (find(low) == nullptr) insert(low);
	SPnode* pred = rootPred();
	if (find(high) == nullptr) insert(high);
	SPnode* succ = rootSucc();
	if (pred == nullptr && succ == nullptr)
	{
		this->Root = nullptr;
		return;
	}
	if (pred == nullptr)
	{
		this->Root->chd[0] = nullptr;
		this->Root->update();
		return;
	}
	if (succ == nullptr)
	{
		splay(pred, nullptr);
		this->Root->chd[1] = nullptr;
		this->Root->update();
		return;
	}
	splay(pred, succ);
	pred->chd[1] = nullptr;
	pred->update();
	succ->update();
}

void SPtree::showAll()
{
	cout << "now elements are:\n";
	if (this->Root == nullptr) return;
	stack<SPnode*> st;
	SPnode* cur = this->Root;
	while (true)
	{
		if (cur != nullptr)
		{
			st.push(cur);
			cur = cur->chd[0];
		}
		else
		{
			cur = st.top();
			cout << cur->key << " ";
			st.pop();
			cur = cur->chd[1];
		}
		if (cur == nullptr && st.empty())
		break;
	}
	cout << "\nmax depth is: " << cal_maxdepth(this->Root) << endl;
}

int SPtree::cal_maxdepth(SPnode* root)
{
	if (root == nullptr) return 0;
	int d1 = cal_maxdepth(root->chd[0]);
	int d2 = cal_maxdepth(root->chd[1]);
	int res = (d1 > d2 ? d1 : d2) + 1;
	return res;
}

void SPtree::showDep()
{
	cout << "max depth is: " << cal_maxdepth(this->Root) << endl;
}



#endif // !SPTREE_H
