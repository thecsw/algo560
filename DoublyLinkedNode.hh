#ifndef DOUBLY_NODE_HH
#define DOUBLY_NODE_HH

class DoublyLinkedNode {
    private:
	DoublyLinkedNode *_next;
	DoublyLinkedNode *_prev;
	int _value;

    public:
	// methods are self-explanatory, just getters and setters

	DoublyLinkedNode(int);
	void setNext(DoublyLinkedNode *);
	void setPrev(DoublyLinkedNode *);
	void setValue(int);
	DoublyLinkedNode *getNext() const;
	DoublyLinkedNode *getPrev() const;
	int getValue() const;
};

#endif /* DOUBLY_NODE_HH */
