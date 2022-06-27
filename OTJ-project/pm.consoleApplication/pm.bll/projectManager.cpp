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
	std::string teamIds = "";

	for (auto team : teams)
	{
		if (std::count(team.members.begin(), team.members.end(), activeUser.id))
		{
			teamIds += std::to_string(team.id) + ",";
		}
	}

	std::cout << "  ========================================================" << std::endl;
	std::cout << "                       PROJECT LIST                    " << std::endl;
	std::cout << "  ========================================================" << std::endl << std::endl;

	for (unsigned i = 0; i < projectList.size(); i++)
	{
		if (projectList[i].teams.empty() && projectList[i].idOfCreator == activeUser.id)
		{
			listProjects(projectList[i]);
		}

		for (auto team : projectList[i].teams)
		{
			if (teamIds.find(std::to_string(team)) != std::string::npos || projectList[i].idOfCreator == activeUser.id)
			{
				listProjects(projectList[i]);
				break;
			}
		}
	}

	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	projectsMenu::projectsManagementView(activeUser);
}

void pm::bll::ProjectManager::listProjects(pm::types::Project project)
{
	char buffer[80];
	struct tm time;
	const time_t* rawTime;

	std::cout << "   Title: " << project.title << std::endl;
	std::cout << "   Description: " << project.description << std::endl;

	rawTime = &project.dateOfCreation;
	localtime_s(&time, rawTime);
	strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
	std::cout << "   Created on: " << buffer << std::endl;
	std::cout << "   ID of creator: " << project.idOfCreator << std::endl;

	rawTime = &project.dateOfLastChange;
	localtime_s(&time, rawTime);
	strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
	std::cout << "   Last change on: " << buffer << std::endl;
	std::cout << "   Id of user who made change: " << project.idOfChange << std::endl;
	std::cout << "   Assigned teams ids: ";

	for (auto teamId : project.teams)
	{
		std::cout << teamId << ", ";
	}

	std::cout << std::endl << std::endl;
}

std::vector<pm::types::Project> pm::bll::ProjectManager::getRegisteredProjects()
{
	return mProjectStore.getAllProjects();
}