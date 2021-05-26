#include "MinMaxHeap.hh"
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <utility>

int mylog2(int);

const std::string ErrEmpty = "Heap is empty.";

MinMaxHeap::MinMaxHeap() : _len(0), _cap(1)
{
	_arr = new int[_cap];
}

MinMaxHeap::~MinMaxHeap()
{
	delete[] _arr;
}

void MinMaxHeap::BuildHeap(int *arr, int len)
{
	for (int i = 0; i < len; i++)
		Insert(arr[i]);
	this->PrintAllLevels();
}

void MinMaxHeap::Insert(int what)
{
	if (_len == _cap)
		_expand();
	_arr[_len++] = what;
	if (_len == 1)
		return;
	int _what = _len - 1;
	int parent = _parent(_what);
	if (_arr[_what] == _arr[parent])
		return;
	// Check the parent first
	if (_is_min(_what)) {
		if (_arr[_what] > _arr[parent]) {
			std::swap(_arr[_what], _arr[parent]);
			_upheap_max(parent);
		} else
			_upheap_min(_what);
	}
	if (_is_max(_what)) {
		if (_arr[_what] < _arr[parent]) {
			std::swap(_arr[_what], _arr[parent]);
			_upheap_min(parent);
		} else
			_upheap_max(_what);
	}
}

int MinMaxHeap::DeleteMin()
{
	if (_len == 0)
		throw std::runtime_error(ErrEmpty);
	if (_len == 1)
		return _arr[--_len];
	if (_len == 2) {
		int toReturn = _arr[0];
		_arr[0] = _arr[--_len];
		return toReturn;
	}
	int s = _find_second_smallest();
	int x = _len - 1;
	if (_arr[x] <= _arr[s]) {
		int toReturn = _arr[0];
		_len--;
		_arr[0] = _arr[x];
		return toReturn;
	}
	int toReturn = _arr[0];
	_arr[0] = _arr[s];
	_len--;
	if (_parent(s) == 0) {
		_arr[s] = _arr[x];
		return toReturn;
	}
	if (_arr[x] <= _arr[_parent(s)]) {
		_arr[s] = _arr[x];
		_upheap_min(s);
		_upheap_max(s);
                _push_down(s);
		return toReturn;
	}
	if (_arr[x] > _arr[_parent(s)]) {
		_arr[_parent(s)] = _arr[x];
		_upheap_min(_parent(s));
		_upheap_max(_parent(s));
                _push_down(_parent(s));
		return toReturn;
	}

	return toReturn;
}

int MinMaxHeap::DeleteMax()
{
	if (_len == 0)
		throw std::runtime_error(ErrEmpty);
	if (_len <= 2)
		return _arr[--_len];
	int toDelete = _find_largest();
	int l = _find_second_largest();
	int pl = _parent(l);
	int x = _len - 1;
	if (_arr[x] > _arr[l]) {
		int toReturn = _arr[toDelete];
		_len--;
		_arr[toDelete] = _arr[x];
		return toReturn;
	}
	int toReturn = _arr[toDelete];
	_arr[toDelete] = _arr[l];
	_len--;
	if (pl == toDelete) {
		_arr[l] = _arr[x];
		return toReturn;
	}
	if (_arr[x] > _arr[pl]) {
		_arr[l] = _arr[x];
		_push_down(l);
		return toReturn;
	}
	if (_arr[x] <= _arr[pl]) {
		_arr[pl] = _arr[x];
		_push_down(pl);
		return toReturn;
	}
	return toReturn;
}

int MinMaxHeap::FindMin() const
{
	if (_len == 0)
		throw std::runtime_error(ErrEmpty);
	return _arr[0];
}

int MinMaxHeap::FindMax() const
{
	if (_len == 0)
		throw std::runtime_error(ErrEmpty);
	return _arr[_find_largest()];
}

void MinMaxHeap::PrintAllLevels() const
{
	for (int i = 0; i < _len - 1; i++) {
		std::cout << _arr[i] << ", ";
		if ((_is_min(i) and _is_max(i + 1)) or
		    (_is_max(i) and _is_min(i + 1)))
			std::cout << std::endl;
	}
	std::cout << _arr[_len - 1] << std::endl;
}

void MinMaxHeap::MinLevelElements() const
{
	for (int i = 0; i < _len; i++) {
		if (not _is_min(i))
			continue;
		std::cout << _arr[i];
		if (_is_min(i + 1))
			std::cout << ", ";
		if (_is_max(i + 1))
			std::cout << std::endl;
	}
}

void MinMaxHeap::MaxLevelElements() const
{
	for (int i = 0; i < _len; i++) {
		if (not _is_max(i))
			continue;
		std::cout << _arr[i];
		if (_is_max(i + 1))
			std::cout << ", ";
		if (_is_min(i + 1))
			std::cout << std::endl;
	}
}

int MinMaxHeap::getSize() const
{
	return _len;
}

void MinMaxHeap::_expand()
{
	int *old = _arr;
	_cap = 2 * _cap + 1;
	_arr = new int[_cap];
	std::memcpy(_arr, old, sizeof(int) * _len);
	delete[] old;
}

void MinMaxHeap::_upheap_min(int index)
{
	int target = 1;
	int temp = index;
	while (target > 0) {
		if (temp == 0)
			return;
		target = _parent(temp);
		if (not _is_min(target)) {
			temp = target;
			continue;
		}
		if (_arr[index] < _arr[target]) {
			std::swap(_arr[index], _arr[target]);
			index = target;
		} else {
			break;
		}
	}
}

