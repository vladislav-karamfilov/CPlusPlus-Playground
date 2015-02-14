#include <iostream>

#include "StudentWithMarks.h"

namespace StudentsSystem
{
	using namespace std;

	StudentWithMarks::StudentWithMarks(string name, string faculty, string facultyNumber, int groupNumber, double* firstSemesterMarks, double* secondSemesterMarks)
		: Student(name, faculty, facultyNumber, groupNumber)
	{
		this->SetFirstSemesterMarks(firstSemesterMarks);
		this->SetSecondSemesterMarks(secondSemesterMarks);
	}

	StudentWithMarks::~StudentWithMarks()
	{
		delete [] this->firstSemesterMarks;
		delete [] this->secondSemesterMarks;
	}

	double* StudentWithMarks::GetFirstSemesterMarks()
	{
		return this->firstSemesterMarks;
	}

	void StudentWithMarks::SetFirstSemesterMarks(double* firstSemesterMarks)
	{
		if (!firstSemesterMarks)
		{
			throw "First semester marks cannot be null!";
		}

		this->firstSemesterMarks = firstSemesterMarks;
	}

	double* StudentWithMarks::GetSecondSemesterMarks()
	{
		return this->secondSemesterMarks;
	}

	void StudentWithMarks::SetSecondSemesterMarks(double* secondSemesterMarks)
	{
		if (!secondSemesterMarks)
		{
			throw "Second semester marks cannot be null!";
		}

		this->secondSemesterMarks = secondSemesterMarks;
	}

	double StudentWithMarks::GetAverageMark()
	{
		double sum = 0;
		for (int i = 0; i < StudentWithMarks::SEMESTER_MARKS_COUNT; i++)
		{
			sum += this->firstSemesterMarks[i];
			sum += this->secondSemesterMarks[i];
		}

		return sum / (StudentWithMarks::SEMESTER_MARKS_COUNT * 2);
	}

	ostream& operator << (ostream& output, StudentWithMarks& student)
	{
		output << student.GetName() << " from " << student.GetGroupNumber() << " group first semester grades: ";
		for (int i = 0; i < StudentWithMarks::SEMESTER_MARKS_COUNT; i++)
		{
			output << student.GetFirstSemesterMarks()[i] << " ";
		}

		output << endl;

		output << student.GetName() << " from " << student.GetGroupNumber() << " group second semester grades: ";
		for (int i = 0; i < StudentWithMarks::SEMESTER_MARKS_COUNT; i++)
		{
			output << student.GetSecondSemesterMarks()[i] << " ";
		}

		output << endl << endl;

		return output;
	}
}