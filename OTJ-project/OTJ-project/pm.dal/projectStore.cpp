/*****************************************************************//**
 * \file   projectStore.cpp
 * \brief  Source file for project storing
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "projectStore.h"
#include "../pm.types/user.h"
#include "../pm.types/project.h"

/// <summary>
/// Object of ProjectStore structure
/// </summary>
pm::dal::ProjectStore pStore;
/// <summary>
/// Vector of type Project. Used to store projects
/// </summary>
std::vector<pm::types::Project> projects;

/// <summary>
/// Used for getting project data from database (.txt file)
/// </summary>
void pm::dal::ProjectStore::getData()
{
	std::string title, description, dateOfCreation, idOfCreator, dateOfLastChange, idOfChange, teamsLine, next;
	std::vector<std::string> teams;

	std::ifstream file("../../data/Projects.txt", std::fstream::in);	// Open Projects.txt
	projects.clear();	// Clear vector of projects so there is no repeating

	while (std::getline(file, title, '^'))
	{
		teams.clear();
		std::getline(file, description, '^');
		std::getline(file, dateOfCreation, '^');
		std::getline(file, idOfCreator, '^');
		std::getline(file, dateOfLastChange, '^');
		std::getline(file, idOfChange, '^');
		std::getline(file, teamsLine);
		teamsLine = teamsLine + '\n';

		while (teamsLine != "\n")
		{
			size_t pos = teamsLine.find(';');
			teams.push_back(teamsLine.substr(0, pos));
			teamsLine.erase(0, pos + 1);
		}

		addToProjects(title, description, stoi(dateOfCreation), stoi(idOfCreator), stoi(dateOfLastChange), stoi(idOfChange), teams);
	}

	file.close();
}

/// <summary>
/// Used for adding a new project in the database (.txt file)
/// </summary>
/// <param name="title">A string argument title of project</param>
/// <param name="description">A string argument descritpion of project</param>
/// <param name="dateOfCreation">A time_t argument date of project's creation</param>
/// <param name="idOfCreator">An integer argument ID of the creator of the project</param>
/// <param name="dateOfLastChange">A time_t argument date of last change made to a project</param>
/// <param name="idOfChange">An integer argument ID of the user who made the latest change</param>
/// <param name="teams">A vector of strings argument. Holds all of the assigned teams' IDs</param>
void pm::dal::ProjectStore::addToProjects(std::string title, std::string description, time_t dateOfCreation, int idOfCreator, time_t dateOfLastChange, int idOfChange, std::vector<std::string> teams)
{
	pm::types::Project project;

	project.title = title;
	project.description = description;
	project.dateOfCreation = dateOfCreation;
	project.idOfCreator = idOfCreator;
	project.dateOfLastChange = dateOfLastChange;
	project.idOfChange = idOfChange;

	for (auto team : teams)
		project.teams.push_back(stoi(team));

	projects.push_back(project);
}

/// <summary>
/// Used for creating a new project and adding it to the end of the database (.txt file)
/// </summary>
/// <param name="project">Argument of type Project. The new project to be added in the database</param>
void pm::dal::ProjectStore::createNewProject(pm::types::Project& project)
{
	std::ofstream file("../../data/Projects.txt", std::ios::in | std::ios::ate);

	file << project.title << '^';
	file << project.description << '^';
	file << project.dateOfCreation << '^';
	file << project.idOfCreator << '^';
	file << project.dateOfLastChange << '^';
	file << project.idOfChange << '^';

	file << '\n';

	file.close();
}

/// <summary>
/// Used to get all currently existing projects from database (.txt file)
/// </summary>
/// <returns>Vector of type Project containing all created projects</returns>
std::vector<pm::types::Project> pm::dal::ProjectStore::getAllProjects()
{
	pStore.getData();
	return std::vector<pm::types::Project>(projects);
}

/// <summary>
/// Used for updating projects' data in database (.txt file)
/// </summary>
/// <param name="projects">Vector of type Project containing all projects that should be in the database, including the updated ones</param>
void pm::dal::ProjectStore::update(std::vector<pm::types::Project> projects)
{
	std::ofstream file("../../data/Projects.txt", std::ios::in | std::ios::trunc);	// Opens database (.txt file) and deletes all of it's contents so that new updated data can be added

	for (unsigned i = 0; i < projects.size(); i++)
	{
		pm::types::Project project = projects[i];

		file << project.title << '^';
		file << project.description << '^';
		file << project.dateOfCreation << '^';
		file << project.idOfCreator << '^';
		file << project.dateOfLastChange << '^';
		file << project.idOfChange << '^';

		for (auto team : project.teams)
			file << team << ';';

		file << '\n';
	}

	file.close();
}

/// <summary>
/// Used for removing a particular project from the database (.txt file) by it's given title
/// </summary>
/// <param name="title">A string argument title of project to be removed</param>
/// <param name="activeUser">Logged-in user</param>
void pm::dal::ProjectStore::remove(std::string title, pm::types::User activeUser)
{
	int index = -1;
	projects = pStore.getAllProjects();

	for (unsigned i = 0; i < projects.size(); i++)
	{
		if (projects[i].title == title && (projects[i].idOfCreator == activeUser.id || activeUser.privilege == 1))	// Check whether project exists or user has rights for deleting it
		{
			index = i;
			break;
		}
	}

	if (index == -1)	// Project either does not exist or currently logged-in user does not have rights to remove it
	{
		std::cout << std::endl << "    Project with title " << title << " does\n    not exist or does not belong to you!";
		return;
	}

	projects.erase(projects.begin() + index);	// Removing the project from the vector containing all projects

	std::cout << std::endl << "    Project successfully removed!";

	pStore.update(projects);
}

/// <summary>
/// Used for assigning teams (their IDs) to a project
/// </summary>
/// <param name="title">A string argument title of project to which teams will get assigned</param>
/// <param name="teamId">An integer argument ID of team to be assigned</param>
void pm::dal::ProjectStore::assignTeams(std::string title, int teamId)
{
	projects = pStore.getAllProjects();

	for (unsigned i = 0; i < projects.size(); i++)
		if (projects[i].title == title)
			projects[i].teams.push_back(teamId);

	pStore.update(projects);
}