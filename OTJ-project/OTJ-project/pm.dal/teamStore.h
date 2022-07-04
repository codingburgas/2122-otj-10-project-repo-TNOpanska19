/*****************************************************************//**
 * \file   teamStore.h
 * \brief  Header file for team storing
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "pch.h"
#include "../pm.types/team.h"

/// <summary>
/// Namespace for data access layer
/// </summary>
namespace pm::dal
{
	/// <summary>
	/// Structure for team storing
	/// </summary>
	struct TeamStore
	{
		void getData();

		void addToTeams(int id, std::string title, time_t dateOfCreation, int idOfCreator, time_t dateOfLastChange, int idOfChange, std::vector<std::string> members);

		void createNewTeam(pm::types::Team& team);

		int generateNewId();

		std::vector<pm::types::Team> getAllTeams();

		void update(std::vector<pm::types::Team> teams);

		void remove(int delId);

		void assignUsers(int id, int userId);

		bool checkExistanceById(int teamId);
	};
}