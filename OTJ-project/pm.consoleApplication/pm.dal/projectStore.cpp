#include "pch.h"
#include "projectStore.h"
#include "../pm.types/project.h"

std::vector<pm::types::Project> projects;
pm::dal::ProjectStore projectStore;

void pm::dal::ProjectStore::getData()
{
	std::ifstream file("../../data/Projects.txt", std::fstream::in);
	projects.clear();

	std::string title, description, dateOfCreation, idOfCreator, dateOfLastChange, idOfChange, teamsLine, next;
	std::vector<std::string> teams;

	while (std::getline(file, title, ','))
	{
		teams.clear();
		std::getline(file, description, ',');
		std::getline(file, dateOfCreation, ',');
		std::getline(file, idOfCreator, ',');
		std::getline(file, dateOfLastChange, ',');
		std::getline(file, idOfChange, ',');
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
	{
		project.teams.push_back(team);
	}

	projects.push_back(project);
}

void pm::dal::ProjectStore::createNewProject(pm::types::Project& project)
{
	std::ofstream file("../../data/Projects.txt", std::ios::in | std::ios::ate);

	file << project.title << ',';
	file << project.description << ',';
	file << project.dateOfCreation << ',';
	file << project.idOfCreator << ',';
	file << project.dateOfLastChange << ',';
	file << project.idOfChange << ',';

	file << '\n';

	file.close();
}