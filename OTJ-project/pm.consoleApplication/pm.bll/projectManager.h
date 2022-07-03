/*****************************************************************//**
 * \file   projectManager.h
 * \brief  Header file for project management
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "pch.h"
#include "userManager.h"
#include "../pm.types/project.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/teamStore.h"

/// <summary>
/// Namespace for business logic layer
/// </summary>
namespace pm::bll
{
	/// <summary>
	/// Structure for project management
	/// </summary>
	struct ProjectManager
	{
		void createProject(std::string title, std::string description, pm::types::User activeUser);

		void updateProject(pm::types::User activeUser);

		void removeProject(pm::types::User activeUser);

		std::vector<pm::types::Project> getRegisteredProjects();
		
		void displayProjects(pm::types::User activeUser);

		void listProjects(pm::types::Project project);

		void assignTeamsToProject(pm::types::User activeUser);

		bool getProjectByTitle(std::string title);
	};
}