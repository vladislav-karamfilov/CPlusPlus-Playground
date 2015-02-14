#ifndef PERSON_GUARD
#define PERSON_GUARD

#include <iostream>

namespace RegisterSystem
{
	using namespace std;

	class Person
	{
	private:
		char* name;
		char* ssn;
		char* address;

	public:
		static const unsigned int PERSON_NAME_MIN_LENGTH = 8; // Min two letters for name + two white spaces
		static const unsigned int PERSON_SSN_LENGTH = 10; // Bulgarian EGN length
		static const unsigned int PERSON_ADDRESS_MIN_LENGTH = 10; // Some random value...

		Person(char* name, char* ssn, char* address);
		~Person();

		void SetName(char* name);
		char* GetName();

		void SetSsn(char* ssn);
		char* GetSsn();

		void SetAddress(char* address);
		char* GetAddress();

		friend ostream& operator << (ostream& output, const Person& person);
	};
}

#endif