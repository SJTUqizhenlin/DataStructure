#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include "RBtreeNode.h"
#include <stack>
using namespace std;


class RBtree
{
private:
	RBtreeNode *NIL;
	RBtreeNode *Root;
	void RB_Fixup_ins(RBtreeNode*);
	void l_rot(RBtreeNode*);
	void r_rot(RBtreeNode*);
	void RB_transplant(RBtreeNode*, RBtreeNode*);
	RBtreeNode* Tree_min(RBtreeNode*);
	void RB_Fixup_del(RBtreeNode*);
	void Insert(RBtreeNode *x);
	void Delete(RBtreeNode *x);
	int cal_maxdepth(RBtreeNode*);
public:
	RBtree();
	RBtreeNode* Find(int key);
	void Ins_kv(int key, string val);
	void Del_k(int key);
	void Show_All();
};

RBtree::RBtree()
{
	this->NIL = new RBtreeNode(0, "", true);
	this->Root = nullptr;
}

void RBtree::Ins_kv(int key, string val)
{
	RBtreeNode* fd = this->Find(key);
	if (fd == nullptr)
	{
		RBtreeNode* nnode = new RBtreeNode(key, val, false);
		this->Insert(nnode);
	}
}
void RBtree::Del_k(int key)
{
	RBtreeNode* fd = this->Find(key);
	if (fd != nullptr)
		this->Delete(fd);
}

RBtreeNode* RBtree::Find(int key)
{
	if (this->Root == nullptr) return nullptr;
	RBtreeNode *x = this->Root;
	while (x != this->NIL)
	{
		if (key == x->key)
			return x;
		else
			x = (key < x->key) ? x->l : x->r;
	}
	return nullptr;
}

void RBtree::Insert(RBtreeNode *x)
{
	if (x->color == true) x->color = false;
	if (this->Root == nullptr)
	{
		this->Root = x;
		x->color = true;
		this->Root->p = this->NIL;
		this->Root->l = this->NIL;
		this->Root->r = this->NIL;
		return;
	}
	RBtreeNode *y = this->Root;
	RBtreeNode *z = nullptr;
	while (y != this->NIL)
	{
		z = y;
		y = (x->key < y->key) ? y->l : y->r;
	}
	if (x->key < z->key)
	{
		z->l = x;
		x->l = this->NIL;
		x->r = this->NIL;
		x->p = z;
	}
	else
	{
		z->r = x;
		x->l = this->NIL;
		x->r = this->NIL;
		x->p = z;
	}
	RB_Fixup_ins(x);
}

void RBtree::l_rot(RBtreeNode* n)
{
	if (n == this->Root)
	{
		RBtreeNode* y = n->r;
		n->r = y->l;
		y->l->p = n;
		this->Root = y;
		y->p = this->NIL;
		y->l = n;
		n->p = y;
	}
	else
	{
		RBtreeNode* y = n->r;
		n->r = y->l;
		y->l->p = n;
		if (n == n->p->l)
		{
			n->p->l = y;
			y->p = n->p;
		}
		else
		{
			n->p->r = y;
			y->p = n->p;
		}
		y->l = n;
		n->p = y;
	}
}

void RBtree::r_rot(RBtreeNode* n)
{
	if (n == this->Root)
	{
		RBtreeNode* y = n->l;
		n->l = y->r;
		y->r->p = n;
		this->Root = y;
		y->p = this->NIL;
		y->r = n;
		n->p = y;
	}
	else
	{
		RBtreeNode* y = n->l;
		n->l = y->r;
		y->r->p = n;
		if (n == n->p->l)
		{
			n->p->l = y;
			y->p = n->p;
		}
		else
		{
			n->p->r = y;
			y->p = n->p;
		}
		y->r = n;
		n->p = y;
	}
}

