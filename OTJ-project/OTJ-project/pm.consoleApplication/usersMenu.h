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
/// Namespace for menu
/// </summary>
namespace menu
{
	/// <summary>
	/// Structure for users menu
	/// </summary>
	struct usersMenu
	{
		void usersManagementView(pm::types::User activeUser);

		void createUserMenu(pm::types::User activeUser);
	};
}