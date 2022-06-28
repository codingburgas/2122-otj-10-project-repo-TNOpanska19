#pragma once

#include "pch.h"
#include "../pm.types/user.h"
#include "../pm.types/project.h"

namespace pm::dal
{
	struct ProjectStore
	{
		void getData();

		void addToProjects(std::string title, std::string description, time_t dateOfCreation, int idOfCreator, time_t dateOfLastChange, int idOfChange, std::vector<std::string> members);

		void createNewProject(pm::types::Project& project);

		void update(std::vector<pm::types::Project> project);
		
		void remove(std::string title, pm::types::User);

		std::vector<pm::types::Project> getAllProjects();

		void assignTeams(std::string title, int teamId);
	};
}