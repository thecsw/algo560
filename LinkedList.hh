/**
 * @file LinkedList.hh
 * @class LinkedList
 * @brief Class that operates on Node objects
 *
 * The class defines a list of Node objects connected 
 * to each other via next Node pointer addresses. Each 
 * Node carries a payload. Supports a list of methods
 * for extensive control over the linked list.
 *
 * @note Works fast thanks to pointer operations
 *
 * @author Sandy Urazayev
 *
 * Contact: ctu@ku.edu
 *
 */
#ifndef LINKED_LIST_HH
#define LINKED_LIST_HH
#include <iostream>
#include <stdexcept>

#include "LinkedNode.hh"

template <typename T> class LinkedList {
    private:
	/* Node pointer to the first node
	 * If empty, points to NULL
	 */
	LinkedNode<T> *m_front;

	/* Number of the nodes */
	int m_length;

	/**
	 * @brief Returns address of i^th node
	 * @pre The position is between 1 and the list's length
	 * @param index 0 <= index < length
	 * @return pointer to the Node at position index
	 *
	 * This is a private method used by other public method.
	 * This is a helper method that assumes all the parameters
	 * passed are valid and sanitized.
	 **/
	LinkedNode<T> *getNode(int) const;

    public:
	/**
	 * @brief Consructor for LinkedList class. 
	 * 
	 * Sets the length of the list to 0 and points 
	 * its front to nullptr
	 **/
	LinkedList();

	/**
	 * @brief Creates a deep copy of a LinkedList instance
	 * @param const LinkedList& exists
	 **/
	LinkedList(const LinkedList<T> &);

	/**
	 * @post Destructor for LinkedList class.
	 * @see clear()
	 *
	 * Calls clear()
	 **/
	~LinkedList();

	/**
	 * @brief Equal sign overloaded for LinkedList
	 * @post makes a copy of rhs to lhs
	 * @param const LinkedList&: 
	 * @return (*this) is returned
	 **/
	LinkedList<T> &operator=(const LinkedList<T> &);

	/**
	 * @brief Compare two lists
	 * @param const LinkedList&: 
	 * @return if lists are the same, return true
	 * false otherwise
	 **/
	bool operator==(LinkedList<T> const &);

	/**
	 * @brief Compare two lists
	 * @param const LinkedList&: 
	 * @return if lists are the same, return true
	 * false otherwise
	 **/
	bool equals(const LinkedList<T> &) const;

	/**
	 * @brief Checks if the list is empty
	 * @return true if length is 0, false otherwise
	 * @see getLength()
	 **/
	bool isEmpty() const;

	/**
	 * @brief Returns the list length
	 * @return list length
	 * @see m_length
	 **/
	int getLength() const;

	/**
	 * @brief Inserts a new node in the list
	 * @pre The position is between 1 and the list's length + 1
	 * @post New node is placed in the list
	 * @param index Given position to insert
	 * @param value Given value to insert
	 * @throw std::runtime_error if position is invalid
	 *
	 * Inserts a new node in the list by rewiring previous node.
	 * Safe to use, corner cases are implemented
	 **/
	void insert(int, T);
	void addBack(T);
	void addFront(T);

	/**
	 * @brief Deletes a node in the list
	 * @pre The position is between 1 and the list's length
	 * @post Node is deleted and freed from memory
	 * @param index 1<= position <= length
	 * @throw std::runtime_error if position is invalid
	 *
	 * Deletes a node from the list and frees the memory.
	 * Safe to use, corner cases are implemented
	 **/
	void remove(int);

	/**
	 * @brief Clears the whole list and frees memory
	 * @post ALL nodes are deleted and freed from memory
	 * @see remove()
	 *
	 * Deletes all nodes by calling remove(1) length number
	 * of times. Safe to use, corner cases are implemented
	 **/
	void clear();

	/**
	 * @brief Returns value of i^th node's payload
	 * @pre The position is between 1 and the list's length
	 * @see getNode()
	 * @param index 1<= position <= length
	 * @throw std::runtime_error if position is invalid
	 * @return index node's value
	 **/
	T getEntry(int) const;

	/**
	 * @pre The position is between 1 and the list's length
	 * @post The entry at the given position is replaced with the new entry
	 * @param index:  1<= position <= length
	 * @param value: A new entry to put in the list
	 * @throw std::runtime_error if the position is invalid.
	 **/
	void replace(int, T);

	// swaps two nodes at those indices
	void swap(int, int);

	bool exists(T) const;
        int find(T) const;
};

