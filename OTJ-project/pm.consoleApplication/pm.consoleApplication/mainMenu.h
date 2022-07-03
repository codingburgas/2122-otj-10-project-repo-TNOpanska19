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
/// Namespace for main menu
/// </summary>
namespace menu::mainMenu
{
	void loginMenu();

	void managementView();

	void currentUserInformation();

	void gotoXY(int x, int y);
}