#include "pch.h"
#include "teamStore.h"
#include "../pm.types/team.h"

std::vector<pm::types::Team> teams;
pm::dal::TeamStore teamStore;

void pm::dal::TeamStore::createNewTeam(pm::types::Team& team)
{
	std::ofstream file("../../data/Teams.txt", std::ios::in | std::ios::ate);

	file << team.id << ',' << team.title << ',' << team.dateOfCreation << ',' << team.idOfCreator <<
		',' << team.dateOfLastChange << ',' << team.idOfChange << ',';

	file << '\n';

	file.close();
}

std::vector<pm::types::Team> pm::dal::TeamStore::getAll()
{
	teamStore.getData();
	return std::vector<pm::types::Team>(teams);
}

int pm::dal::TeamStore::generateNewId()
{
	int maxId = 0;

	teamStore.getData();
	teams = teamStore.getAll();

	for (auto team : teams)
	{
		if (team.id > maxId)
		{
			maxId = team.id;
		}
	}

	return maxId + 1;
}

void pm::dal::TeamStore::getData()	// Starts reading the Records.txt file so it can input information into it
{
	std::ifstream file("../../data/Teams.txt", std::fstream::in);
	teams.clear();

	std::string id, title, dateOfCreation, idOfCreator, dateOfLastChange, idOfChange, membersLine, next;
	std::vector<std::string> members;

	if (file.is_open())	// The file is successfully opened
	{
		while (std::getline(file, id, ','))
		{
			members.clear();
			std::getline(file, title, ',');
			std::getline(file, dateOfCreation, ',');
			std::getline(file, idOfCreator, ',');
			std::getline(file, dateOfLastChange, ',');
			std::getline(file, idOfChange, ',');
			std::getline(file, membersLine);
			membersLine = membersLine + '\n';

			while (membersLine != "\n")
			{
				size_t pos = membersLine.find(';');
				members.push_back(membersLine.substr(0, pos));
				membersLine.erase(0, pos + 1);
			}

			addToTeams(stoi(id), title, stoi(dateOfCreation), stoi(idOfCreator), stoi(dateOfLastChange), stoi(idOfChange), members);
		}

		file.close();
	}

	else	// there is a problem with the file
	{
		std::cout << "Enable to open the file!" << std::endl;
	}
}

void pm::dal::TeamStore::addToTeams(int id, std::string title, time_t dateOfCreation, int idOfCreator, time_t dateOfLastChange, int idOfChange, std::vector<std::string> members)
{
	pm::types::Team team;

	team.id = id;
	team.title = title;
	team.dateOfCreation = dateOfCreation;
	team.idOfCreator = idOfCreator;
	team.dateOfLastChange = dateOfLastChange;
	team.idOfChange = idOfChange;

	for (auto member : members)
	{
		team.members.push_back(member);
	}

	teams.push_back(team);
}

void pm::dal::TeamStore::update(std::vector<pm::types::Team> teams)
{
	std::ofstream file("../../data/Teams.txt", std::ios::in | std::ios::trunc);
	
	for (unsigned i = 0; i < teams.size(); i++)
	{
		pm::types::Team team = teams[i];

		file << team.id << ',';
		file << team.title << ',';
		file << team.dateOfCreation << ',';
		file << team.idOfCreator << ',';
		file << team.dateOfLastChange << ',';
		file << team.idOfChange << ',';

		for (auto member : team.members)
		{
			file << member << ';';
		}

		file << '\n';
	}

	file.close();
}

void pm::dal::TeamStore::remove(int delId)
{
	int index = -1;
	teamStore.getData();

	for (unsigned i = 0; i < teams.size(); i++)
	{
		if (teams[i].id == delId)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		std::cout << std::endl << "     Team with ID " << delId << " does not exist!";
		return;
	}

	teams.erase(teams.begin() + index);

	std::cout << std::endl << "     Team successfully removed!";

	teamStore.update(teams);
}

void pm::dal::TeamStore::assignUsers(int id, std::string user)
{
	teams.clear();
	teams = teamStore.getAll();

	for (unsigned i = 0; i < teams.size(); i++)
	{
		if (teams[i].id == id)
		{
			teams[i].members.push_back(user);
		}
	}

	teamStore.update(teams);
}