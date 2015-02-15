#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <algorithm>

#include "ElectoralDistrict.h"

using namespace std;
using namespace ElectionSystem;

static const char* ELECTORAL_DISTRICTS_FILE_NAME = "electoral-districts.txt";
static const char* ELECTORAL_DISTRICTS_WINNERS_FILE_NAME = "electoral-districts-winners.txt";

ofstream outputFile;

vector<ElectoralDistrict*> electoralDistricts = vector<ElectoralDistrict*>();

void ReadPoliticalParties(PoliticalParty** politicalParties, int politicalPartiesCount)
{
	char* name;
	int votes;

	for (int i = 0; i < politicalPartiesCount; i++)
	{
		name = new char[PoliticalParty::MAX_POLITICAL_PARTY_NAME_LENGTH];

		cin.ignore();

		cout << "Enter political party #" << (i + 1) << " name: ";
		cin.getline(name, PoliticalParty::MAX_POLITICAL_PARTY_NAME_LENGTH);

		cout << "Enter political party #" << (i + 1) << " votes: ";
		cin >> votes;

		politicalParties[i] = new PoliticalParty(name, votes);
	}

	cin.ignore();
}

void ReadElectoralDistrictInfo(char* name, int& votersCount, int& politicalPartiesCount, PoliticalParty** politicalParties)
{
	cout << "Enter name: ";
	cin.getline(name, ElectoralDistrict::MAX_ELECTORAL_DISTRICT_NAME_LENGTH);

	cout << "Enter voters count: ";
	cin >> votersCount;

	cout << "Enter political parties count: ";
	cin >> politicalPartiesCount;

	ReadPoliticalParties(politicalParties, politicalPartiesCount);
}

void AddElectoralDistrict()
{
	char* name = new char[ElectoralDistrict::MAX_ELECTORAL_DISTRICT_NAME_LENGTH];
	int votersCount;
	int politicalPartiesCount;
	PoliticalParty** politicalParties = new PoliticalParty*[ElectoralDistrict::MAX_POLITICAL_PARTIES_COUNT];

	ReadElectoralDistrictInfo(name, votersCount, politicalPartiesCount, politicalParties);

	ElectoralDistrict* newElectoralDistrict = new ElectoralDistrict(name, votersCount, politicalPartiesCount, politicalParties);
	
	electoralDistricts.push_back(newElectoralDistrict);
}

void WriteAllElectoralDistrictsToFile(const char* filename)
{
	outputFile.open(filename, ios::app);

	vector<ElectoralDistrict*>::size_type electoralDistrictsCount = electoralDistricts.size();
	for (vector<ElectoralDistrict*>::size_type i = 0; i < electoralDistrictsCount; i++)
	{
		outputFile << *electoralDistricts[i] << endl;
	}

	outputFile.close();
}

void PrintElectoralDistrictsWithoutWinner()
{
	vector<ElectoralDistrict*>::size_type electoralDistrictsCount = electoralDistricts.size();
	for (vector<ElectoralDistrict*>::size_type i = 0; i < electoralDistrictsCount; i++)
	{
		if ((*electoralDistricts[i]).GetWinnerPoliticalParty() == NULL)
		{
			cout << *electoralDistricts[i] << endl;
		}
	}
}

void PrintElectoralDistrictsWithWinner(const char* winnerName)
{
	vector<char*> electoralDistrictsWithWinner = vector<char*>();

	vector<ElectoralDistrict*>::size_type electoralDistrictsCount = electoralDistricts.size();
	for (vector<ElectoralDistrict*>::size_type i = 0; i < electoralDistrictsCount; i++)
	{
		PoliticalParty* politicalPartyWinner = electoralDistricts[i]->GetWinnerPoliticalParty();
		if (politicalPartyWinner != NULL && strcmp(politicalPartyWinner->GetName(), winnerName) == 0)
		{
			electoralDistrictsWithWinner.push_back((*electoralDistricts[i]).GetName());
		}
	}

	sort(electoralDistrictsWithWinner.begin(), electoralDistrictsWithWinner.end());

	cout << "Electoral districts with winner '" << winnerName << "' are: ";
	vector<char*>::size_type electoralDistrictsWithWinnerCount = electoralDistrictsWithWinner.size();
	if (electoralDistrictsWithWinnerCount > 0)
	{
		for (vector<char*>::size_type i = 0; i < electoralDistrictsWithWinnerCount - 1; i++)
		{
			cout << electoralDistrictsWithWinner[i] << ", ";
		}

		cout << electoralDistrictsWithWinner[electoralDistrictsWithWinnerCount - 1] << endl;
	}
	else
	{
		cout << "No winners with name '" << winnerName << "'!";
	}
}

void WriteElectoralDistrictsWinnersToFile(const char* filename)
{
	outputFile.open(filename, ios::app);

	vector<ElectoralDistrict*>::size_type electoralDistrictsCount = electoralDistricts.size();
	for (vector<ElectoralDistrict*>::size_type i = 0; i < electoralDistrictsCount; i++)
	{
		PoliticalParty* politicalPartyWinner = (*electoralDistricts[i]).GetWinnerPoliticalParty();
		outputFile << "Electoral district '" << (*electoralDistricts[i]).GetName() << "' with winner political party: ";
		if (politicalPartyWinner != NULL)
		{
			outputFile << politicalPartyWinner->GetName() << endl;
		}
		else
		{
			outputFile << "no winner" << endl;
		}
	}

	outputFile.close();
}

int Menu()
{
	cout << "---Election System---" << endl;
	cout << "0 -> Enter electoral district" << endl;
	cout << "1 -> Write all electoral districts to a file" << endl;
	cout << "2 -> Get electoral districts with specified political party winner" << endl;
	cout << "3 -> Write electoral districts with their winners to a file" << endl;
	cout << "4 -> Get electoral districts without winner" << endl;
	cout << "ESC -> Exit" << endl;

	cout << "Enter your choice: ";
	return _getche();
}

int main()
{
	char* politicalPartyName = new char[80];

	int userChoice;
	try {
		do
		{
			userChoice = Menu();
			switch (userChoice)
			{
			case 48: // '0'
				cout << endl << endl;

				AddElectoralDistrict();
				cout << "Electoral district added!";

				cout << endl << endl;
				break;
			case 49: // '1'
				cout << endl << endl;

				WriteAllElectoralDistrictsToFile(ELECTORAL_DISTRICTS_FILE_NAME);
				cout << "All electoral districts written to a file!" << endl;

				break;
			case 50: // '2'
				cout << endl << endl;

				cout << "Enter political party name: ";
				cin >> politicalPartyName;
				PrintElectoralDistrictsWithWinner(politicalPartyName);

				cout << endl << endl;
				break;
			case 51: // '3'
				cout << endl << endl;

				WriteElectoralDistrictsWinnersToFile(ELECTORAL_DISTRICTS_WINNERS_FILE_NAME);
				cout << "All districts with their winners written to a file!" << endl;

				cout << endl;
				break;
			case 52: // '4'
				cout << endl << endl;

				cout << "All electoral districts without winner: " << endl;
				PrintElectoralDistrictsWithoutWinner();

				cout << endl << endl;
				break;
			case 27:
				cout << endl << endl;
				break;
			default:
				cout << endl << "Invalid input!" << endl << endl;
				break;
			}
		} while (userChoice != 27);
	}
	catch (char* ex)
	{
		cout << ex << endl << endl;
	}

	return 0;
}