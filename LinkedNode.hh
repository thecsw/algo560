/**
 * @file Node.hh
 * @class Node
 * @brief Single node to store next Node object's address and a value
 *
 * @author Sandy Urazayev
 *
 * @version 1.09
 *
 * Contact: ctu@ku.edu
 *
 */
#ifndef LINKED_NODE_HH
#define LINKED_NODE_HH

template <typename T> class LinkedNode {
    private:
	/* Pointer to the next node */
	LinkedNode<T> *m_next;

	/* The payload (carry value) */
	T m_value;

    public:
	/**
	 * @brief Consructor for Node class. 
	 * @param value payload for the Node 
	 *
	 * Allocates a Node with value value
	 **/
	LinkedNode(T);

	/**
	 * @brief Sets the object's next pointer
	 * @param Node class pointer
	 *
	 **/
	void setNext(LinkedNode<T> *);

	/**
	 * @brief Sets the object's payload
	 * @param value integer value to update
	 *
	 **/
	void setValue(T);

	/**
	 * @brief Return pointer to the next object
	 * @return Node* value to the next object
	 **/
	LinkedNode<T> *getNext() const;

	/**
	 * @brief Return value of the current object
	 * @return Integer value of the current Node (object)
	 **/
	T getValue() const;
};

template <typename T> LinkedNode<T>::LinkedNode(T value) : m_next(nullptr)
{
	this->m_value = value;
}

template <typename T> void LinkedNode<T>::setNext(LinkedNode<T> *next)
{
	this->m_next = next;
}

template <typename T> void LinkedNode<T>::setValue(T value)
{
	this->m_value = value;
}

template <typename T> LinkedNode<T> *LinkedNode<T>::getNext() const
{
	return this->m_next;
}

template <typename T> T LinkedNode<T>::getValue() const
{
	return this->m_value;
}
#endif /* LINKED_NODE_HH */
