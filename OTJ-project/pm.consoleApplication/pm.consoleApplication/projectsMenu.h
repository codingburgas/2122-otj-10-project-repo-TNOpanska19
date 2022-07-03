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
/// Namespace for projects management view
/// </summary>
namespace menu::projectsMenu
{
	void projectsManagementView(pm::types::User activeUser);

	void createProjectMenu(pm::types::User activeUser);
}