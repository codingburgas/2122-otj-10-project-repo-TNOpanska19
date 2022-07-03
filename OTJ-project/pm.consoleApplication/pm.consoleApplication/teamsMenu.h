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
/// Namespace for team management view
/// </summary>
namespace menu::teamsMenu
{
	void teamsManagementView(pm::types::User activeUser);

	void createTeamMenu(pm::types::User activeUser);
}