#include "DoublyLinkedNode.hh"
#include <cstddef>

DoublyLinkedNode::DoublyLinkedNode(int value) : _next(nullptr), _prev(nullptr), _value(value)
{
}

void DoublyLinkedNode::setNext(DoublyLinkedNode *next)
{
	this->_next = next;
}

void DoublyLinkedNode::setPrev(DoublyLinkedNode *prev)
{
	this->_prev = prev;
}

void DoublyLinkedNode::setValue(int value)
{
	this->_value = value;
}

DoublyLinkedNode *DoublyLinkedNode::getNext() const
{
	return this->_next;
}

DoublyLinkedNode *DoublyLinkedNode::getPrev() const
{
	return this->_prev;
}

int DoublyLinkedNode::getValue() const
{
	return this->_value;
}
