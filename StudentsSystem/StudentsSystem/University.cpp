#include <limits>

#include "University.h"

namespace StudentsSystem
{
	University::University(string name)
	{
		this->SetName(name);
		this->groupsStudents = map<int, vector<StudentWithMarks*>>();
	}

	University::~University()
	{
	}

	void University::SetName(string name)
	{
		if (name.length() < UNIVERSITY_NAME_MIN_LENGTH)
		{
			char* message = new char[80];
			sprintf(message, "University name cannot be less than %d characters long!", UNIVERSITY_NAME_MIN_LENGTH);
			throw message;
		}

		this->name = name;
	}

	string University::GetName()
	{
		return this->name;
	}

	vector<int> University::GetAllGroups()
	{
		vector<int> allGroups = vector<int>();
		for (map<int, vector<StudentWithMarks*>>::iterator i = this->groupsStudents.begin(); i != this->groupsStudents.end(); i++)
		{
			allGroups.push_back(i->first);
		}

		return allGroups;
	}

	vector<StudentWithMarks*> University::GetAllStudentsInGroup(int groupNumber)
	{
		map<int, vector<StudentWithMarks*>>::iterator group = this->groupsStudents.find(groupNumber);
		if (group == this->groupsStudents.end())
		{
			char* message = new char[80];
			sprintf(message, "There is no group '%d'!", groupNumber);
			throw message;
		}

		return group->second;
	}

	void University::AddStudent(StudentWithMarks* student)
	{
		if (student == NULL)
		{
			throw "Student cannot be null!";
		}

		int groupNumber = student->GetGroupNumber();
		map<int, vector<StudentWithMarks*>>::iterator existingGroupStudents = groupsStudents.find(groupNumber);
		if (existingGroupStudents == groupsStudents.end())
		{
			vector<StudentWithMarks*> groupStudents = vector<StudentWithMarks*>();
			groupStudents.push_back(student);
			groupsStudents.insert(pair<int, vector<StudentWithMarks*>>(groupNumber, groupStudents));
		}
		else
		{
			(existingGroupStudents->second).push_back(student);
		}
	}

	double University::GetAverageMark(int group)
	{
		map<int, vector<StudentWithMarks*>>::iterator groupStudents = this->groupsStudents.find(group);
		if (groupStudents == this->groupsStudents.end())
		{
			char* message = new char[80];
			sprintf(message, "There is no group '%d'!", group);
			throw message;
		}

		vector<StudentWithMarks*> students = groupStudents->second;
		vector<StudentWithMarks*>::size_type groupStudentsCount = students.size();
		if (groupStudentsCount == 0)
		{
			return 0;
		}

		double sum = 0;
		for (vector<StudentWithMarks*>::size_type i = 0; i < groupStudentsCount; i++)
		{
			sum += students[i]->GetAverageMark();
		}

		return sum / groupStudentsCount;
	}

	double University::GetMinimalAverageMarkInGroup(int groupNumber)
	{
		map<int, vector<StudentWithMarks*>>::iterator group = this->groupsStudents.find(groupNumber);
		if (group == this->groupsStudents.end())
		{
			char* message = new char[80];
			sprintf(message, "There is no group '%d'!", groupNumber);
			throw message;
		}

		double minimalAverageMark = INT_MAX;
		vector<StudentWithMarks*>::size_type studentsCount = group->second.size();
		for (vector<StudentWithMarks*>::size_type i = 0; i < studentsCount; i++)
		{
			double currentAverageMark = group->second[i]->GetAverageMark();
			if (minimalAverageMark > currentAverageMark)
			{
				minimalAverageMark = currentAverageMark;
			}
		}

		return minimalAverageMark;
	}

	double University::GetMaximalAverageMarkInGroup(int groupNumber)
	{
		map<int, vector<StudentWithMarks*>>::iterator group = this->groupsStudents.find(groupNumber);
		if (group == this->groupsStudents.end())
		{
			char* message = new char[80];
			sprintf(message, "There is no group '%d'!", groupNumber);
			throw message;
		}

		double maximalAverageMark = INT_MIN;
		vector<StudentWithMarks*>::size_type studentsCount = group->second.size();
		for (vector<StudentWithMarks*>::size_type i = 0; i < studentsCount; i++)
		{
			double currentAverageMark = group->second[i]->GetAverageMark();
			if (maximalAverageMark < currentAverageMark)
			{
				maximalAverageMark = currentAverageMark;
			}
		}

		return maximalAverageMark;
	}
}