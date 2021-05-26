#include <cstddef>
#include "BinarySearchNode.hh"

BinarySearchNode::BinarySearchNode(int value) : _value(value), _left(nullptr), _right(nullptr){};

BinarySearchNode::~BinarySearchNode(){};

int BinarySearchNode::getValue() const
{
	return _value;
}

BinarySearchNode *BinarySearchNode::getLeft() const
{
	return _left;
}

BinarySearchNode *BinarySearchNode::getRight() const
{
	return _right;
}

void BinarySearchNode::setValue(int value)
{
	_value = value;
}

void BinarySearchNode::setLeft(BinarySearchNode *left)
{
	_left = left;
}

void BinarySearchNode::setRight(BinarySearchNode *right)
{
	_right = right;
}
