/*****************************************************************//**
 * \file   teamManager.cpp
 * \brief  Source file for team management
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "teamManager.h"
#include "../pm.consoleApplication/teamsMenu.h"
#include "../pm.dal/userStore.h"

/// <summary>
/// Object of teamsMenu structure
/// </summary>
menu::teamsMenu tMenuManager;

/// <summary>
/// Object of TeamManager structure
/// </summary>
pm::bll::TeamManager tTeamManager;
/// <summary>
/// Object of TeamStore structure
/// </summary>
pm::dal::TeamStore tTeamStore;
/// <summary>
/// Object of UserStore structure
/// </summary>
pm::dal::UserStore tUserStore;
/// <summary>
/// Vector of type Team. Used to store teams.
/// </summary>
std::vector<pm::types::Team> teamList;

/// <summary>
/// Used to create new team
/// </summary>
/// <param name="title">A string argument title of new team</param>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::TeamManager::createTeam(std::string title, pm::types::User activeUser)
{
	pm::types::Team newTeam;

	newTeam.id = tTeamStore.generateNewId();
	newTeam.title = title;
	newTeam.dateOfCreation = time(NULL);	// Current time
	newTeam.idOfCreator = activeUser.id;
	newTeam.dateOfLastChange = time(NULL);	// Current time
	newTeam.idOfChange = activeUser.id;

	tTeamStore.createNewTeam(newTeam);

	tMenuManager.teamsManagementView(activeUser);
}

/// <summary>
/// Used for updating team data with given ID
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::TeamManager::updateTeam(pm::types::User activeUser)
{
	system("CLS");

	int id;
	bool flag = false;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               UPDATE TEAM            " << std::endl;
	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "     Update team with id: ";
	
	while (!(std::cin >> id))	// Checks whether entered ID is a number
	{
		system("CLS");

		std::cout << " ID needs to be a number!" << std::endl << std::endl;
		std::cout << "  ======================================" << std::endl;
		std::cout << "               UPDATE TEAM            " << std::endl;
		std::cout << "  ======================================" << std::endl << std::endl;
		std::cout << "     Update team with id: "; std::cin >> id;

		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	
	std::cout << std::endl;

	teamList = tTeamManager.getRegisteredTeams();

	// Checks wether there is such a team with the given ID
	for (unsigned i = 0; i < teamList.size(); i++)
	{
		if (teamList[i].id == id)
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "                                " << std::endl;
			std::cout << "     Update title: "; std::getline(std::cin, teamList[i].title);
			teamList[i].dateOfLastChange = time(NULL);	// Change date of change to current date
			teamList[i].idOfChange = activeUser.id;		// Change ID of person who made update to current user's ID

			flag = true;
			break;
		}
	}

	if (flag)	// Team with given ID exists
		tTeamStore.update(teamList);

	else		// Team with given ID does not exist
		std::cout << "     Team with ID " << id << " does not exist!" << std::endl;

	std::cout << std::endl << "  ======================================" << std::endl;
	std::cout << std::endl << "  Press any key to go back to menu...";
	(void)_getch();
	tMenuManager.teamsManagementView(activeUser);
}

/// <summary>
/// Used to remove team with given ID
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::TeamManager::removeTeam(pm::types::User activeUser)
{
	system("CLS");
	int id;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               REMOVE TEAM            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "     Remove team with Id: "; 
	
	while (!(std::cin >> id))	// Checks whether entered ID is a number
	{
		system("CLS");

		std::cout << " ID needs to be a number!" << std::endl << std::endl;
		std::cout << "  ======================================" << std::endl;
		std::cout << "               REMOVE TEAM            " << std::endl;
		std::cout << "  ======================================" << std::endl;
		std::cout << "                                " << std::endl;
		std::cout << "     Remove team with Id: ";

		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	tTeamStore.remove(id);
	std::cout << std::endl << std::endl;

	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	(void)_getch();
	tMenuManager.teamsManagementView(activeUser);
}

/// <summary>
/// Used to get all registered teams
/// </summary>
/// <returns>Vector of all registered teams</returns>
std::vector<pm::types::Team> pm::bll::TeamManager::getRegisteredTeams()
{
	teamList.clear();
	tTeamStore.getData();
	return tTeamStore.getAllTeams();
}

/// <summary>
/// Used to get a team by given ID
/// </summary>
/// <param name="id">A integer argument id of team</param>
/// <returns>True or false depending on whether a team with given ID exists</returns>
bool pm::bll::TeamManager::getTeamById(int id)
{
	teamList = tTeamManager.getRegisteredTeams();

	for (unsigned i = 0; i < teamList.size(); i++)
		if (teamList[i].id == id)
			return true;

	return false;
}

/// <summary>
/// Used to display all registered teams
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::TeamManager::displayTeams(pm::types::User activeUser)
{
	system("CLS");
	teamList = tTeamManager.getRegisteredTeams();

	std::cout << "  ========================================================" << std::endl;
	std::cout << "                         TEAM LIST                    " << std::endl;
	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "                     id, title, members" << std::endl << std::endl << std::endl;

	for (unsigned i = 0; i < teamList.size(); i++)
	{
		std::cout << "   Id: " << teamList[i].id << std::endl;
		std::cout << "   Title: " << teamList[i].title << std::endl;
		std::cout << "   Assigned members IDs: ";

		for (auto member : teamList[i].members)
			std::cout << member << ", ";

		std::cout << std::endl << std::endl;
	}

	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	(void)_getch();
	tMenuManager.teamsManagementView(activeUser);
}

/// <summary>
/// Used to assign users to a team
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::TeamManager::assignUsersToTeam(pm::types::User activeUser)
{
	system("CLS");
	int teamId, userId;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               ASSIGN USERS            " << std::endl;
	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "     Choose team with Id: ";

	while (!(std::cin >> teamId))	// Checks whether entered ID is a number
	{
		system("CLS");

		std::cout << " ID needs to be a number!" << std::endl << std::endl;
		std::cout << "  ======================================" << std::endl;
		std::cout << "               ASSIGN USERS            " << std::endl;
		std::cout << "  ======================================" << std::endl << std::endl;
		std::cout << "     Choose team with Id: ";

		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	if (tTeamManager.getTeamById(teamId))	// Checks if team with given ID exists
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << std::endl << "     Add user by Id: "; std::cin >> userId;
		std::cout << std::endl;

		if (mUserStore.checkExistanceById(userId))	// Checks if user with given ID exists
		{
			std::cout << "     User added to team!" << std::endl;
			tTeamStore.assignUsers(teamId, userId);
		}

		else
			std::cout << "     User does not exist!" << std::endl;
	}

	else
		std::cout << std::endl << "     Team does not exist!" << std::endl;

	std::cout << std::endl << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	(void)_getch();
	tMenuManager.teamsManagementView(activeUser);
}