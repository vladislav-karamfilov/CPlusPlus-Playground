#ifndef ELECTIONDISTRICT_GUARD
#define ELECTIONDISTRICT_GUARD

#include "PoliticalParty.h"

namespace ElectionSystem
{
	using namespace std;

	class ElectoralDistrict
	{
	private:
		char* name;
		int votersCount;
		int politicalPartiesCount;
		PoliticalParty** politicalParties;

	public:
		static const int MAX_POLITICAL_PARTIES_COUNT = 80; // Some random value...
		static const int MIN_ELECTORAL_DISTRICT_NAME_LENGTH = 10; // Some random value...
		static const int MAX_ELECTORAL_DISTRICT_NAME_LENGTH = 80; // Some random value...

		ElectoralDistrict(char* name, int votersCount, int politicalPartiesCount, PoliticalParty** politicalParties);
		~ElectoralDistrict();

		void SetName(char* name);
		char* GetName();

		void SetVotersCount(int votersCount);
		int GetVotersCount();

		void SetPoliticalPartiesCount(int politicalPartiesCount);
		int GetPoliticalPartiesCount();

		void SetPoliticalParties(PoliticalParty** politicalParties);
		PoliticalParty** GetPoliticalParties();

		PoliticalParty* GetWinnerPoliticalParty();

		friend ostream& operator << (ostream& output, const ElectoralDistrict& district);
	};
}

#endif