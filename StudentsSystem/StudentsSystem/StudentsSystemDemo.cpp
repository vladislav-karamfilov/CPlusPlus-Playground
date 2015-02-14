#include <iostream>
#include <fstream>
#include <conio.h>

#include "Person.h"
#include "Student.h"
#include "StudentWithMarks.h"
#include "University.h"

using namespace std;
using namespace StudentsSystem;

static const char* OUTPUT_FILE_NAME = "out.txt";

University* testUniversity = new University("Test Uni");

ofstream outputFile;

#pragma region Adding new student

void ReadStudentInfo(string& name, string& faculty, string& facultyNumber, int& groupNumber)
{
	cout << "Enter student name: ";
	getline(cin, name);

	cout << "Enter student faculty: ";
	getline(cin, faculty);

	cout << "Enter faculty number: ";
	getline(cin, facultyNumber);

	cout << "Enter group number: ";
	cin >> groupNumber;
}

void ReadStudentWithMarksInfo(string& name, string& faculty, string& facultyNumber, int& groupNumber, double* firstSemesterMarks, double* secondSemesterMarks)
{
	ReadStudentInfo(name, faculty, facultyNumber, groupNumber);

	double mark;
	for (int i = 0; i < StudentWithMarks::SEMESTER_MARKS_COUNT; i++)
	{
		mark = 0;
		while (mark < 2 || mark > 6)
		{
			cout << "Enter first semester mark #" << (i + 1) << ": ";
			cin >> mark;
		}

		firstSemesterMarks[i] = mark;
	}

	for (int i = 0; i < StudentWithMarks::SEMESTER_MARKS_COUNT; i++)
	{
		mark = 0;
		while (mark < 2 || mark > 6)
		{
			cout << "Enter second semester mark #" << (i + 1) << ": ";
			cin >> mark;
		}

		secondSemesterMarks[i] = mark;
	}

	cin.ignore();
}

void AddStudent()
{
	string name;
	string faculty;
	string facultyNumber;
	int groupNumber;
	double* firstSemesterMarks = new double[StudentWithMarks::SEMESTER_MARKS_COUNT];
	double* secondSemesterMarks = new double[StudentWithMarks::SEMESTER_MARKS_COUNT];

	ReadStudentWithMarksInfo(name, faculty, facultyNumber, groupNumber, firstSemesterMarks, secondSemesterMarks);

	StudentWithMarks* newStudent = new StudentWithMarks(name, faculty, facultyNumber, groupNumber, firstSemesterMarks, secondSemesterMarks);

	testUniversity->AddStudent(newStudent);
}

#pragma endregion

void WriteStudentsToFile(vector<StudentWithMarks*> students, ofstream& file)
{
	for (vector<StudentWithMarks*>::size_type i = 0; i < students.size(); i++)
	{
		file << *students[i] << endl;
	}
}

int Menu()
{
	cout << "---Students System---" << endl;
	cout << "0 -> Enter student" << endl;
	cout << "1 -> Get average mark for every group" << endl;
	cout << "2 -> Get minimal average mark of student in a group" << endl;
	cout << "3 -> Get maximal average mark of student in a group" << endl;
	cout << "4 -> Get marks of all students" << endl;
	cout << "5 -> Get marks of all students in a group" << endl;
	cout << "ESC -> Exit" << endl;

	cout << "Enter your choice: ";
	return _getche();
}

int main()
{
	short groupNumber;

	int userChoice;
	try {
		do
		{
			userChoice = Menu();
			switch (userChoice)
			{
			case 48: // '0'
			{
				cout << endl << endl;

				AddStudent();
				cout << "Student added!";

				cout << endl << endl;
				break;
			}
			case 49: // '1'
			{
				cout << endl << endl;

				outputFile.open(OUTPUT_FILE_NAME, ios::app);
				outputFile << "All groups average marks:" << endl;

				vector<int> allGroups = testUniversity->GetAllGroups();
				for (vector<int>::size_type i = 0; i < allGroups.size(); i++)
				{
					outputFile << "Group '" << allGroups[i] << "' average mark: " << testUniversity->GetAverageMark(allGroups[i]) << endl;
				}

				outputFile << endl;
				outputFile.close();

				cout << endl;
				break;
			}
			case 50: // '2'
			{
				cout << endl << endl;

				outputFile.open(OUTPUT_FILE_NAME, ios::app);
				cout << "Enter group number: ";
				cin >> groupNumber;
				outputFile << "Minimal average mark of student in group '" << groupNumber << "': ";
				try
				{
					outputFile << testUniversity->GetMinimalAverageMarkInGroup(groupNumber) << endl;
				}
				catch (char* ex)
				{
					outputFile << ex << endl;
				}

				outputFile << endl;
				outputFile.close();

				cout << endl << endl;
				break;
			}
			case 51: // '3'
			{
				cout << endl << endl;

				outputFile.open(OUTPUT_FILE_NAME, ios::app);
				cout << "Enter group number: ";
				cin >> groupNumber;
				outputFile << "Maximal average mark of student in group '" << groupNumber << "': ";
				try
				{
					outputFile << testUniversity->GetMaximalAverageMarkInGroup(groupNumber) << endl;
				}
				catch (char* ex)
				{
					outputFile << ex << endl;
				}

				outputFile << endl;
				outputFile.close();

				cout << endl << endl;
				break;
			}
			case 52: // '4'
			{
				cout << endl << endl;

				outputFile.open(OUTPUT_FILE_NAME, ios::app);
				outputFile << "All students marks:" << endl;
				vector<int> allGroups = testUniversity->GetAllGroups();
				for (vector<int>::size_type i = 0; i < allGroups.size(); i++)
				{
					vector<StudentWithMarks*> groupStudents = testUniversity->GetAllStudentsInGroup(allGroups[i]);
					WriteStudentsToFile(groupStudents, outputFile);
				}

				outputFile.close();

				cout << endl << endl;
				break;
			}
			case 53: // '5'
			{
				cout << endl << endl;

				cout << "Enter group number: ";
				cin >> groupNumber;
				vector<StudentWithMarks*> groupStudents = testUniversity->GetAllStudentsInGroup(groupNumber);
				
				outputFile.open(OUTPUT_FILE_NAME, ios::app);
				if (groupStudents.size() > 0)
				{
					outputFile << "All students marks from group '" << groupNumber << "':" << endl;
					WriteStudentsToFile(groupStudents, outputFile);
				}
				else
				{
					outputFile << "There is no group '" << groupNumber << "'!" << endl;
				}

				outputFile.close();

				cout << endl << endl;
				break;
			}
			case 27: // 'ESC'
			{
				cout << endl << endl;
				break;
			}
			default:
				cout << endl << "Invalid input!" << endl << endl;
				break;
			}

		} while (userChoice != 27);
	}
	catch (char* ex)
	{
		cout << ex << endl << endl;
	}

	return 0;
}
