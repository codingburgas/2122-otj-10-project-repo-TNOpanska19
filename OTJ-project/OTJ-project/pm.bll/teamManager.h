/*****************************************************************//**
 * \file   teamManager.h
 * \brief  Header file for team management
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "pch.h"
#include "userManager.h"
#include "../pm.types/team.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/teamStore.h"

/// <summary>
/// Namespace for business logic layer
/// </summary>
namespace pm::bll
{
	/// <summary>
	/// Structure for team management
	/// </summary>
	struct TeamManager
	{
		pm::dal::UserStore mUserStore;
		
		void createTeam(std::string title, pm::types::User activeUser);

		void updateTeam(pm::types::User activeUser);

		void removeTeam(pm::types::User activeUser);

		std::vector<pm::types::Team> getRegisteredTeams();

		bool getTeamById(int id);

		void displayTeams(pm::types::User activeUser);

		void assignUsersToTeam(pm::types::User activeUser);
	};
}