#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include "Person.h"
#include "Register.h"

using namespace std;
using namespace RegisterSystem;

static const int MAX_STRING_LENGTH = 256;
static const char* OUTPUT_FILE_NAME = "out.bin";

Register peopleRegister = Register();

void ReadPersonInfo(char* name, char* ssn, char* address)
{
	cout << "Enter person name: ";
	cin.getline(name, MAX_STRING_LENGTH);

	cout << "Enter person SSN: ";
	cin.getline(ssn, MAX_STRING_LENGTH);

	cout << "Enter person address: ";
	cin.getline(address, MAX_STRING_LENGTH);
}

void AddPersonToRegister()
{
	char* name = new char[MAX_STRING_LENGTH];
	char* ssn = new char[MAX_STRING_LENGTH];
	char* address = new char[MAX_STRING_LENGTH];

	ReadPersonInfo(name, ssn, address);

	Person* newPerson = new Person(name, ssn, address);

	peopleRegister.AddPerson(newPerson);
}

void RemovePersonFromRegister()
{
	char* ssn = new char[MAX_STRING_LENGTH];
	cout << "Enter SSN of the person to be removed: ";
	cin.getline(ssn, MAX_STRING_LENGTH);

	peopleRegister.RemovePerson(ssn);
}

void PrintPeopleAlphabeticallyOrdered()
{
	vector<Person*> peopleAlphabeticallyOrdered = peopleRegister.GetPeopleAlphabeticallyOrdered();
	int peopleCount = peopleAlphabeticallyOrdered.size();
	if (peopleCount > 0)
	{
		for (int i = 0; i < peopleCount; i++)
		{
			cout << *peopleAlphabeticallyOrdered[i] << endl;
		}
	}
	else
	{
		cout << "No people in the register!";
	}
}

int GetPeopleLivingOnAddressCount()
{
	char* address = new char[MAX_STRING_LENGTH];
	cout << "Enter address: ";
	cin.getline(address, MAX_STRING_LENGTH);

	return peopleRegister.GetPeopleOnAddressCount(address);
}

void WritePeopleOnBinaryFile(const char* fileName)
{
	ofstream outputFile;
	outputFile.open(fileName, ios::out | ios::binary | ios::app);

	outputFile << peopleRegister;

	outputFile.close();
}

int Menu()
{
	cout << "---Register System---" << endl;
	cout << "0 -> Add person" << endl;
	cout << "1 -> Remove person by SSN" << endl;
	cout << "2 -> Print people alphabetically ordered" << endl;
	cout << "3 -> Write people information in binary file" << endl;
	cout << "4 -> Get people living on an address" << endl;
	cout << "ESC -> Exit" << endl;

	cout << "Enter your choice: ";
	return _getche();
}

int main()
{
	int userChoice;
	try {
		do
		{
			userChoice = Menu();
			switch (userChoice)
			{
			case 48: // '0'
				cout << endl << endl;

				AddPersonToRegister();
				cout << "Person added!";

				cout << endl << endl;
				break;
			case 49: // '1'
				cout << endl << endl;

				RemovePersonFromRegister();

				cout << endl;
				break;
			case 50: // '2'
				cout << endl << endl;

				cout << "All people in the register: " << endl;
				PrintPeopleAlphabeticallyOrdered();

				cout << endl << endl;
				break;
			case 51: // '3'
				cout << endl << endl;

				WritePeopleOnBinaryFile(OUTPUT_FILE_NAME);
				cout << "All people from the register are written to the file '" << OUTPUT_FILE_NAME << "'!";

				cout << endl << endl;
				break;
			case 52: // '4'
				cout << endl << endl;

				cout << GetPeopleLivingOnAddressCount() << " people";

				cout << endl << endl;
				break;
			case 27: // 'ESC'
				cout << endl << endl;
				break;
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