#include "pch.h"
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
	newTeam.dateOfCreation = time(NULL);
	newTeam.idOfCreator = activeUser.id;
	newTeam.dateOfLastChange = time(NULL);
	newTeam.idOfChange = activeUser.id;

	mTeamStore.createNewTeam(newTeam);

	teamMenu::teamsManagementView(activeUser);
}

void pm::bll::TeamManager::displayTeams()
{
	system("CLS");
	mTeamStore.getData();

	/*
	system("CLS");
	mUserStore.getData();
	teamList = mTeamManager.getRegisteredUsers();

	std::cout << "  ========================================================" << std::endl;
	std::cout << "                         USER LIST                    " << std::endl;
	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "   id, username, first name, last name, email, privilege" << std::endl << std::endl << std::endl;

	for (unsigned i = 0; i < userList.size(); i++)
	{
		std::cout << "   " << userList[i].id << ", " << userList[i].username << ", " << userList[i].firstName << ", " << userList[i].lastName << ", "
			<< userList[i].email << ", " << userList[i].privilege << std::endl << std::endl;
	}

	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	mainMenu::usersManagementView();
	*/
}