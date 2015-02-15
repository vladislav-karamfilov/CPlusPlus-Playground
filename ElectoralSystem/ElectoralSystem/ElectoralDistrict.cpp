#include <iostream>
#include <string>

#include "limits.h"
#include "ElectoralDistrict.h"

using namespace std;

namespace ElectionSystem
{
	ElectoralDistrict::ElectoralDistrict(char* name, int votersCount, int politicalPartiesCount, PoliticalParty** politicalParties)
	{
		this->SetName(name);
		this->SetVotersCount(votersCount);
		this->SetPoliticalPartiesCount(politicalPartiesCount);
		this->SetPoliticalParties(politicalParties);
	}

	ElectoralDistrict::~ElectoralDistrict()
	{
		delete [] this->name;
		delete [] this->politicalParties;
	}

	void ElectoralDistrict::SetName(char* name)
	{
		if (name == NULL)
		{
			throw "Electoral district name cannot be null!";
		}

		int nameLength = strlen(name);
		if (nameLength < MIN_ELECTORAL_DISTRICT_NAME_LENGTH || nameLength > MAX_ELECTORAL_DISTRICT_NAME_LENGTH)
		{
			char* message = new char[80];
			sprintf(
				message,
				"Electoral district name must be between %d and %d characters long!",
				MIN_ELECTORAL_DISTRICT_NAME_LENGTH,
				MAX_ELECTORAL_DISTRICT_NAME_LENGTH);

			throw message;
		}

		this->name = name;
	}

	char* ElectoralDistrict::GetName()
	{
		return this->name;
	}

	void ElectoralDistrict::SetVotersCount(int votersCount)
	{
		if (votersCount < 0)
		{
			throw "Electoral district voters count cannot be a negative number!";
		}

		this->votersCount = votersCount;
	}

	int ElectoralDistrict::GetVotersCount()
	{
		return this->votersCount;
	}

	void ElectoralDistrict::SetPoliticalPartiesCount(int politicalPartiesCount)
	{
		if (politicalPartiesCount < 0)
		{
			throw "Electoral district political parties count cannot be a negative number!";
		}

		this->politicalPartiesCount = politicalPartiesCount;
	}

	int ElectoralDistrict::GetPoliticalPartiesCount()
	{
		return this->politicalPartiesCount;
	}

	void ElectoralDistrict::SetPoliticalParties(PoliticalParty** politicalParties)
	{
		if (politicalParties == NULL)
		{
			throw "Political parties cannot be null!";
		}

		this->politicalParties = politicalParties;
	}

	PoliticalParty** ElectoralDistrict::GetPoliticalParties()
	{
		return this->politicalParties;
	}

	PoliticalParty* ElectoralDistrict::GetWinnerPoliticalParty()
	{
		int maxVotes = INT_MIN;
		PoliticalParty* maxVotesPoliticalParty;
		bool duplicatedWinner = false;
		for (int i = 0; i < this->politicalPartiesCount; i++)
		{
			if (this->politicalParties[i]->GetVotesCount() > maxVotes)
			{
				maxVotes = this->politicalParties[i]->GetVotesCount();
				maxVotesPoliticalParty = this->politicalParties[i];
				duplicatedWinner = false;
			}
			else if (this->politicalParties[i]->GetVotesCount() == maxVotes)
			{
				duplicatedWinner = true;
			}
		}

		if (duplicatedWinner)
		{
			return NULL;
		}
		else
		{
			return maxVotesPoliticalParty;
		}
	}

	ostream& operator << (ostream& output, const ElectoralDistrict& district)
	{
		output << "Electoral district: " << district.name << endl;
		output << "Voters count: " << district.votersCount << endl;

		output << "Political parties: ";
		if (district.politicalPartiesCount > 0)
		{
			for (int i = 0; i < district.politicalPartiesCount - 1; i++)
			{
				output << *district.politicalParties[i] << ", ";
			}

			output << *district.politicalParties[district.politicalPartiesCount - 1] << endl;
		}
		else
		{
			output << "no political parties" << endl;
		}

		return output;
	}
}