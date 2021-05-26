/**
 * @file HashTable.cc
 * @class HashTable
 * @brief It's a hashtable lol
 *
 * @author Sandy Urazayev
 *
 * Contact: ctu@ku.edu

 *
 */
#ifndef HASHTABLE_HH
#define HASHTABLE_HH
#include "LinkedList.hh"
#include "Student.hh"

class OpenHashTable {
    private:
        // Linked lists of students
	LinkedList<Student *> **m_buckets;

        // Number of linked lists to store
	int m_bucket_size;

    public:
        // HashTable here takes the bucket size and initializes
        // and allocates m_bucket_size number of linked lists
	OpenHashTable(int);

        // Eagerly frees all the memory occupied by linked lists and
        // whatnot
	~OpenHashTable();

        // Takes a Student pointer and adds it to the hash table
	void AddStudent(Student *);

        // Removes the student by provided name and ID,
        // where both should match
	void RemoveStudent(std::string, int);

        // Return the 1 <= index <= n in the linked list
        // of the hashed name, where n is the size of
        // this->m_buckets(hash(name)) linked list
        // if id==-1, then we only use name for search
        // otherwise, match both the name and the id
        int FindStudent(std::string, int id=-1) const;

        // HashFunction returns the hash for buckets
        int Hashfunction(std::string) const;

        // PrintKeys just prints the whole hash table
        // while also printing the linked lists of every
        // bucket in the hash table
        void PrintKeys() const;
};
#endif /* HASHTABLE_HH */
