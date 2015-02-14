#ifndef PERSON_GUARD
#define PERSON_GUARD

#include <string>

namespace StudentsSystem
{
	using namespace std;

	class Person
	{
	private:
		string name;
		void SetName(string name);

	public:
		static const unsigned int PERSON_NAME_MIN_LENGTH = 8; // Min 2 characters for three names + 2 white spaces

		virtual string GetName() = 0;

	protected:
		Person(string name);
		~Person();
	};
}

#endif