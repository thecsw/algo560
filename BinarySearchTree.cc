#include <math.h>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <iostream>
#include <string>

#include "BinarySearchTree.hh"

const std::string ErrEmpty = "BST is empty";
const std::string ErrNotFound = "Not found";

BinarySearchTree::BinarySearchTree() : _root(nullptr){};

BinarySearchTree::~BinarySearchTree()
{
	this->clear();
}

void BinarySearchTree::add(int what)
{
	_root = _add(_root, new BinarySearchNode(what));
}

BinarySearchNode *BinarySearchTree::_add(BinarySearchNode *subtree,
					 BinarySearchNode *toAdd)
{
	if (subtree == nullptr)
		return toAdd;
	if (subtree->getValue() <= toAdd->getValue())
		subtree->setRight(_add(subtree->getRight(), toAdd));
	else
		subtree->setLeft(_add(subtree->getLeft(), toAdd));
	return subtree;
}

void BinarySearchTree::remove(int what)
{
	if (isEmpty())
		throw std::runtime_error(ErrEmpty);
	if (_find(_root, what) == nullptr)
		throw std::runtime_error(ErrNotFound);
	_remove(_root, what);
}

BinarySearchNode *BinarySearchTree::_remove(BinarySearchNode *subtree, int what)
{
	if (subtree == nullptr)
		return subtree;
	if (what < subtree->getValue())
		subtree->setLeft(_remove(subtree->getLeft(), what));
	else if (what > subtree->getValue())
		subtree->setRight(_remove(subtree->getRight(), what));
	else {
		// no children
		if (subtree->getLeft() == nullptr &&
		    subtree->getRight() == nullptr) {
			delete subtree;
			return nullptr;
		}
		// only left child
		if (subtree->getRight() == nullptr) {
			BinarySearchNode *tmp = subtree->getLeft();
			delete subtree;
			return tmp;
		}
		// only right child
		if (subtree->getLeft() == nullptr) {
			BinarySearchNode *tmp = subtree->getRight();
			delete subtree;
			return tmp;
		}
		// both children exist
		int min = _find_min(subtree->getRight());
		subtree->setValue(min);
		subtree->setRight(_remove(subtree->getRight(), min));
	}
	return subtree;
}

BinarySearchNode *BinarySearchTree::_find(BinarySearchNode *subtree, int what)
{
	if (subtree == nullptr)
		return nullptr;
	if (subtree->getValue() == what)
		return subtree;
	if (subtree->getValue() < what)
		return _find(subtree->getRight(), what);
	return _find(subtree->getLeft(), what);
}

void BinarySearchTree::clear()
{
	_clear(_root);
	_root = nullptr;
}

void BinarySearchTree::_clear(BinarySearchNode *subtree)
{
	if (subtree == nullptr)
		return;
	_clear(subtree->getLeft());
	_clear(subtree->getRight());
	delete subtree;
}

void BinarySearchTree::removeMin()
{
	remove(findMin());
}

void BinarySearchTree::removeMax()
{
	remove(findMax());
}

bool BinarySearchTree::isEmpty() const
{
	return (_root == nullptr);
}

int BinarySearchTree::getSize() const
{
	return _get_size(_root);
}

int BinarySearchTree::_get_size(BinarySearchNode *subtree) const
{
	return (subtree) ? _get_size(subtree->getLeft()) +
				   _get_size(subtree->getRight()) + 1 :
				 0;
}

int BinarySearchTree::getHeight() const
{
	return _get_height(_root) - 1;
}

int BinarySearchTree::_get_height(BinarySearchNode *subtree) const
{
	if (subtree == nullptr)
		return 0;
	int left_height = _get_height(subtree->getLeft());
	int right_height = _get_height(subtree->getRight());
	if (right_height > left_height)
		return right_height + 1;
	return left_height + 1;
}

int BinarySearchTree::findMin() const
{
	if (isEmpty())
		throw std::runtime_error(ErrEmpty);
	return _find_min(_root);
}

int BinarySearchTree::_find_min(BinarySearchNode *subtree) const
{
	if (subtree->getLeft() == nullptr)
		return subtree->getValue();
	return _find_min(subtree->getLeft());
}

int BinarySearchTree::findMax() const
{
	if (isEmpty())
		throw std::runtime_error(ErrEmpty);
	return _find_max(_root);
}

int BinarySearchTree::_find_max(BinarySearchNode *subtree) const
{
	if (subtree->getRight() == nullptr)
		return subtree->getValue();
	return _find_max(subtree->getRight());
}

int BinarySearchTree::findInOrderSuccessor(int what) const
{
	int *inorder = new int[getSize()];
	int counter = 0;
	bool found = false;
	int to_return;
	_fill_arr_with_inorder(_root, inorder, &counter);
	for (int i = 0; i < getSize(); i++)
		if (inorder[i] == what && i + 1 < getSize()) {
			found = true;
			to_return = inorder[i + 1];
		}
	delete[] inorder;
	if (found)
		return to_return;
	throw std::runtime_error(ErrNotFound);
}

