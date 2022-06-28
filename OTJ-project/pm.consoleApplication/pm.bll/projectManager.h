#pragma once

#include "pch.h"
#include "userManager.h"
#include "../pm.types/project.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/teamStore.h"

namespace pm::bll
{
	struct ProjectManager
	{
		void createProject(std::string title, std::string description, pm::types::User activeUser);

		void updateProject(pm::types::User activeUser);

		void removeProject(pm::types::User activeUser);

		void displayProjects(pm::types::User activeUser);

		void listProjects(pm::types::Project project);

		std::vector<pm::types::Project> getRegisteredProjects();

		void assignTeamsToProject(pm::types::User activeUser);

		bool getProjectByTitle(std::string title);
	};
}