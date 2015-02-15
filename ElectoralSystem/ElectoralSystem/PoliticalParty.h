#ifndef POLITICAL_PARTY_GUARD
#define POLITICAL_PARTY_GUARD

#include <iostream>

namespace ElectionSystem
{
	using namespace std;

	class PoliticalParty
	{
	private:
		char* name;
		int votesCount;

	public:
		static const int MIN_POLITICAL_PARTY_NAME_LENGTH = 2;
		static const int MAX_POLITICAL_PARTY_NAME_LENGTH = 80;

		PoliticalParty(char* name, int votesCount);
		~PoliticalParty();

		void SetName(char* name);
		char* GetName();

		void SetVotesCount(int votesCount);
		int GetVotesCount();

		friend ostream& operator << (ostream& output, const PoliticalParty& politicalParty);
	};
}

#endif