template <typename T>
LinkedList<T>::LinkedList() : m_front(nullptr), m_length(0)
{
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &original)
	: m_front(nullptr), m_length(0)
{
	for (int i = 1; i <= original.getLength(); i++)
		this->insert(this->m_length + 1, original.getEntry(i));
}

template <typename T> LinkedList<T>::~LinkedList()
{
	this->clear();
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
	/* Clear everything that was here before */
	this->clear();
	for (int i = 1; i <= rhs.getLength(); i++)
		this->insert(i, rhs.getEntry(i));
	return (*this);
}

template <typename T> bool LinkedList<T>::operator==(LinkedList<T> const &rhs)
{
	return this->equals(rhs);
}

template <typename T> bool LinkedList<T>::equals(const LinkedList<T> &rhs) const
{
	if (this->m_length != rhs.getLength())
		return false;
	for (int i = 1; i <= this->m_length; i++)
		if (this->getEntry(i) != rhs.getEntry(i))
			return false;
	return true;
}

template <typename T> bool LinkedList<T>::isEmpty() const
{
	return (this->m_length == 0);
}

template <typename T> int LinkedList<T>::getLength() const
{
	return this->m_length;
}

template <typename T> void LinkedList<T>::insert(int index, T value)
{
	/* Prepare the index */
	index--;
	/* Return if index is invalid */
	if (index > this->m_length or index < 0) {
		throw(std::runtime_error("Length out of bounds."));
	}
	/* If list is empty */
	if (this->isEmpty()) {
		this->m_front = new LinkedNode<T>(value);
		this->m_length++;
		return;
	}
	/* Adding a node in front of the list */
	if (index == 0) {
		LinkedNode<T> *temp = new LinkedNode<T>(value);
		temp->setNext(this->m_front);
		this->m_front = temp;
		this->m_length++;
		return;
	}
	/* Finding the previous node to rewire */
	LinkedNode<T> *prev = this->getNode(--index);
	LinkedNode<T> *temp = new LinkedNode<T>(value);
	temp->setNext(prev->getNext());
	prev->setNext(temp);
	/* Increase the length by 1 */
	this->m_length++;
}

template <typename T> void LinkedList<T>::addBack(T value)
{
	this->insert(this->m_length + 1, value);
}

template <typename T> void LinkedList<T>::addFront(T value)
{
	this->insert(1, value);
}

template <typename T> void LinkedList<T>::remove(int index)
{
	/* Preparing the index */
	index--;
	if (index < 0 or index >= this->m_length)
		throw(std::runtime_error("Length out of bounds."));
	if (this->getLength() == 1) {
		delete (this->m_front);
		this->m_front = nullptr;
		this->m_length--;
		return;
	}
	if (index == 0) {
		LinkedNode<T> *temp = this->m_front;
		this->m_front = this->m_front->getNext();
		delete temp;
		this->m_length--;
		return;
	}
	LinkedNode<T> *prev = this->getNode(--index);
	LinkedNode<T> *entry = prev->getNext();
	prev->setNext(entry->getNext());
	delete entry;
	this->m_length--;
}

template <typename T> void LinkedList<T>::clear()
{
	int size = this->m_length;
	while (size--) {
		this->remove(1);
	}
}

