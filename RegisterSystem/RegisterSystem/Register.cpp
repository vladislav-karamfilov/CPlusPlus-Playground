#include <iostream>
#include <vector>
#include <algorithm>
#include "Register.h"
#include "PeopleComparer.h"

namespace RegisterSystem
{
	using namespace std;

	Register::Register()
	{
		this->people = vector<Person*>();
	}

	Register::~Register()
	{
		int peopleCount = this->people.size();
		for (int i = 0; i < peopleCount; i++)
		{
			delete this->people[i];
		}
	}

	void Register::AddPerson(Person* person)
	{
		if (person == NULL)
		{
			throw "Cannot add a null person in the register!";
		}

		this->people.push_back(person);
	}

	void Register::RemovePerson(const char* ssn)
	{
		int searchedPersonIndex = -1;

		int peopleCount = this->people.size();
		for (int i = 0; i < peopleCount; i++)
		{
			if (strcmp(this->people[i]->GetSsn(), ssn) == 0)
			{
				searchedPersonIndex = i;
				break;
			}
		}

		if (searchedPersonIndex >= 0)
		{
			this->people.erase(this->people.begin() + searchedPersonIndex);
		}
	}

	vector<Person*> Register::GetPeopleAlphabeticallyOrdered()
	{
		vector<Person*> alphabeticallyOrderedPeople = this->people;

		sort(alphabeticallyOrderedPeople.begin(), alphabeticallyOrderedPeople.end(), PeopleComparer());

		return alphabeticallyOrderedPeople;
	}

	int Register::GetPeopleOnAddressCount(const char* address)
	{
		int peopleOnAddress = 0;

		int peopleCount = this->people.size();
		for (int i = 0; i < peopleCount; i++)
		{
			if (strcmp(this->people[i]->GetAddress(), address))
			{
				peopleCount++;
			}
		}

		return peopleCount;
	}

	ostream& operator << (ostream& output, const Register& peopleRegister)
	{
		int peopleCount = peopleRegister.people.size();
		if (peopleCount > 0)
		{
			for (int i = 0; i < peopleCount; i++)
			{
				output << *peopleRegister.people[i] << endl;
			}
		}
		else
		{
			output << "No people in the register!" << endl;
		}

		return output;
	}
}