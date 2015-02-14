#ifndef STUDENTS_SYSTEM_GUARD
#define STUDENTS_SYSTEM_GUARD

#include <map>
#include <vector>

#include "StudentWithMarks.h"

namespace StudentsSystem
{
	class University
	{
	private:
		string name;
		map<int, vector<StudentWithMarks*>> groupsStudents;
		void SetName(string name);

	public:
		static const unsigned int UNIVERSITY_NAME_MIN_LENGTH = 3;

		University(string name);
		~University();

		string GetName();

		vector<int> GetAllGroups();

		vector<StudentWithMarks*> GetAllStudentsInGroup(int group);

		void AddStudent(StudentWithMarks* student);
		
		double GetAverageMark(int group);

		double GetMinimalAverageMarkInGroup(int group);

		double GetMaximalAverageMarkInGroup(int group);
	};
}

#endif