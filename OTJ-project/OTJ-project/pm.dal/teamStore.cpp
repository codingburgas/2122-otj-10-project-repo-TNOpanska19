/*****************************************************************//**
 * \file   teamStore.cpp
 * \brief  Source file for team storing
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "teamStore.h"
#include "../pm.types/team.h"

/// <summary>
/// Object of TeamStore structure
/// </summary>
pm::dal::TeamStore teamStore;
/// <summary>
/// Vector of type Team. Used to store teams
/// </summary>
std::vector<pm::types::Team> teams;

/// <summary>
/// Used for getting team data from database (.txt file)
/// </summary>
void pm::dal::TeamStore::getData()
{
	std::string id, title, dateOfCreation, idOfCreator, dateOfLastChange, idOfChange, membersLine, next;
	std::vector<std::string> members;

	std::ifstream file("../../data/Teams.txt", std::fstream::in);	// Open Teams.txt
	teams.clear();	// Clear vector of teams so there is no repeating

	while (std::getline(file, id, '^'))
	{
		members.clear();
		std::getline(file, title, '^');
		std::getline(file, dateOfCreation, '^');
		std::getline(file, idOfCreator, '^');
		std::getline(file, dateOfLastChange, '^');
		std::getline(file, idOfChange, '^');
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

/// <summary>
/// Used for adding a new team in the database (.txt file)
/// </summary>
/// <param name="id">An integer argument ID of team</param>
/// <param name="title">A string argument title of team</param>
/// <param name="dateOfCreation">A time_t argument date of team's creation</param>
/// <param name="idOfCreator">An integer argument ID of the creator of the team</param>
/// <param name="dateOfLastChange">A time_t argument date of last change made to a team</param>
/// <param name="idOfChange">An integer argument ID of the user who made the latest change</param>
/// <param name="members">A vector of strings argument. Holds all of the assigned users' IDs</param>
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
		team.members.push_back(stoi(member));

	teams.push_back(team);
}

/// <summary>
/// Used for creating a new team and adding it to the end of the database (.txt file)
/// </summary>
/// <param name="team">Argument of type Team. The new team to be added in the database</param>
void pm::dal::TeamStore::createNewTeam(pm::types::Team& team)
{
	std::ofstream file("../../data/Teams.txt", std::ios::in | std::ios::ate);

	file << team.id << '^';
	file << team.title << '^';
	file << team.dateOfCreation << '^';
	file << team.idOfCreator << '^';
	file << team.dateOfLastChange << '^';
	file << team.idOfChange << '^';

	file << '\n';

	file.close();
}

/// <summary>
/// Used for generating an ID for a new team so there aren't any repeating IDs
/// </summary>
/// <returns>ID for new team</returns>
int pm::dal::TeamStore::generateNewId()
{
	int maxId = 0;

	teamStore.getData();
	teams = teamStore.getAllTeams();

	for (auto team : teams)
		if (team.id > maxId)
			maxId = team.id;

	return maxId + 1;
}

/// <summary>
/// Used to get all currently existing teams from database (.txt file)
/// </summary>
/// <returns>Vector of type Team containing all created teams</returns>
std::vector<pm::types::Team> pm::dal::TeamStore::getAllTeams()
{
	teamStore.getData();
	return std::vector<pm::types::Team>(teams);
}

/// <summary>
/// Used for updating teams' data in database (.txt file)
/// </summary>
/// <param name="teams">Vector of type Team containing all teams that should be in the database, including the updated ones</param>
void pm::dal::TeamStore::update(std::vector<pm::types::Team> teams)
{
	std::ofstream file("../../data/Teams.txt", std::ios::in | std::ios::trunc);	// Opens database (.txt file) and deletes all of it's contents so that new updated data can be added
	
	for (unsigned i = 0; i < teams.size(); i++)
	{
		pm::types::Team team = teams[i];

		file << team.id << '^';
		file << team.title << '^';
		file << team.dateOfCreation << '^';
		file << team.idOfCreator << '^';
		file << team.dateOfLastChange << '^';
		file << team.idOfChange << '^';

		for (auto member : team.members)
			file << member << ';';

		file << '\n';
	}

	file.close();
}

/// <summary>
/// Used for removing a particular team from the database (.txt file) by it's given ID
/// </summary>
/// <param name="delId">An integer argument ID of team to be removed</param>
void pm::dal::TeamStore::remove(int delId)
{
	int index = -1;
	teamStore.getData();

	for (unsigned i = 0; i < teams.size(); i++)
	{
		if (teams[i].id == delId)	// Team with given ID exists
		{
			index = i;
			break;
		}
	}

	if (index == -1)	// Team with given ID does not exist
	{
		std::cout << std::endl << "     Team with ID " << delId << " does not exist!";
		return;
	}

	teams.erase(teams.begin() + index);		// Removing the team from the vector containing all teams

	std::cout << std::endl << "     Team successfully removed!";

	teamStore.update(teams);
}

/// <summary>
/// Used for assigning users (their IDs) to a team
/// </summary>
/// <param name="id">An integer argument ID of team to which users will get assigned</param>
/// <param name="userId">An integer argument ID of user to be assigned</param>
void pm::dal::TeamStore::assignUsers(int id, int userId)
{
	teams.clear();
	teams = teamStore.getAllTeams();

	for (unsigned i = 0; i < teams.size(); i++)
		if (teams[i].id == id)
			teams[i].members.push_back(userId);

	teamStore.update(teams);
}

/// <summary>
/// Used for checking if a team exists by giving an ID
/// </summary>
/// <param name="teamId">An integer argument (supposedly) ID of team</param>
/// <returns>True or false depending on whether team does exist</returns>
bool pm::dal::TeamStore::checkExistanceById(int teamId)
{
	teams.clear();
	teams = teamStore.getAllTeams();

	for (unsigned i = 0; i < teams.size(); i++)
		if (teams[i].id == teamId)
			return true;

	return false;
}