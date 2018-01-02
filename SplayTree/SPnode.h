#ifndef SPNODE_H
#define SPNODE_H

using namespace std;

class SPnode;

class SPnode
{
public:
	int key;
	int size;
	SPnode* p;
	SPnode* chd[2];
	SPnode();
	SPnode(int key);
	bool isRightKid();
	SPnode* linkTo(bool LoR, SPnode* n);
	void update();
};

SPnode::SPnode()
{
	this->p = nullptr;
	this->chd[0] = nullptr;
	this->chd[1] = nullptr;
	this->key = 0;
	this->size = 1;
}

SPnode::SPnode(int key)
{
	this->p = nullptr;
	this->chd[0] = nullptr;
	this->chd[1] = nullptr;
	this->key = key;
	this->size = 1;
}

bool SPnode::isRightKid()
{
	return (this == this->p->chd[1]);
}

SPnode* SPnode::linkTo(bool LnR, SPnode* n)
{
	this->chd[LnR] = n;
	if (n != nullptr) n->p = this;
	return this;
}

void SPnode::update()
{
	this->size = (this->chd[0] != nullptr ? this->chd[0]->size : 0) +
		(this->chd[1] != nullptr ? this->chd[1]->size : 0) + 1;
}


#endif // !SPNODE_H
