#ifndef BINARY_NODE_HH
#define BINARY_NODE_HH
class BinarySearchNode {
    private:
	int _value;
	BinarySearchNode *_left;
	BinarySearchNode *_right;

    public:
	BinarySearchNode(int);
	~BinarySearchNode();
	int getValue() const;
	BinarySearchNode *getLeft() const;
	BinarySearchNode *getRight() const;
	void setValue(int);
	void setLeft(BinarySearchNode *);
	void setRight(BinarySearchNode *);
};
#endif
