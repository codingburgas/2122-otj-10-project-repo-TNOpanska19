/*****************************************************************//**
 * \file   mainMenu.h
 * \brief  Header file for login and management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "pch.h"

/// <summary>
/// Namespace for menu
/// </summary>
namespace menu
{
	/// <summary>
	/// Structure for main menu
	/// </summary>
	struct mainMenu
	{
		void loginMenu();

		void managementView();

		void currentUserInformation();

		void gotoXY(int x, int y);
	};
}