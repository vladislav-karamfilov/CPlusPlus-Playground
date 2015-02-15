#include <iostream>

#include "PoliticalParty.h"

using namespace std;

namespace ElectionSystem
{
	PoliticalParty::PoliticalParty(char* name, int votesCount)
	{
		this->SetName(name);
		this->SetVotesCount(votesCount);
	}

	PoliticalParty::~PoliticalParty()
	{
		delete [] this->name;
	}

	void PoliticalParty::SetName(char* name)
	{
		if (name == NULL)
		{
			throw "Political party name cannot be null!";
		}

		if (strlen(name) < MIN_POLITICAL_PARTY_NAME_LENGTH)
		{
			char* message = new char[80];
			sprintf(message, "Political party name cannot be less than %d characters long!", MIN_POLITICAL_PARTY_NAME_LENGTH);
			throw message;
		}

		this->name = name;
	}

	char* PoliticalParty::GetName()
	{
		return this->name;
	}

	void PoliticalParty::SetVotesCount(int votesCount)
	{
		if (votesCount < 0)
		{
			throw "Political party votes count cannot be a negative number!";
		}

		this->votesCount = votesCount;
	}

	int PoliticalParty::GetVotesCount()
	{
		return this->votesCount;
	}

	ostream& operator << (ostream& output, const PoliticalParty& politicalParty)
	{
		output << politicalParty.name << " (" << politicalParty.votesCount << " votes)";

		return output;
	}
}