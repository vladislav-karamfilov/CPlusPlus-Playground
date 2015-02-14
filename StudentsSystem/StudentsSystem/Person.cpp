#include "Person.h"

namespace StudentsSystem
{
	using namespace std;

	Person::Person(string name)
	{
		this->SetName(name);
	}

	Person::~Person()
	{
	}

	string Person::GetName()
	{
		return this->name;
	}

	void Person::SetName(string name)
	{
		if (name.length() < PERSON_NAME_MIN_LENGTH)
		{
			char* message = new char[80];
			sprintf(message, "Person name cannot be less than %d characters long!", PERSON_NAME_MIN_LENGTH);
			throw message;
		}

		this->name = name;
	}
}