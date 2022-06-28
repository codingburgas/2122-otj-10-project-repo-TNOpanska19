#include "pch.h"
#include "teamManager.h"
#include "projectManager.h"
#include "../pm.consoleApplication/projectsMenu.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/projectStore.h"

pm::bll::TeamManager mTeamsManager;
pm::bll::ProjectManager mProjectManager;
pm::dal::TeamStore pTeamStore;
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

void pm::bll::ProjectManager::updateProject(pm::types::User activeUser)
{
	system("CLS");

	std::string title;
	bool flag = false;

	std::cout << "  ======================================" << std::endl;
	std::cout << "             UPDATE PROJECT            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "     Update project with title: "; std::getline(std::cin, title);
	std::cout << std::endl;

	getRegisteredProjects();

	for (unsigned i = 0; i < projectList.size(); i++)
	{
		if (projectList[i].title == title && (projectList[i].idOfCreator == activeUser.id || activeUser.privilege == 1))
		{
			std::cout << "                                " << std::endl;
			std::cout << "     Update title: "; std::getline(std::cin, projectList[i].title);
			std::cout << "     Update descritpion: "; std::getline(std::cin, projectList[i].description);
			projectList[i].dateOfLastChange = time(NULL);
			projectList[i].idOfChange = activeUser.id;

			flag = true;
			break;
		}
	}

	if (flag)
		mProjectStore.update(projectList);

	else
		std::cout << "     Project with title " << title << " does\n     not exist or does not belong to you!" << std::endl;

	std::cout << std::endl << "  ======================================" << std::endl;
	std::cout << std::endl << "  Press any key to go back to menu...";
	_getch();
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
	getRegisteredProjects();

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
		if ((projectList[i].teams.empty() && projectList[i].idOfCreator == activeUser.id) || activeUser.privilege == 1)
		{
			listProjects(projectList[i]);
			continue;
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

void pm::bll::ProjectManager::getRegisteredProjects()
{
	mProjectStore.getData();
	projectList.clear();
	projectList = mProjectStore.getAllProjects();
}

void pm::bll::ProjectManager::assignTeamsToProject(pm::types::User activeUser)
{
	system("CLS");
	int teamId;
	bool flag = false;
	std::string projectTitle;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               ASSIGN TEAMS            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "     Choose project with title: "; std::getline(std::cin, projectTitle);

	getRegisteredProjects();

	for (unsigned i = 0; i < projectList.size(); i++)
	{
		if (projectList[i].title == projectTitle && (projectList[i].idOfCreator == activeUser.id || activeUser.privilege == 1))
		{
			std::cin.clear();
			std::cout << std::endl << "     Add team by Id: "; std::cin >> teamId;
			std::cout << std::endl;

			if (pTeamStore.checkExistanceById(teamId))
			{
				std::cout << "     Team added to project!" << std::endl;
				mProjectStore.assignTeams(projectTitle, teamId);
			}

			else
			{
				std::cout << "     Team with id " << teamId << " does not exist!" << std::endl;
			}

			flag = true;
			break;
		}
	}

	if (!flag)
	{
		std::cout << "\n     Project with title " << projectTitle << " does\n     not exist or does not belong to you!" << std::endl;
	}

	std::cout << std::endl << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	projectsMenu::projectsManagementView(activeUser);
}

bool pm::bll::ProjectManager::getProjectByTitle(std::string title)
{
	getRegisteredProjects();

	for (unsigned i = 0; i < projectList.size(); i++)
	{
		if (projectList[i].title == title)
		{
			return true;
		}
	}

	return false;
}
