/*****************************************************************//**
 * \file   projectStore.h
 * \brief  Header file for project storing
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "pch.h"
#include "../pm.types/user.h"
#include "../pm.types/project.h"

/// <summary>
/// Namespace for data access layer
/// </summary>
namespace pm::dal
{
	/// <summary>
	/// Structure for project storing
	/// </summary>
	struct ProjectStore
	{
		void getData();

		void addToProjects(std::string title, std::string description, time_t dateOfCreation, int idOfCreator, time_t dateOfLastChange, int idOfChange, std::vector<std::string> members);

		void createNewProject(pm::types::Project& project);


		std::vector<pm::types::Project> getAllProjects();

		void update(std::vector<pm::types::Project> project);
		
		void remove(std::string title, pm::types::User);

		void assignTeams(std::string title, int teamId);
	};
}