#include "Leftist.hh"

Leftist::Leftist() : _root(nullptr)
{
}

Leftist::~Leftist()
{
	while (_root != nullptr)
		DeleteMin();
}

void Leftist::BuildHeap(int *arr, int n)
{
	if (arr == nullptr or n == 0)
		return;
	for (int i = 0; i < n; i++)
		Insert(arr[i]);
}

Node *Leftist::Root() const
{
	return _root;
}

void Leftist::setRoot(Node *newRoot)
{
	_root = newRoot;
}

void Leftist::Insert(int x)
{
	Node *toInsert = new Node();
	toInsert->key = x;
	toInsert->rank = 1;
	setRoot(Concatenate(toInsert, _root));
}

int Leftist::DeleteMin()
{
	if (_root == nullptr)
		return INT_MIN;
	Node *toDelete = _root;
	int toReturn = toDelete->key;
	setRoot(Concatenate(_root->lchild, _root->rchild));
	delete toDelete;
	return toReturn;
}

Node *Leftist::Concatenate(Node *H1, Node *H2)
{
	if (H1 == nullptr)
		return H2;
	if (H2 == nullptr)
		return H1;
	if (H1->key > H2->key)
		std::swap(H1, H2);
	H1->rchild = Concatenate(H1->rchild, H2);
	H1->rank = Rank(H1);
	if (Rank(H1->lchild) < Rank(H1->rchild))
		std::swap(H1->lchild, H1->rchild);
	return H1;
}

int Leftist::FindMin() const
{
	if (_root == nullptr)
		return INT_MIN;
	return _root->key;
}

int Leftist::Rank(Node *what)
{
	if (what == nullptr)
		return 0;
	int rank = 1;
	while (what->rchild != nullptr) {
		rank++;
		what = what->rchild;
	}
	return rank;
}

void Leftist::InOrder() const
{
	_in_order(_root);
	std::cout << "\b\b." << std::endl;
}

void Leftist::_in_order(Node *subtree) const
{
	if (subtree == nullptr)
		return;
	_in_order(subtree->lchild);
	std::cout << subtree->key << ", ";
	_in_order(subtree->rchild);
}

void Leftist::LevelOrder() const
{
	for (int h = 0; h <= Height(_root); h++)
		_level_order(_root, h);
	std::cout << "\b\b." << std::endl;
}

void Leftist::_level_order(Node *subtree, int level) const
{
	if (subtree == nullptr)
		return;
	if (level == 0)
		std::cout << subtree->key << ", ";
	else {
		_level_order(subtree->lchild, level - 1);
		_level_order(subtree->rchild, level - 1);
	}
}

int Leftist::Height(Node *subtree) const
{
	return _get_height(_root) - 1;
}

int Leftist::_get_height(Node *subtree) const
{
	if (subtree == nullptr)
		return 0;
	int lheight = _get_height(subtree->lchild);
	int rheight = _get_height(subtree->rchild);
	return (rheight > lheight) ? (rheight + 1) : (lheight + 1);
}
