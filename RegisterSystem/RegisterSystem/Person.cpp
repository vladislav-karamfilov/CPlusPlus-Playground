#include <iostream>
#include "Person.h"

namespace RegisterSystem
{
	using namespace std;

	Person::Person(char* name, char* ssn, char* address)
	{
		this->SetName(name);
		this->SetSsn(ssn);
		this->SetAddress(address);
	}

	Person::~Person()
	{
		delete [] this->name;
		delete [] this->ssn;
		delete [] this->address;
	}

	void Person::SetName(char* name)
	{
		if (name == NULL)
		{
			throw "Person name cannot be null!";
		}

		if (strlen(name) < PERSON_NAME_MIN_LENGTH)
		{
			char* message = new char[80];
			sprintf(message, "Person name must be at least %d characters long!", PERSON_NAME_MIN_LENGTH);
			throw message;
		}

		this->name = name;
	}

	char* Person::GetName()
	{
		return this->name;
	}

	void Person::SetSsn(char* ssn)
	{
		if (ssn == NULL)
		{
			throw "Person SSN cannot be null!";
		}

		int ssnLength = strlen(ssn);
		if (ssnLength != PERSON_SSN_LENGTH)
		{
			char* message = new char[80];
			sprintf(message, "Person SSN must be %d characters long!", PERSON_SSN_LENGTH);
			throw message;
		}

		this->ssn = ssn;
	}

	char* Person::GetSsn()
	{
		return this->ssn;
	}

	void Person::SetAddress(char* address)
	{
		if (address == NULL)
		{
			throw "Person address cannot be null!";
		}

		if (strlen(address) < PERSON_ADDRESS_MIN_LENGTH)
		{
			char* message = new char[80];
			sprintf(message, "Person address must be at least %d characters long!", PERSON_ADDRESS_MIN_LENGTH);
			throw message;
		}

		this->address = address;
	}

	char* Person::GetAddress()
	{
		return this->address;
	}

	ostream& operator << (ostream& output, const Person& person)
	{
		output << "Name: " << person.name << endl;
		output << "SSN: " << person.ssn << endl;
		output << "Address: " << person.address << endl;

		return output;
	}
}