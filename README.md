# algo560
Implementations of various data structures taught in EECS 560: Data Structures. 
This is simply a repo that contains some header files and their respective 
sources from my lab submissions for the course. Some classes are properly 
documented, some are not. Oh well

Here is a list of data structures that you can comfortably use
(some helper classes, such as `BinarySearchNode`, which is used internally
by `BinarySearchTree` would be omitted, as they're not intended for direct use):

- `BinarySearchTree`: Implementation of a templated
  [Binary Search Tree](https://en.wikipedia.org/wiki/Binary_search_tree)
- `ClosedHashTable`: Implementation of an 
  [Open addressing](https://en.wikipedia.org/wiki/Open_addressing) hash table.
- `OpenHashTable`: Implementation of a Closed addressing hash table.
- `DisjointSet`: Implementation of [Disjoint Sets](https://en.wikipedia.org/wiki/Disjoint_sets).
- `DoublyLinkedList`: Implementation of a 
  [Doubly Linked List](https://en.wikipedia.org/wiki/Doubly_linked_list.)
- `Heap`: Implementation of a standard min or max 
  [Priority Queue](https://en.wikipedia.org/wiki/Priority_queue).
- `Leftist`: Implementation of a [Leftist Tree](https://en.wikipedia.org/wiki/Leftist_tree)
  priority queue.
- `LinkedList`: Implementation of a templated [Linked List](https://en.wikipedia.org/wiki/Linked_list).
- `MinMaxHeap`: Implementation of a [Min-max heap](https://en.wikipedia.org/wiki/Min-max_heap)
  priority queue.

*Note:* For one of the labs on `OpenHashTable`, where we make hashtable that consists
of linked lists, I wrote a class-specific implementation for `Student`. Can't be bothered
to rewrite, as open addressing is usually better. For legacy and consistency purposes, I 
will leave both of the classes here.
