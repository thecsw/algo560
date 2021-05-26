#include "Student.hh"
#include <string>

Student::Student(int id, std::string name) : m_id(id), m_name(name)
{
}

void Student::setID(int id)
{
	this->m_id = id;
}

void Student::setName(std::string name)
{
	this->m_name = name;
}

int Student::getID() const
{
	return this->m_id;
}

std::string Student::getName() const
{
	return this->m_name;
}

bool Student::operator==(const Student &rhs)
{
	return this->m_name == rhs.getName();
}
