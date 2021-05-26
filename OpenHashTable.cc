#include "OpenHashTable.hh"
#include "LinkedList.hh"
#include "Student.hh"
#include <stdexcept>

OpenHashTable::OpenHashTable(int bucket_size)
{
	this->m_bucket_size = bucket_size;
	this->m_buckets = new LinkedList<Student *> *[this->m_bucket_size];
	for (int i = 0; i < this->m_bucket_size; i++)
		this->m_buckets[i] = new LinkedList<Student *>();
}

OpenHashTable::~OpenHashTable()
{
	for (int i = 0; i < this->m_bucket_size; i++) {
		LinkedList<Student *> *list = this->m_buckets[i];
		for (int i = 1; i <= list->getLength(); i++)
			delete list->getEntry(i);
		delete list;
	}
	delete[] this->m_buckets;
}

int OpenHashTable::Hashfunction(std::string what) const
{
	int sum = 0;
	for (int i = 0; i < what.size(); i++)
		sum += char(what.at(i));
	return sum % this->m_bucket_size;
}

void OpenHashTable::AddStudent(Student *what)
{
	if (what == nullptr)
		throw std::runtime_error("Insert student is null.");
	int loc = this->FindStudent(what->getName());
	if (loc != -1)
		throw std::runtime_error("Student already exists.");
	this->m_buckets[this->Hashfunction(what->getName())]->addBack(what);
}

void OpenHashTable::RemoveStudent(std::string name, int id)
{
	int loc = this->FindStudent(name, id);
	if (loc == -1)
		throw std::runtime_error("No record found");
	delete this->m_buckets[this->Hashfunction(name)]->getEntry(loc);
	this->m_buckets[this->Hashfunction(name)]->remove(loc);
}

int OpenHashTable::FindStudent(std::string name, int id) const
{
	int hash = this->Hashfunction(name);
	LinkedList<Student *> *list = this->m_buckets[hash];
	for (int i = 1; i <= list->getLength(); i++)
		if (list->getEntry(i)->getName() == name) {
			// Only matching name
			if (id == -1)
				return i;
			// Try to match the ID as well
			if (list->getEntry(i)->getID() == id)
				return i;
		}
	return -1;
}

void OpenHashTable::PrintKeys() const
{
	for (int i = 0; i < this->m_bucket_size; i++) {
		std::cout << i << ":";
		LinkedList<Student *> *list = this->m_buckets[i];
		for (int j = 1; j <= list->getLength(); j++)
			std::cout << " -> " << list->getEntry(j)->getID() << " "
				  << list->getEntry(j)->getName();
		std::cout << std::endl;
	}
}
