#include "Student.h"

namespace StudentsSystem
{
	using namespace std;

	Student::Student(string name, string faculty, string facultyNumber, int groupNumber)
		: Person(name)
	{
		this->SetFaculty(faculty);
		this->SetFacultyNumber(facultyNumber);
		this->SetGroupNumber(groupNumber);
	}

	Student::~Student()
	{
	}

	string Student::GetFaculty()
	{
		return this->faculty;
	}

	void Student::SetFaculty(string faculty)
	{
		if (faculty.length() < FACULTY_NAME_MIN_LENGTH)
		{
			char* message = new char[80];
			sprintf(message, "Faculty name must be at least %d characters long!", FACULTY_NAME_MIN_LENGTH);
			throw message;
		}

		this->faculty = faculty;
	}

	string Student::GetFacultyNumber()
	{
		return this->facultyNumber;
	}

	void Student::SetFacultyNumber(string facultyNumber)
	{
		if (facultyNumber.length() < FACULTY_NUMBER_MIN_LENGTH)
		{
			char* message = new char[80];
			sprintf(message, "Faculty number must be at least %d characters long!", FACULTY_NUMBER_MIN_LENGTH);
			throw message;
		}

		for (size_t i = 0; i < facultyNumber.length(); i++)
		{
			if (facultyNumber[i] < '0' || facultyNumber[i] > '9')
			{
				throw "Faculty number cannot contain other characters than digits!";
			}
		}

		this->facultyNumber = facultyNumber;
	}

	short Student::GetGroupNumber()
	{
		return this->groupNumber;
	}

	void Student::SetGroupNumber(int groupNumber)
	{
		if (groupNumber < 0)
		{
			throw "Group number cannot be negative!";
		}

		this->groupNumber = groupNumber;
	}
}