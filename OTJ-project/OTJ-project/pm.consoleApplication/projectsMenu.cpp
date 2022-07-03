/*****************************************************************//**
 * \file   projectsMenu.cpp
 * \brief  Source file for projects management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "projectsMenu.h"
#include "mainMenu.h"
#include "usersMenu.h"
#include "teamsMenu.h"
#include "../pm.types/team.h"
#include "../pm.types/user.h"
#include "../pm.bll/teamManager.h"
#include "../pm.bll/userManager.h"
#include "../pm.bll/projectManager.h"

/// <summary>
/// Object of mainMenu structure
/// </summary>
menu::mainMenu pMainMenu;

/// <summary>
/// Object of ProjectManager structure
/// </summary>
pm::bll::ProjectManager pManager;

/// <summary>
/// Prints projects management view
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void menu::projectsMenu::projectsManagementView(pm::types::User activeUser)
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	pMainMenu.gotoXY(2, 0); std::cout << "======================================";
	pMainMenu.gotoXY(11, 1); std::cout << "PROJECTS MANAGEMENT";
	pMainMenu.gotoXY(2, 2); std::cout << "======================================";
	pMainMenu.gotoXY(15, 4); std::cout << "Choose option";
	pMainMenu.gotoXY(2, 13); std::cout << "======================================";
	pMainMenu.gotoXY(8, 6); std::cout << "->";

	while (running)
	{
		pMainMenu.gotoXY(11, 6); std::cout << "Create new project";
		pMainMenu.gotoXY(11, 7); std::cout << "Update project";
		pMainMenu.gotoXY(11, 8); std::cout << "Remove project";
		pMainMenu.gotoXY(11, 9); std::cout << "View your projects";
		pMainMenu.gotoXY(11, 10); std::cout << "Assign teams to project";
		pMainMenu.gotoXY(11, 11); std::cout << "Go back";

		system("pause>nul"); // The >nul bit causes it to print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 11)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 11) // Down arrow was pressed
		{
			pMainMenu.gotoXY(8, y); std::cout << "  ";
			y++;
			pMainMenu.gotoXY(8, y); std::cout << "->";
			menuItem++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && y != 6) // Up arrow was pressed
		{
			pMainMenu.gotoXY(8, y); std::cout << "  ";
			y--;
			pMainMenu.gotoXY(8, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))	// Enter key was pressed
		{ 
			switch (menuItem)
			{
			case 0:
				createProjectMenu(activeUser);
				break;
			case 1:
				pManager.updateProject(activeUser);
				break;
			case 2:
				pManager.removeProject(activeUser);
				break;
			case 3:
				pManager.displayProjects(activeUser);
				break;
			case 4:
				pManager.assignTeamsToProject(activeUser);
				break;
			case 5:
				pMainMenu.managementView();
				break;
			}
		}
	}
}

/// <summary>
/// Prints create project prompt
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void menu::projectsMenu::createProjectMenu(pm::types::User activeUser)
{
	system("CLS");

	std::string title, description;

	std::cout << "  ======================================" << std::endl;
	std::cout << "              CREATE PROJECT            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "                  Enter             " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "       Title: "; std::getline(std::cin, title); std::cout << std::endl;
	std::cout << "       Description: "; std::getline(std::cin, description); std::cout << std::endl;

	pManager.createProject(title, description, activeUser);
}