#ifndef PEOPLE_COMPARER_GUARD
#define PEOPLE_COMPARER_GUARD

#include "Person.h"

namespace RegisterSystem
{
	struct PeopleComparer
	{
		inline bool operator() (Person* first, Person* second)
		{
			return strcmpi(first->GetName(), second->GetName()) < 0;
		}
	};
}

#endif