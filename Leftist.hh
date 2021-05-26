#ifndef LEFTIST_LIB
#define LEFTIST_LIB
#include <climits>
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <limits.h>

struct Node {
	Node *lchild;
	Node *rchild;
	int key;
	int rank;
};

class Leftist {
    private:
	Node *_root;

	void _in_order(Node *) const;
	void _level_order(Node *, int) const;
	int _get_height(Node *) const;

    public:
	Leftist();
	~Leftist();

	void BuildHeap(int *, int);
	void Insert(int);
	int DeleteMin();

	Node *Root() const;
	void setRoot(Node *);

	static Node *Concatenate(Node *, Node *);
	static int Rank(Node *);

	int FindMin() const;
	int Height(Node *) const;
	void InOrder() const;
	void LevelOrder() const;
};
#endif // LEFTIST_LIB