void BinarySearchTree::_fill_arr_with_inorder(BinarySearchNode *subtree,
					      int *arr, int *counter) const
{
	if (subtree == nullptr)
		return;
	_fill_arr_with_inorder(subtree->getLeft(), arr, counter);
	arr[(*counter)++] = subtree->getValue();
	_fill_arr_with_inorder(subtree->getRight(), arr, counter);
}

void BinarySearchTree::visitPreOrder(std::function<void(int)> visit) const
{
	_visit_pre_order(_root, visit);
}

void BinarySearchTree::_visit_pre_order(BinarySearchNode *subtree,
					std::function<void(int)> visit) const
{
	if (subtree == nullptr)
		return;
	visit(subtree->getValue());
	_visit_pre_order(subtree->getLeft(), visit);
	_visit_pre_order(subtree->getRight(), visit);
}

void BinarySearchTree::visitPostOrder(std::function<void(int)> visit) const
{
	_visit_post_order(_root, visit);
}

void BinarySearchTree::_visit_post_order(BinarySearchNode *subtree,
					 std::function<void(int)> visit) const
{
	if (subtree == nullptr)
		return;
	_visit_post_order(subtree->getLeft(), visit);
	_visit_post_order(subtree->getRight(), visit);
	visit(subtree->getValue());
}

void BinarySearchTree::visitInOrder(std::function<void(int)> visit) const
{
	_visit_in_order(_root, visit);
}

void BinarySearchTree::_visit_in_order(BinarySearchNode *subtree,
				       std::function<void(int)> visit) const
{
	if (subtree == nullptr)
		return;
	_visit_in_order(subtree->getLeft(), visit);
	visit(subtree->getValue());
	_visit_in_order(subtree->getRight(), visit);
}

void BinarySearchTree::visitLeftSideView(std::function<void(int)> visit) const
{
	_visit_left_side_view(_root, visit);
}

void BinarySearchTree::_visit_left_side_view(
	BinarySearchNode *subtree, std::function<void(int)> visit) const
{
	if (subtree == nullptr)
		return;
	visit(subtree->getValue());
	if (subtree->getLeft() == nullptr)
		_visit_left_side_view(subtree->getRight(), visit);
	else
		_visit_left_side_view(subtree->getLeft(), visit);
}

void BinarySearchTree::visitRightSideView(std::function<void(int)> visit) const
{
	_visit_right_side_view(_root, visit);
}

void BinarySearchTree::_visit_right_side_view(
	BinarySearchNode *subtree, std::function<void(int)> visit) const
{
	if (subtree == nullptr)
		return;
	visit(subtree->getValue());
	if (subtree->getRight() == nullptr)
		_visit_right_side_view(subtree->getLeft(), visit);
	else
		_visit_right_side_view(subtree->getRight(), visit);
}

void BinarySearchTree::visitLevelOrder(std::function<void(int)> visit) const
{
	for (int h = 0; h <= getHeight(); h++)
		_visit_level_order_level(_root, h, visit);
}

void BinarySearchTree::_visit_level_order_level(
	BinarySearchNode *subtree, int level,
	std::function<void(int)> visit) const
{
	if (subtree == nullptr)
		return;
	if (level == 0)
		visit(subtree->getValue());
	else {
		_visit_level_order_level(subtree->getLeft(), level - 1, visit);
		_visit_level_order_level(subtree->getRight(), level - 1, visit);
	}
}

void BinarySearchTree::visitSpiralLevelOrder(
	std::function<void(int)> visit) const
{
	int *_arr = new int[getSize()];
	int counter = 0;
	for (int h = 0; h <= getHeight(); h++) {
		int *_arr_tmp = new int[int(pow(2, h))];
		int _counter_tmp = 0;
		_visit_level_order_level_no_visit(_root, h, _arr_tmp,
						  &_counter_tmp);
		if (h % 2 == 0)
			for (int i = 0; i < _counter_tmp; i++)
				_arr[counter++] = _arr_tmp[i];
		else
			for (int i = _counter_tmp - 1; i >= 0; i--)
				_arr[counter++] = _arr_tmp[i];
		delete[] _arr_tmp;
	}
	for (int i = 0; i < counter; i++)
		visit(_arr[i]);
	delete[] _arr;
}

void BinarySearchTree::_visit_level_order_level_no_visit(
	BinarySearchNode *subtree, int level, int *arr, int *counter) const
{
	if (subtree == nullptr)
		return;
	if (level == 0)
		arr[(*counter)++] = subtree->getValue();
	else {
		_visit_level_order_level_no_visit(subtree->getLeft(), level - 1,
						  arr, counter);
		_visit_level_order_level_no_visit(subtree->getRight(),
						  level - 1, arr, counter);
	}
}
