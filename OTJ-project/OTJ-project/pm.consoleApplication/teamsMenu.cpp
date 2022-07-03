/*****************************************************************//**
 * \file   teamsMenu.cpp
 * \brief  Source file for teams management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "mainMenu.h"
#include "teamsMenu.h"
#include "../pm.types/team.h"
#include "../pm.types/user.h"
#include "../pm.bll/teamManager.h"

/// <summary>
/// Object of mainMenu structure
/// </summary>
menu::mainMenu tMainMenu;

/// <summary>
/// Object of TeamManager structure
/// </summary>
pm::bll::TeamManager tManager;

/// <summary>
/// Prints teams management view
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void menu::teamsMenu::teamsManagementView(pm::types::User activeUser)
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	tMainMenu.gotoXY(2, 0); std::cout << "======================================";
	tMainMenu.gotoXY(13, 1); std::cout << "TEAMS MANAGEMENT";
	tMainMenu.gotoXY(2, 2); std::cout << "======================================";
	tMainMenu.gotoXY(15, 4); std::cout << "Choose option";
	tMainMenu.gotoXY(2, 13); std::cout << "======================================";
	tMainMenu.gotoXY(8, 6); std::cout << "->";

	while (running)
	{
		tMainMenu.gotoXY(11, 6); std::cout << "Create new team";
		tMainMenu.gotoXY(11, 7); std::cout << "Update team";
		tMainMenu.gotoXY(11, 8); std::cout << "Remove team";
		tMainMenu.gotoXY(11, 9); std::cout << "View all teams";
		tMainMenu.gotoXY(11, 10); std::cout << "Assign users to team";
		tMainMenu.gotoXY(11, 11); std::cout << "Go back";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 11)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 11) //down button pressed
		{
			tMainMenu.gotoXY(8, y); std::cout << "  ";
			y++;
			tMainMenu.gotoXY(8, y); std::cout << "->";
			menuItem++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			tMainMenu.gotoXY(8, y); std::cout << "  ";
			y--;
			tMainMenu.gotoXY(8, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed
			switch (menuItem)
			{
			case 0:
				teamsMenu::createTeamMenu(activeUser);
				break;
			case 1:
				tManager.updateTeam(activeUser);
				break;
			case 2:
				tManager.removeTeam(activeUser);
				break;
			case 3:
				tManager.displayTeams(activeUser);
				break;
			case 4:
				tManager.assignUsersToTeam(activeUser);
				break;
			case 5:
				tMainMenu.managementView();
				break;
			}
		}
	}
}

/// <summary>
/// Prints create team prompt
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void menu::teamsMenu::createTeamMenu(pm::types::User activeUser)
{
	system("CLS");

	std::string title;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               CREATE TEAM            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "                   Enter             " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "       Title: "; std::getline(std::cin, title); std::cout << std::endl;

	tManager.createTeam(title, activeUser);
}