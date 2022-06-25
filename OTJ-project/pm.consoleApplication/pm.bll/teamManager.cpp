#include "pch.h"
#include "teamManager.h"
#include "../pm.consoleApplication/teamsMenu.h"

pm::bll::TeamManager mTeamManager;
pm::dal::TeamStore mTeamStore;

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