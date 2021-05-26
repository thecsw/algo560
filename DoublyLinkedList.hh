#ifndef DLINKED_LIST_HH
#define DLINKED_LIST_HH

#include "DoublyLinkedNode.hh"

class DoublyLinkedList {
    private:
	// _head is the first node in the list.
	DoublyLinkedNode *_head;

	// _tail is the last node in the list.
	DoublyLinkedNode *_tail;

	// _length is the number of nodes in the list.
	int _length;

        // findNode returns pointer to value node if found, null otherwise.
        DoublyLinkedNode* findNode(int);

    public:
	// DoublyLinkedList returns an instance of DoublyLinkedList.
	DoublyLinkedList();

	// ~DoubleLinkedList frees all the nodes and clears the memory.
	~DoublyLinkedList();

	// isEmpty returns true if list is empty, false otherwise.
	bool isEmpty() const;

	// getLength returns the number of elements in the list.
	int getLength() const;

	// insert appends a value at the tail of the list.
	void insert(int);

	// remove removes the passed value from the list.
	void remove(int);

	// find return true if value is found, false otherwise.
	bool find(int);

	// findPrev return value previous to the one passed.
	int findPrev(int);

	// forwardTraverse returns an array of all values head->tail.
	int *forwardTraverse();

	// backwardTraverse returns an array of all values tail->head.
	int *backwardTraverse();
};

#endif /* DLINKED_LIST_HH*/
