#ifndef STUDENTWITHMARKS_GUARD
#define STUDENTWITHMARKS_GUARD

#include <string>

#include "Student.h"

namespace StudentsSystem
{
	class StudentWithMarks : public Student
	{
	private:
		double* firstSemesterMarks;
		double* secondSemesterMarks;

	public:
		static const int SEMESTER_MARKS_COUNT = 5;

		StudentWithMarks(string name, string faculty, string facultyNumber, int groupNumber, double* firstSemesterMarks, double* secondSemesterMarks);
		~StudentWithMarks();

		double* GetFirstSemesterMarks();
		void SetFirstSemesterMarks(double* firstSemesterMarks);

		double* GetSecondSemesterMarks();
		void SetSecondSemesterMarks(double* secondSemesterMarks);

		double GetAverageMark();

		friend ostream& operator << (ostream& output, StudentWithMarks& student);
	};
}

#endif