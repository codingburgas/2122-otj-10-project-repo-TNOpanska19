/*****************************************************************//**
 * \file   teamsMenu.h
 * \brief  Header file for team management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "pch.h"
#include "../pm.types/user.h"

/// <summary>
/// Namespace for menu
/// </summary>
namespace menu
{
	/// <summary>
	/// Structure for teams menu
	/// </summary>
	struct teamsMenu
	{
		void teamsManagementView(pm::types::User activeUser);

		void createTeamMenu(pm::types::User activeUser);
	};
}