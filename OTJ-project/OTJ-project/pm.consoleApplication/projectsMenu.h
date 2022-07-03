/*****************************************************************//**
 * \file   projectsMenu.h
 * \brief  Header file for projects management view
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
	/// Structure for projects menu
	/// </summary>
	struct projectsMenu 
	{
		void projectsManagementView(pm::types::User activeUser);

		void createProjectMenu(pm::types::User activeUser);
	};
}