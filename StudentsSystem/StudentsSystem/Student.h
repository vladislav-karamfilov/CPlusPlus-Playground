#ifndef STUDENT_GUARD
#define STUDENT_GUARD

#include <string>

#include "Person.h"

namespace StudentsSystem
{
	class Student : public Person
	{
	private:
		string faculty;
		string facultyNumber;
		int groupNumber;

	public:
		static const int FACULTY_NAME_MIN_LENGTH = 2;
		static const int FACULTY_NUMBER_MIN_LENGTH = 5;

		Student(string name, string faculty, string facultyNumber, int groupNumber);
		~Student();

		virtual string GetName() override
		{
			return Person::GetName();
		}

		string GetFaculty();
		void SetFaculty(string faculty);

		string GetFacultyNumber();
		void SetFacultyNumber(string facultyNumber);

		short GetGroupNumber();
		void SetGroupNumber(int groupNumber);
	};
}

#endif