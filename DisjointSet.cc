#include <iostream>
#include <stddef.h>
#include <exception>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "DisjointSet.hh"
#include "ArrayList.hh"

DisjointSet::DisjointSet(int *to_build, int len)
	: _arr(nullptr), _len(len), _to_build(to_build)
{
}

DisjointSet::~DisjointSet()
{
	if (!_arr)
		return;
	for (int i = 0; i < _len; i++) {
		delete _arr[i];
	}
	delete[] _arr;
}

void DisjointSet::MakeSet()
{
	// To build array is empty.
	if (!_to_build)
		return;
	// Init each node and put it in the array.
	_arr = new DisjointSetNode *[_len];
	for (int i = 0; i < _len; i++) {
		_arr[i] = new DisjointSetNode();
		_arr[i]->parent = _arr[i];
		_arr[i]->payload = _to_build[i];
		_arr[i]->rank = 0;
	}
	// Clear the build array.
	delete[] _to_build;
	_to_build = nullptr;
}

int DisjointSet::UnionByRank(int x, int y)
{
	DisjointSetNode *left = _find(x);
	DisjointSetNode *right = _find(y);
	if (left->rank > right->rank)
		std::swap(left, right);
	left->parent = right;
	if (left->rank == right->rank)
		right->rank += 1;
	return right->payload;
}

DisjointSetNode *DisjointSet::_get_node(int what) const
{
	for (int i = 0; i < _len; i++)
		if (_arr[i]->payload == what)
			return _arr[i];
	return nullptr;
}

DisjointSetNode *DisjointSet::_find(int what) const
{
	DisjointSetNode *candidate = _get_node(what);
	if (!candidate)
		throw std::runtime_error(std::to_string(what) + " not found");
	while (candidate != candidate->parent)
		candidate = candidate->parent;
	return candidate;
}

int DisjointSet::find(int what) const
{
	return _find(what)->payload;
}

ArrayList<DisjointSetNode *> *DisjointSet::_path(int what) const
{
	// Use home-cooked ArrayList to keep track of our path.
	ArrayList<DisjointSetNode *> *path = new ArrayList<DisjointSetNode *>();
	DisjointSetNode *temp = _get_node(what);
	while (temp != temp->parent) {
		path->Append(temp);
		temp = temp->parent;
	}
	// Add the representative.
	path->Append(temp);
	return path;
}

int DisjointSet::PathCompression(int what)
{
	ArrayList<DisjointSetNode *> *path = _path(what);
	DisjointSetNode *rep = path->List()[path->Len() - 1];
	for (int i = 0; i < path->Len(); i++)
		path->List()[i]->parent = rep;
	delete path;
	return rep->payload;
}

void DisjointSet::PrintPath(int what) const
{
	ArrayList<DisjointSetNode *> *path = _path(what);
	if (path->Len() == 1) {
		std::cout << path->List()[0]->payload;
		return;
	}
	for (int i = 0; i < path->Len() - 1; i++)
		std::cout << path->List()[i]->payload << "->";
	std::cout << path->List()[path->Len() - 1]->payload;
	delete path;
}
