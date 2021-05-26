#ifndef STUDENT_HH
#define STUDENT_HH
#include <string>

class Student {
    private:
	int m_id;
	std::string m_name;

    public:
	Student(int, std::string);
	void setID(int);
	void setName(std::string);
	int getID() const;
	std::string getName() const;
	bool operator==(const Student &);
};

#endif /* STUDENT_HH */
