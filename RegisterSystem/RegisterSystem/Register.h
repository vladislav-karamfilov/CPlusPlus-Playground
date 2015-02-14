#ifndef REGISTER_GUARD
#define REGISTER_GUARD

#include <vector>
#include "Person.h"

namespace RegisterSystem
{
	class Register
	{
	private:
		vector<Person*> people;

	public:
		Register();
		~Register();

		void AddPerson(Person* person);

		void RemovePerson(const char* ssn);

		vector<Person*> GetPeopleAlphabeticallyOrdered();

		int GetPeopleOnAddressCount(const char* address);

		friend ostream& operator << (ostream& output, const Register& peopleRegister);
	};
}

#endif