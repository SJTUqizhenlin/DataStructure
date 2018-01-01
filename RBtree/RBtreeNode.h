#ifndef RBTREENODE_H
#define RBTREENODE_H

#include <string>
using namespace std;

class RBtreeNode
{
public:
	int key;
	string val;
	bool color; // true is black and false is red
	RBtreeNode *l;
	RBtreeNode *r;
	RBtreeNode *p;

	RBtreeNode();
	RBtreeNode(int key, string val, bool color);
};

RBtreeNode::RBtreeNode()
{
	this->key = 0;
	this->val = "";
	this->color = false;
	this->l = nullptr;
	this->r = nullptr;
	this->p = nullptr;
}

RBtreeNode::RBtreeNode(int key, string val, bool color)
{
	this->key = key;
	this->val = val;
	this->color = color;
	this->l = nullptr;
	this->r = nullptr;
	this->p = nullptr;
}


#endif // !RBTREENODE_H

