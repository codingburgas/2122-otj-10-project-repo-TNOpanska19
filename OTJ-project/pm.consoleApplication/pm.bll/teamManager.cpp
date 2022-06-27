#include "pch.h"
#include "teamManager.h"
#include "../pm.consoleApplication/teamsMenu.h"
#include "../pm.dal/userStore.h"

pm::bll::TeamManager mTeamManager;
pm::dal::TeamStore mTeamStore;
pm::dal::UserStore mUserStore;
std::vector<pm::types::Team> teamList;

void pm::bll::TeamManager::createTeam(std::string title, pm::types::User activeUser)
{
	pm::types::Team newTeam;

	newTeam.id = mTeamStore.generateNewId();
	newTeam.title = title;
	newTeam.dateOfCreation = time(NULL);
	newTeam.idOfCreator = activeUser.id;
	newTeam.dateOfLastChange = time(NULL);
	newTeam.idOfChange = activeUser.id;

	mTeamStore.createNewTeam(newTeam);

	teamsMenu::teamsManagementView(activeUser);
}

void pm::bll::TeamManager::updateTeam(pm::types::User activeUser)
{
	system("CLS");

	int id;
	bool flag = false;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               UPDATE TEAM            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "     Update team with id: "; std::cin >> id;
	std::cout << std::endl;

	teamList.clear();
	teamList = mTeamManager.getRegisteredTeams();

	for (unsigned i = 0; i < teamList.size(); i++)
	{
		if (teamList[i].id == id)
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "                                " << std::endl;
			std::cout << "     Update title: "; std::getline(std::cin, teamList[i].title);
			teamList[i].dateOfLastChange = time(NULL);
			teamList[i].idOfChange = activeUser.id;

			flag = true;
			break;
		}
	}

	if (flag)
	{
		mTeamStore.update(teamList);
	}

	else
	{
		std::cout << "     Team with ID " << id << " does not exist!" << std::endl;
	}

	std::cout << std::endl << "  ======================================" << std::endl;
	std::cout << std::endl << "  Press any key to go back to menu...";
	_getch();
	teamsMenu::teamsManagementView(activeUser);
}

void pm::bll::TeamManager::removeTeam(pm::types::User activeUser)
{
	system("CLS");
	int id;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               REMOVE TEAM            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;

	std::cout << "     Remove team with Id: "; std::cin >> id;
	mTeamStore.remove(id);
	std::cout << std::endl << std::endl;

	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	teamsMenu::teamsManagementView(activeUser);
}

std::vector<pm::types::Team> pm::bll::TeamManager::getRegisteredTeams()
{
	return mTeamStore.getAllTeams();
}

bool pm::bll::TeamManager::getTeamById(int id)
{
	mTeamStore.getData();
	teamList = mTeamManager.getRegisteredTeams();

	for (unsigned i = 0; i < teamList.size(); i++)
	{
		if (teamList[i].id == id)
		{
			return true;
		}
	}

	return false;
}

void pm::bll::TeamManager::assignUsersToTeam(pm::types::User activeUser)
{
	system("CLS");
	int teamId, userId;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               ASSIGN USERS            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "     Choose team with Id: "; std::cin >> teamId;

	if (mTeamManager.getTeamById(teamId))
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << std::endl << "     Add user by Id: "; std::cin >> userId;
		std::cout << std::endl;

		if (mUserStore.checkExistanceById(userId))
		{
			std::cout << "     User added to team!" << std::endl;
			mTeamStore.assignUsers(teamId, userId);
		}

		else
		{
			std::cout << "     User does not exist!" << std::endl;
		}
	}

	else
	{
		std::cout << std::endl << "     Team does not exist!" << std::endl;
	}

	std::cout << std::endl << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	teamsMenu::teamsManagementView(activeUser);
}

void pm::bll::TeamManager::displayTeams(pm::types::User activeUser)
{
	system("CLS");
	mTeamStore.getData();
	teamList = mTeamManager.getRegisteredTeams();

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
		{
			std::cout << member << ", ";
		}

		std::cout << std::endl << std::endl;
	}

	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	teamsMenu::teamsManagementView(activeUser);
}