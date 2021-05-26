#include <limits.h>
#include <exception>
#include <stdexcept>
#include <iostream>

#include "ClosedHashTable.hh"

#define AVAIL INT_MAX
#define R 5

bool is_prime(int);

const std::string ErrNotFound = "Not found.";
const std::string ErrAlreadyExists = "Already exists.";
const std::string ErrInsertFailed = "Insert failed. Not my problem.";
const std::string InfRehashApplied = "> Rehash applied.\n";

ClosedHashTable::ClosedHashTable(int size)
{
	_size = size;
	_load = 0;
	_max_load_frac_denom = 2;
	_arr = new int[_size];
	_fl = new bool[_size];
	_use_quad = true;
	for (int i = 0; i < _size; i++) {
		_arr[i] = AVAIL;
		_fl[i] = false;
	}
}

ClosedHashTable::~ClosedHashTable()
{
	delete[] _arr;
	delete[] _fl;
}

void ClosedHashTable::UseDoubleHashing()
{
	_use_quad = false;
}

int ClosedHashTable::_h(int x) const
{
	return x % _size;
}

int ClosedHashTable::_f_quad(int k) const
{
	return k * k;
}

int ClosedHashTable::_f_doub(int x, int k) const
{
	return k * (R - (x % R));
}

int ClosedHashTable::_super_h(int x, int k) const
{
	if (_use_quad)
		return (_h(x) + _f_quad(k)) % _size;
	return (_h(x) + _f_doub(x, k)) % _size;
}

void ClosedHashTable::_rehash()
{
	// Find the first prime >= 2*size
	int new_size = 2 * _size;
	while (!is_prime(new_size))
		new_size++;
	// Temporarily save pointers
	int *old_arr = _arr;
	int old_size = _size;
	// Allocate new array and refresh the load factor
	_arr = new int[new_size];
	_size = new_size;
	_load = 0;
	for (int i = 0; i < _size; i++)
		_arr[i] = AVAIL;
	// Start readding all the elements into new array
	for (int i = 0; i < old_size; i++)
		if (old_arr[i] != AVAIL)
			this->Insert(old_arr[i]);
	// Refresh the deletion flags
	delete[] _fl;
	_fl = new bool[new_size];
	// Delete the old array
	delete[] old_arr;
	std::cout << InfRehashApplied;
}

void ClosedHashTable::Insert(int what)
{
	// If we hit the max load, rehash
	if (_max_load_frac_denom * _load >= _size)
		_rehash();
	int pos = 0;
	for (int k = 0; k <= _size; k++) {
		pos = _super_h(what, k);
		if (_arr[pos] == what)
			throw std::runtime_error(ErrAlreadyExists);
		if (_arr[pos] != AVAIL)
			continue;
		_arr[pos] = what;
		_load++;
		return;
	}
	// This should never happen but it's good to panic
	throw std::runtime_error(ErrInsertFailed);
}

void ClosedHashTable::Delete(int what)
{
	int pos = 0;
	for (int k = 0; k <= _size; k++) {
		pos = _super_h(what, k);
		if (_arr[pos] == AVAIL && !_fl[pos])
			break;
		if (_arr[pos] != what)
			continue;
		_arr[pos] = AVAIL;
		_fl[pos] = true;
		_load--;
		return;
	}
	throw std::runtime_error(ErrNotFound);
}

int ClosedHashTable::Find(int what) const
{
	int pos = 0;
	for (int k = 0; k <= _size; k++) {
		if (_arr[_super_h(what, k)] == what)
			return pos;
	}
	return -1;
}

void ClosedHashTable::Print() const
{
	for (int i = 0; i < _size; i++) {
		std::cout << i << ": ";
		if (_arr[i] == AVAIL)
			std::cout << "";
		else
			std::cout << _arr[i];
		std::cout << std::endl;
	}
}

bool is_prime(int what)
{
	for (int i = 2; i < what / 2; i++)
		if (what % i == 0)
			return false;
	return true;
}
