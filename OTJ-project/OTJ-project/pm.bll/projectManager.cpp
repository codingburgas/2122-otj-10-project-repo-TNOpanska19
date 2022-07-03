/*****************************************************************//**
 * \file   projectManager.cpp
 * \brief  Source file for project management
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "teamManager.h"
#include "projectManager.h"
#include "../pm.consoleApplication/projectsMenu.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/projectStore.h"

/// <summary>
/// Object of projectsMenu structure
/// </summary>
menu::projectsMenu pMenuManager;

/// <summary>
/// Object of TeamManager structure
/// </summary>
pm::bll::TeamManager pTeamManager;
/// <summary>
/// Object of ProjectManager structure
/// </summary>
pm::bll::ProjectManager pProjectManager;
/// <summary>
/// Object of TeamStore structure
/// </summary>
pm::dal::TeamStore pTeamStore;
/// <summary>
/// Object of ProjectStore structure
/// </summary>
pm::dal::ProjectStore pProjectStore;
/// <summary>
/// Vector of type Project. Used to store projects.
/// </summary>
std::vector<pm::types::Project> projectList;

/// <summary>
/// Used to create a new project
/// </summary>
/// <param name="title">A string argument title of new project</param>
/// <param name="description">A string argument description of new project</param>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::ProjectManager::createProject(std::string title, std::string description, pm::types::User activeUser)
{
	pm::types::Project newProject;

	newProject.title = title;
	newProject.description = description;
	newProject.dateOfCreation = time(NULL);		// Current time
	newProject.idOfCreator = activeUser.id;
	newProject.dateOfLastChange = time(NULL);	// Current time
	newProject.idOfChange = activeUser.id;

	pProjectStore.createNewProject(newProject);

	pMenuManager.projectsManagementView(activeUser);
}

/// <summary>
/// Used for updating a project with given title
/// </summary>
/// <param name="activeUser">Logged-in user</param>
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

	projectList = pProjectManager.getRegisteredProjects();

	// Goes through all projects to see whether entered one exists
	for (unsigned i = 0; i < projectList.size(); i++)
	{
		if (projectList[i].title == title && (projectList[i].idOfCreator == activeUser.id || activeUser.privilege == 1))
		{
			std::cout << "     Update title: "; std::getline(std::cin, projectList[i].title);
			std::cout << "\n     Update descritpion: "; std::getline(std::cin, projectList[i].description);
			projectList[i].dateOfLastChange = time(NULL);	// Change time of last change to current time
			projectList[i].idOfChange = activeUser.id;		// Change id of person who made the last change to the currently logged-in user's

			flag = true;
			break;
		}
	}

	if (flag)	// Project with given title exists
		pProjectStore.update(projectList);

	else		// Project with given title does not exists
		std::cout << "     Project with title " << title << " does\n     not exist or does not belong to you!" << std::endl;

	std::cout << std::endl << "  ======================================" << std::endl;
	std::cout << std::endl << "  Press any key to go back to menu...";
	(void)_getch();
	pMenuManager.projectsManagementView(activeUser);
}

/// <summary>
/// Used to remove project with given title
/// </summary>
/// <param name="activeUser">Logged-in</param>
void pm::bll::ProjectManager::removeProject(pm::types::User activeUser)
{
	system("CLS");
	std::string title;

	std::cout << "  ======================================" << std::endl;
	std::cout << "             REMOVE PROJECT            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;

	std::cout << "    Remove project with title: "; std::getline(std::cin, title);
	pProjectStore.remove(title, activeUser);
	std::cout << std::endl << std::endl;

	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	(void)_getch();
	pMenuManager.projectsManagementView(activeUser);
}

/// <summary>
/// Used to get all registered projects
/// </summary>
/// <returns></returns>
std::vector<pm::types::Project> pm::bll::ProjectManager::getRegisteredProjects()
{
	pProjectStore.getData();
	projectList.clear();
	return pProjectStore.getAllProjects();
}

/// <summary>
/// Used to display all created projects
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::ProjectManager::displayProjects(pm::types::User activeUser)
{
	system("CLS");
	projectList = pProjectManager.getRegisteredProjects();

	std::vector<pm::types::Team> teams = pTeamManager.getRegisteredTeams();
	std::string teamIds = "";

	// If the current user's id appears in a team's members, that team's id gets added to a string
	for (auto team : teams)
	{
		if (std::count(team.members.begin(), team.members.end(), activeUser.id))
			teamIds += std::to_string(team.id) + ",";
	}

	std::cout << "  ========================================================" << std::endl;
	std::cout << "                       PROJECT LIST                    " << std::endl;
	std::cout << "  ========================================================" << std::endl << std::endl;

	// Checks whether user has access to given project
	for (unsigned i = 0; i < projectList.size(); i++)
	{
		// If project does not have any teams assigned
		if ((projectList[i].teams.empty() && projectList[i].idOfCreator == activeUser.id) || activeUser.privilege == 1)
		{
			listProjects(projectList[i]);
			continue;
		}
		
		// If project does have teams assigned, it checks their id and whether they're contained in the previously mentioned string
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
	(void)_getch();
	pMenuManager.projectsManagementView(activeUser);
}

/// <summary>
/// Used for listing the projects
/// </summary>
/// <param name="project">Argument of type Project</param>
void pm::bll::ProjectManager::listProjects(pm::types::Project project)
{
	char buffer[80];
	struct tm time;
	const time_t* rawTime;

	std::cout << "   Title: " << project.title << std::endl;
	std::cout << "   Description: " << project.description << std::endl;

	// Transform time_t to readable format
	rawTime = &project.dateOfCreation;
	localtime_s(&time, rawTime);
	strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
	std::cout << "   Created on: " << buffer << std::endl;
	std::cout << "   ID of creator: " << project.idOfCreator << std::endl;

	// Transform time_t to readable format
	rawTime = &project.dateOfLastChange;
	localtime_s(&time, rawTime);
	strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
	std::cout << "   Last change on: " << buffer << std::endl;
	std::cout << "   Id of user who made change: " << project.idOfChange << std::endl;
	std::cout << "   Assigned teams ids: ";

	for (auto teamId : project.teams)
		std::cout << teamId << ", ";

	std::cout << std::endl << std::endl;
}

/// <summary>
/// Used for assgining teams (their IDs) to a project
/// </summary>
/// <param name="activeUser">Logged-in user</param>
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

	projectList = pProjectManager.getRegisteredProjects();

	// Checks whether user has access to given project
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
				pProjectStore.assignTeams(projectTitle, teamId);
			}

			else
				std::cout << "     Team with id " << teamId << " does not exist!" << std::endl;

			flag = true;
			break;
		}
	}

	if (!flag)
		std::cout << "\n     Project with title " << projectTitle << " does\n     not exist or does not belong to you!" << std::endl;

	std::cout << std::endl << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	(void)_getch();
	pMenuManager.projectsManagementView(activeUser);
}

/// <summary>
/// Used for checking whether a project exists by their title
/// </summary>
/// <param name="title">A string argument title of searched for project</param>
/// <returns>True or false depending on whether project exists or not</returns>
bool pm::bll::ProjectManager::getProjectByTitle(std::string title)
{
	pProjectStore.getData();
	projectList = pProjectManager.getRegisteredProjects();

	for (unsigned i = 0; i < projectList.size(); i++)
		if (projectList[i].title == title)
			return true;

	return false;
}
