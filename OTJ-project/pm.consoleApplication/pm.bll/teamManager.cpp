#include "pch.h"
#include <conio.h>
#include "teamManager.h"
#include "../pm.consoleApplication/teamsMenu.h"

pm::bll::TeamManager mTeamManager;
pm::dal::TeamStore mTeamStore;
std::vector<pm::types::Team> teamList;

void pm::bll::TeamManager::createTeam(std::string title, pm::types::User activeUser)
{
	pm::types::Team newTeam;

	newTeam.id = mUserStore.generateNewId(); // nova funkciq za teams
	newTeam.title = title;
	/*
	newTeam.dateOfCreation = time(NULL);
	newTeam.idOfCreator = activeUser.id;
	newTeam.dateOfLastChange = time(NULL);
	newTeam.idOfChange = activeUser.id;
	*/

	mTeamStore.createNewTeam(newTeam);

	teamMenu::teamsManagementView(activeUser);
}

std::vector<pm::types::Team> pm::bll::TeamManager::getRegisteredTeams()
{
	return mTeamStore.getAll();
}

void pm::bll::TeamManager::displayTeams()
{
	system("CLS");
	mTeamStore.getData();
	teamList = mTeamManager.getRegisteredTeams();

	std::cout << "  ========================================================" << std::endl;
	std::cout << "                         TEAM LIST                    " << std::endl;
	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "   id, title, members" << std::endl << std::endl << std::endl;

	for (unsigned i = 0; i < teamList.size(); i++)
	{
		std::cout << "   " << teamList[i].id << ", " << teamList[i].title << ", ";

		for (auto member : teamList[i].members)
		{
			std::cout << member << ", ";
		}

		std::cout << std::endl << std::endl;
	}

	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	//teamMenu::teamsManagementView(activeUser);
}