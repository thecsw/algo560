#include "DoublyLinkedList.hh"
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <string>

DoublyLinkedList::DoublyLinkedList()
	: _head(nullptr), _tail(nullptr), _length(0)
{
}

DoublyLinkedList::~DoublyLinkedList()
{
	int *values = this->forwardTraverse();
	int size = this->getLength();
	for (int i = 0; i < size; i++)
		this->remove(values[i]);
	delete[] values;
}

DoublyLinkedNode *DoublyLinkedList::findNode(int value)
{
	DoublyLinkedNode *last = this->_head;
	while (last != nullptr) {
		if (last->getValue() == value) {
			return last;
		}
		last = last->getNext();
	}
	return last;
}

bool DoublyLinkedList::isEmpty() const
{
	return this->_length == 0;
}

int DoublyLinkedList::getLength() const
{
	return this->_length;
}

void DoublyLinkedList::insert(int value)
{
	// check if the value already exists
	if (this->find(value))
		throw std::runtime_error("Value already exists.");
	DoublyLinkedNode *newNode = new DoublyLinkedNode(value);
	// if the list is empty
	if (this->isEmpty()) {
		this->_head = newNode;
		this->_tail = newNode;
	}
	// if only one node exists
	else if (this->getLength() == 1) {
		this->_head->setNext(newNode);
		this->_tail = newNode;
		this->_tail->setPrev(this->_head);
	}
	// general case when appending it
	else {
		this->_tail->setNext(newNode);
		newNode->setPrev(this->_tail);
		this->_tail = newNode;
	}
	this->_length += 1;
}

void DoublyLinkedList::remove(int value)
{
	if (this->isEmpty())
		throw std::runtime_error("List is empty.");

	if (this->getLength() == 1) {
		delete this->_tail;
		this->_head = nullptr;
		this->_tail = nullptr;
	} else {
		DoublyLinkedNode *toDelete = findNode(value);
		if (toDelete == nullptr)
			throw(std::runtime_error("Value not found."));

		// this is bad code but I don't want to do anything with it
		if (toDelete == this->_head) {
			this->_head = this->_head->getNext();
			toDelete->getNext()->setPrev(toDelete->getPrev());
		} else if (toDelete == this->_tail) {
			this->_tail = this->_tail->getPrev();
			toDelete->getPrev()->setNext(toDelete->getNext());
		} else {
			toDelete->getPrev()->setNext(toDelete->getNext());
			toDelete->getNext()->setPrev(toDelete->getPrev());
		}
		delete toDelete;
	}
	this->_length--;
}

bool DoublyLinkedList::find(int value)
{
	return this->findNode(value) != nullptr;
}

int DoublyLinkedList::findPrev(int value)
{
	DoublyLinkedNode *found = this->findNode(value);
	if (found == nullptr)
		throw std::runtime_error("Value not found.");
	if (found == this->_head) {
		throw std::runtime_error(
			"Previous value to head doesn't exist. None.");
	}
	return found->getPrev()->getValue();
}

int *DoublyLinkedList::forwardTraverse()
{
	int *forwardValues = new int[this->getLength()];
	DoublyLinkedNode *iter = this->_head;
	int counter = 0;
	while (iter != nullptr) {
		forwardValues[counter] = iter->getValue();
		iter = iter->getNext();
		counter++;
	}
	return forwardValues;
}

int *DoublyLinkedList::backwardTraverse()
{
	int temp = 0, size = this->getLength();
	int *forwardValues = this->forwardTraverse();
	for (int i = 0; i < size / 2; i++) {
		temp = forwardValues[i];
		forwardValues[i] = forwardValues[size - 1 - i];
		forwardValues[size - 1 - i] = temp;
	}
	return forwardValues;
}