template <typename T> T LinkedList<T>::getEntry(int index) const
{
	/* Preparing the index */
	index--;
	/* Die if index is wrong */
	if (index < 0 or index >= this->m_length)
		throw(std::runtime_error("Length out of bounds."));
	/* Get the i^th Node */
	LinkedNode<T> *entry = this->getNode(index);
	/* Return the value */
	return entry->getValue();
}

template <typename T> void LinkedList<T>::replace(int index, T new_value)
{
	/* Preparing the index */
	index--;
	if (index < 0 or index >= this->m_length)
		throw(std::runtime_error("Length out of bounds."));
	LinkedNode<T> *entry = this->getNode(index);
	entry->setValue(new_value);
}

template <typename T> void LinkedList<T>::swap(int index1, int index2)
{
	if (index1 == index2)
		return;
	index1--;
	index2--;
	if ((index1 < 0 or index1 >= this->m_length) or
	    (index2 < 0 or index2 >= this->m_length))
		throw(std::runtime_error("Length out of bounds."));

	/* Finding the locations of the indecies */
	int big_index = (index1 > index2) ? index1 : index2;
	int small_index = (index1 < index2) ? index1 : index2;

	/* If swapping nodes are adjacent */
	if (big_index - small_index == 1) {
		/* Adjacent and first index is the head */
		if (small_index == 0) {
			/* Should work too */
			LinkedNode<T> *first = m_front;
			LinkedNode<T> *second = m_front->getNext();
			first->setNext(second->getNext());
			second->setNext(first);
			this->m_front = second;
			return;
		}
		/* Normal case */
		/* This one should work too */
		LinkedNode<T> *prev = this->getNode(small_index - 1);
		LinkedNode<T> *first = prev->getNext();
		LinkedNode<T> *second = first->getNext();
		first->setNext(second->getNext());
		second->setNext(first);
		prev->setNext(second);
		return;
	}

	/* If swapping nodes are distant from each other */
	/* If the first index is the head of the list */
	if (small_index == 0) {
		/* This should work, tested on a whiteboard */
		LinkedNode<T> *first = m_front;
		LinkedNode<T> *prev = this->getNode(big_index - 1);
		LinkedNode<T> *second = prev->getNext();
		LinkedNode<T> *next = second->getNext();
		second->setNext(first->getNext());
		first->setNext(next);
		prev->setNext(first);
		this->m_front = second;
		return;
	}
	/* Nodes are placed apart and first index is not head */
	/* This is the general case where nodes are at some 
	 distance > 1 from each other and first index is not 
	located at the beginning of the list */
	LinkedNode<T> *prev_first = this->getNode(small_index - 1);
	LinkedNode<T> *first = prev_first->getNext();
	LinkedNode<T> *prev_second = this->getNode(big_index - 1);
	LinkedNode<T> *second = prev_second->getNext();
	LinkedNode<T> *next_second = second->getNext();
	prev_first->setNext(second);
	second->setNext(first->getNext());
	first->setNext(next_second);
	prev_second->setNext(first);
	return;
	/* Let's hope this works */
}

template <typename T> LinkedNode<T> *LinkedList<T>::getNode(int index) const
{
	LinkedNode<T> *entry = this->m_front;
	while (index--)
		entry = entry->getNext();
	return entry;
}

template <typename T> bool LinkedList<T>::exists(T what) const
{
	LinkedNode<T> *curr = this->m_front;
	while (curr != nullptr) {
		if (curr->getValue() == what)
			return true;
                curr = curr->getNext();
        }
	return false;
}

template <typename T> int LinkedList<T>::find(T what) const
{
        int ans = 1;
	LinkedNode<T> *curr = this->m_front;
	while (curr != nullptr) {
		if (curr->getValue() == what)
			return ans;
                curr = curr->getNext();
                ans += 1;
        }
	return -1;
}
#endif /* LINKEDLIST_HH */
