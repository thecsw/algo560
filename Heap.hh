#ifndef __HEAP_HEAP_HH
#define __HEAP_HEAP_HH
#include <cstring>
#include <cstddef>
#include <cmath>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <iostream>
#include <functional>

#define _DEFAULT_KEY 3

const std::string ErrEmpty = "Heap is empty.";
const std::string ErrNotEmpty = "Heap has to be empty.";

double log_n(int, int);

template <typename T> class Heap {
    private:
	T *_arr;
	int _len; // Current number of elements in the heap.
	int _cap; // Maximum capacity, enlarge heap if _len == _cap.
	int _key; // Number of kids for each element.
	bool _is_max; // Max-heap if true, min-heap otherwise.

	void _expand();
	void _downheap(int);
	void _upheap(int);
	void _clear();
	int _parent(int) const;
	int _kid(int, int) const;
	bool _greater(int, int) const;
	bool _less(int, int) const;
	bool _cmp_violates(int, int) const;

    public:
	Heap();
	Heap(int);
	~Heap();

	void add(T);
	void remove();
	void makeMaxHeap();
	void makeMinHeap();
	void visitLevelOrder(std::function<void(T)>) const;
	int getSize() const;
	int getKeyNum() const;
	bool isEmpty() const;
	T getTop() const;
};

template <typename T> Heap<T>::Heap() : Heap(_DEFAULT_KEY)
{
	// Delegated to the second constructor.
}

template <typename T>
Heap<T>::Heap(int key) : _len(0), _cap(1), _key(key), _is_max(true)
{
	_arr = new T[_cap];
}

template <typename T> Heap<T>::~Heap()
{
	_clear();
	delete[] _arr;
}

template <typename T> void Heap<T>::add(T what)
{
	if (_len == _cap)
		_expand();
	_arr[_len++] = what;
	_upheap(_len - 1);
}

template <typename T> void Heap<T>::remove()
{
	if (_len < 1)
		throw std::runtime_error(ErrEmpty);
	delete _arr[0];
	_arr[0] = _arr[--_len];
	_downheap(0);
}

template <typename T>
void Heap<T>::visitLevelOrder(std::function<void(T)> visit) const
{
	for (int i = 0; i < _len; i++)
		visit(_arr[i]);
}

template <typename T> int Heap<T>::getSize() const
{
	return _len;
}

template <typename T> int Heap<T>::getKeyNum() const
{
	return _key;
}

template <typename T> bool Heap<T>::isEmpty() const
{
	return _len == 0;
}

template <typename T> T Heap<T>::getTop() const
{
	if (_len < 1)
		throw std::runtime_error(ErrEmpty);
	return _arr[0];
}

template <typename T> void Heap<T>::makeMaxHeap()
{
	if (_len != 0)
		throw std::runtime_error(ErrNotEmpty);
	_is_max = true;
}

template <typename T> void Heap<T>::makeMinHeap()
{
	if (_len != 0)
		throw std::runtime_error(ErrNotEmpty);
	_is_max = false;
}

template <typename T> void Heap<T>::_expand()
{
	T *old = _arr;
	_cap = _cap * _key + 1;
	_arr = new T[_cap];
	std::memcpy(_arr, old, sizeof(T) * _len);
	delete[] old;
}

template <typename T> void Heap<T>::_upheap(int index)
{
	int parent = _parent(index);
	//std::cout << " -- UPHEAP: index:" << index << " parent:" << parent;
	// We hit the root, stop doing everything lol
	if (parent < 0)
		return;
	// Check if comparison between a kid and its parent
	// is violated according to the heap rules
	if (_cmp_violates(index, parent)) {
		std::swap(_arr[index], _arr[parent]);
		_upheap(parent);
	}
}

template <typename T> void Heap<T>::_downheap(int parent)
{
	// if the downheap element doesn't have kids, there is
	// nowhere to downheap
	bool no_kids = true;
	for (int j = 1; j <= _key; j++)
		if (_kid(parent, j) != -1) {
			no_kids = false;
			break;
		}
	if (no_kids)
		return;
	int target_kid = _kid(parent, 1);
	for (int j = 2; j <= _key; j++) {
		int jth_kid = _kid(parent, j);
		if (jth_kid == -1) // no more kids left
			break;
		if (_cmp_violates(jth_kid, target_kid))
			target_kid = jth_kid;
	}
	if (_cmp_violates(target_kid, parent)) {
		std::swap(_arr[target_kid], _arr[parent]);
		_downheap(target_kid);
	}
}

template <typename T> void Heap<T>::_clear()
{
	int size = _len;
	while (size--)
		remove();
}

template <typename T> int Heap<T>::_parent(int index) const
{
	return int((index - 1) / _key);
}
template <typename T> int Heap<T>::_kid(int index, int kid) const
{
	// The number of the kid ranges from 1 to _key
	if (kid < 1 or kid > _key)
		return -1;
	int ans = int(_key * index + kid);
	// If kid is out of bounds, return -1
	if (ans >= _len)
		return -1;
	return ans;
}

template <typename T> bool Heap<T>::_greater(int lhs, int rhs) const
{
	return (*(_arr[lhs]) > *(_arr[rhs]));
};

template <typename T> bool Heap<T>::_less(int lhs, int rhs) const
{
	return (*(_arr[lhs]) < *(_arr[rhs]));
};

template <typename T> bool Heap<T>::_cmp_violates(int kid, int parent) const
{
	if (_is_max)
		return _greater(kid, parent); // if kid > parent
	else
		return _less(kid, parent); // if kid < parent
};
#endif /* __HEAP_HEAP_HH */
