/*****************************************************************//**
 * \file   usersMenu.h
 * \brief  Header file for user management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "pch.h"
#include "../pm.types/user.h"

/// <summary>
/// Namespace for user management view
/// </summary>
namespace menu::usersMenu
{
	void usersManagementView(pm::types::User activeUser);

	void createUserMenu(pm::types::User activeUser);
}