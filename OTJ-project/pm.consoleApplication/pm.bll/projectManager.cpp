#include "pch.h"
#include "teamManager.h"
#include "projectManager.h"
#include "../pm.consoleApplication/projectsMenu.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/projectStore.h"

pm::bll::TeamManager mTeamsManager;
pm::bll::ProjectManager mProjectManager;
pm::dal::ProjectStore mProjectStore;
std::vector<pm::types::Project> projectList;

void pm::bll::ProjectManager::createProject(std::string title, std::string description, pm::types::User activeUser)
{
	pm::types::Project newProject;

	newProject.title = title;
	newProject.description = description;
	newProject.dateOfCreation = time(NULL);
	newProject.idOfCreator = activeUser.id;
	newProject.dateOfLastChange = time(NULL);
	newProject.idOfChange = activeUser.id;

	mProjectStore.createNewProject(newProject);

	projectsMenu::projectsManagementView(activeUser);
}

void pm::bll::ProjectManager::removeProject(pm::types::User activeUser)
{
	system("CLS");
	std::string title;

	std::cout << "  ======================================" << std::endl;
	std::cout << "             REMOVE PROJECT            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;

	std::cout << "    Remove project with title: "; std::getline(std::cin, title);
	mProjectStore.remove(title, activeUser);
	std::cout << std::endl << std::endl;

	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	projectsMenu::projectsManagementView(activeUser);
}

void pm::bll::ProjectManager::displayProjects(pm::types::User activeUser)
{
	system("CLS");
	mProjectStore.getData();
	projectList = mProjectManager.getRegisteredProjects();

	std::vector<pm::types::Team> teams = mTeamsManager.getRegisteredTeams();
	std::string inTeams = "";

	char buffer[80];
	struct tm time;
	const time_t* rawTime;

	for (auto team : teams)
	{
		std::cout << team.title << std::endl;
		if (std::count(team.members.begin(), team.members.end(), activeUser.username))
		{
			inTeams += team.title + ",";
		}
	}

	std::cout << "  ========================================================" << std::endl;
	std::cout << "                       PROJECT LIST                    " << std::endl;
	std::cout << "  ========================================================" << std::endl << std::endl;

	for (unsigned i = 0; i < projectList.size(); i++)
	{
		for (auto team : projectList[i].teams)
		{
			if (inTeams.find(team) != std::string::npos || projectList[i].idOfCreator == activeUser.id)
			{
				std::cout << "   Title: " << projectList[i].title << std::endl;
				std::cout << "   Description: " << projectList[i].title << std::endl;

				rawTime = &projectList[i].dateOfCreation;
				localtime_s(&time, rawTime);
				strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
				std::cout << "   Created on: " << buffer << std::endl;
				std::cout << "   ID of creator: " << projectList[i].idOfCreator << std::endl;

				rawTime = &projectList[i].dateOfLastChange;
				localtime_s(&time, rawTime);
				strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
				std::cout << "   Last change on: " << buffer << std::endl;
				std::cout << "   Id of user who made change: " << projectList[i].idOfChange << std::endl;
				std::cout << "   Teams: ";

				for (auto teamD : projectList[i].teams)
				{
					std::cout << teamD << ", ";
				}

				std::cout << std::endl << std::endl;
			}
		}
	}

	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	projectsMenu::projectsManagementView(activeUser);
}

std::vector<pm::types::Project> pm::bll::ProjectManager::getRegisteredProjects()
{
	return mProjectStore.getAllProjects();
}