void MinMaxHeap::_upheap_max(int index)
{
	int target = 1;
	int temp = index;
	while (target > 0) {
		if (temp == 0)
			return;
		target = _parent(temp);
		if (not _is_max(target)) {
			temp = target;
			continue;
		}
		if (_arr[index] > _arr[target]) {
			std::swap(_arr[index], _arr[target]);
			index = target;
		} else {
			break;
		}
	}
}

void MinMaxHeap::_push_down(int parent)
{
	// Parents of min should be bigger
	if (_is_min(parent)) {
		int first = _first_kid(parent);
		int second = _second_kid(parent);
		// no kids
		if (first == -1)
			return;
		// only one kid
		if (second == -1) {
			if (_arr[first] < _arr[parent])
				std::swap(_arr[first], _arr[parent]);
			return;
		}
		// both kids

		// if parent is bigger than both kids, replace it with the smallest kid
		if (_arr[first] <= _arr[parent] &&
		    _arr[second] <= _arr[parent]) {
			int smaller_kid =
				(_arr[first] < _arr[second]) ? first : second;
			std::swap(_arr[smaller_kid], _arr[parent]);
			_push_down(smaller_kid);
			return;
		}
		// first kid is smaller (NOT OK) and second kid is bigger (OK)
		if (_arr[first] < _arr[parent] && _arr[second] > _arr[parent]) {
			std::swap(_arr[first], _arr[parent]);
			_push_down(first);
			return;
		}
		// first kid is bigger (OK) and second kid is smaller (NOT OK)
		if (_arr[first] > _arr[parent] && _arr[second] < _arr[parent]) {
			std::swap(_arr[second], _arr[parent]);
			_push_down(second);
			return;
		}
		// first kid is bigger (OK) and second kid is bigger (OK)
		int larger_kid = (_arr[first] > _arr[second]) ? first : second;
		int grandpa = _parent(parent);
		if (_arr[larger_kid] > _arr[grandpa]) {
			std::swap(_arr[larger_kid], _arr[grandpa]);
                        _push_down(grandpa);
		}
	}
	// parents of max should be smaller
	if (_is_max(parent)) {
		int first = _first_kid(parent);
		int second = _second_kid(parent);
		// no kids
		if (first == -1)
			return;
		// only one kid
		if (second == -1) {
			if (_arr[first] > _arr[parent])
				std::swap(_arr[first], _arr[parent]);
			return;
		}
		// both kids

		// if parent is smaller than both kids, replace it with the smallest kid
		if (_arr[first] >= _arr[parent] &&
		    _arr[second] >= _arr[parent]) {
			int larger_kid =
				(_arr[first] > _arr[second]) ? first : second;
			std::swap(_arr[larger_kid], _arr[parent]);
			_push_down(larger_kid);
			return;
		}
		// first kid is bigger (NOT OK) and second is smaller (OK)
		if (_arr[first] > _arr[parent] && _arr[second] < _arr[parent]) {
			std::swap(_arr[first], _arr[parent]);
			_push_down(first);
			return;
		}
		// first kid is smaller (OK) and second kid is bigger (NOT OK)
		if (_arr[first] < _arr[parent] && _arr[second] > _arr[parent]) {
			std::swap(_arr[second], _arr[parent]);
			_push_down(second);
			return;
		}
                // first kid is smaller (OK) and second kid is smaller (OK)
		int smaller_kid = (_arr[first] < _arr[second]) ? first : second;
		int grandpa = _parent(parent);
		if (_arr[smaller_kid] < _arr[grandpa]) {
			std::swap(_arr[smaller_kid], _arr[grandpa]);
                        _push_down(grandpa);
		}
	}
}

int MinMaxHeap::_first_kid(int parent) const
{
	int ans = int(2 * parent + 1);
	return (ans >= _len) ? -1 : ans;
}

int MinMaxHeap::_second_kid(int parent) const
{
	int ans = int(2 * parent + 2);
	return (ans >= _len) ? -1 : ans;
}

int MinMaxHeap::_parent(int kid) const
{
	return (kid - 1) / 2;
}

int MinMaxHeap::_grandparent(int kid) const
{
	if (kid < 3)
		return -1;
	return (_parent(kid) - 1) / 2;
}

bool MinMaxHeap::_is_min(int what) const
{
	return not _is_max(what);
}

bool MinMaxHeap::_is_max(int what) const
{
	if (what < 2)
		return what;
	return mylog2(what) % 2 == 1;
}

int MinMaxHeap::_find_second_smallest() const
{
	if (_len == 1)
		return 0;
	if (_len == 2)
		return 1;
	if (_len == 3)
		return (_arr[_first_kid(0)] < _arr[_second_kid(0)]) ? 1 : 2;
	// Search the grandchildren, default to the 4th node (first min node)
	int smallest = 3;
	for (int i = 4; i < ((_len < 7) ? _len : 7); i++)
		if (_arr[i] < _arr[smallest])
			smallest = i;
	return smallest;
}

int MinMaxHeap::_find_largest() const
{
	if (_len == 1 or _len == 2)
		return _len - 1;
	return (_arr[1] < _arr[2]) ? 2 : 1;
}

int MinMaxHeap::_find_second_largest() const
{
	if (_len == 1 or _len == 2)
		return 0;
	// Search the next max nodes
	int largest = (_arr[1] < _arr[2]) ? 1 : 2;
	if (_len < 8)
		return largest;
	for (int i = 8; i < ((_len <= 14) ? _len : 14); i++)
		if (_arr[i] > _arr[largest])
			largest = i;
	return largest;
}

int mylog2(int what)
{
	return floor(log2(what + 1));
}