void RBtree::RB_Fixup_ins(RBtreeNode* x)
{
	while (x->p->color == false)
	{
		if (x->p == x->p->p->l)
		{
			RBtreeNode *w = x->p->p->r;
			if (w->color == false)
			{
				x->p->color = true;
				w->color = true;
				x->p->p->color = false;
				x = x->p->p;
			}
			else
			{
				if (x == x->p->r)
				{
					x = x->p;
					l_rot(x);
				}
				x->p->color = true;
				x->p->p->color = false;
				r_rot(x->p->p);
			}
		}
		else
		{
			RBtreeNode *w = x->p->p->l;
			if (w->color == false)
			{
				x->p->color = true;
				w->color = true;
				x->p->p->color = false;
				x = x->p->p;
			}
			else
			{
				if (x == x->p->l)
				{
					x = x->p;
					r_rot(x);
				}
				x->p->color = true;
				x->p->p->color = false;
				l_rot(x->p->p);
			}
		}
	}
	this->Root->color = true;
}

void RBtree::RB_transplant(RBtreeNode* u, RBtreeNode* v)
{
	if (u == this->Root)
	{
		this->Root = v;
		v->p = this->NIL;
	}
	else
	{
		if (u == u->p->l)
			u->p->l = v;
		else
			u->p->r = v;
		v->p = u->p;
	}
}

RBtreeNode* RBtree::Tree_min(RBtreeNode* n)
{
	RBtreeNode* cur = n;
	while (cur->l != this->NIL)
		cur = cur->l;
	return cur;
}

void RBtree::Delete(RBtreeNode* x)
{
	RBtreeNode* y = x;
	bool y_original_color = y->color;
	RBtreeNode* z = nullptr;
	if (x->l == this->NIL)
	{
		z = x->r;
		RB_transplant(x, x->r);
	}
	else
	{
		if (x->r == this->NIL)
		{
			z = x->l;
			RB_transplant(x, x->l);
		}
		else
		{
			y = Tree_min(x->r);
			y_original_color = y->color;
			z = y->r;
			if (y->p == x)
				z->p = y;
			else
			{
				RB_transplant(y, y->r);
				y->r = x->r;
				y->r->p = y;
			}
			RB_transplant(x, y);
			y->l = x->l;
			y->l->p = y;
			y->color = x->color;
		}
	}
	if (y_original_color == true)
		RB_Fixup_del(z);
}

void RBtree::RB_Fixup_del(RBtreeNode *n)
{
	while (n != this->Root && n->color == true)
	{
		if (n == n->p->l)
		{
			RBtreeNode* w = n->p->r;
			if (w->color == false)
			{
				w->color = true;
				n->p->color = false;
				l_rot(n->p);
				w = n->p->r;
			}
			if (w->l->color == true && w->r->color == true)
			{
				w->color = false;
				n = n->p;
			}
			else
			{
				if (w->r->color == true)
				{
					w->l->color = true;
					w->color = false;
					r_rot(w);
					w = n->p->r;
				}
				w->color = n->p->color;
				n->p->color = true;
				w->r->color = true;
				l_rot(n->p);
				n = this->Root;
			}
		}
		else
		{
			RBtreeNode* w = n->p->l;
			if (w->color == false)
			{
				w->color = true;
				n->p->color = false;
				r_rot(n->p);
				w = n->p->l;
			}
			if (w->l->color == true && w->r->color == true)
			{
				w->color = false;
				n = n->p;
			}
			else
			{
				if (w->l->color == true)
				{
					w->r->color = true;
					w->color = false;
					l_rot(w);
					w = n->p->l;
				}
				w->color = n->p->color;
				n->p->color = true;
				w->l->color = true;
				r_rot(n->p);
				n = this->Root;
			}
		}
	}
	n->color = true;
}

void RBtree::Show_All()
{
	if (this->Root == nullptr) return;
	stack<RBtreeNode*> st;
	RBtreeNode* cur = this->Root;
	cout << "now all elements are:\n";
	while (true)
	{
		if (cur != this->NIL)
		{
			st.push(cur);
			cur = cur->l;
		}
		else
		{
			cur = st.top();
			cout << cur->key << " ";
			st.pop();
			cur = cur->r;
		}
		if (cur == this->NIL && st.empty())
			break;
	}
	cout << "\nmax depth is: " << cal_maxdepth(this->Root) << endl;
}

int RBtree::cal_maxdepth(RBtreeNode* root)
{
	if (this->Root == nullptr) return 0;
	if (root == this->NIL)
		return 0;
	int d1 = cal_maxdepth(root->l);
	int d2 = cal_maxdepth(root->r);
	int res = (d1 > d2) ? d1 : d2;
	return res + 1;
}


#endif // !RBTREE_H

