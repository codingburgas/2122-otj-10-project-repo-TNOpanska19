/*****************************************************************//**
 * \file   mainMenu.cpp
 * \brief  Source file for login and management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "../pm.types/user.h"
#include "../pm.bll/userManager.h"
#include "mainMenu.h"
#include "usersMenu.h"
#include "teamsMenu.h"
#include "projectsMenu.h"
#include "tasksMenu.h"
#include "workLogsMenu.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Used for gotoXY
COORD CursorPosition; // Used for gotoXY

/// <summary>
/// Object of UserManager structure
/// </summary>
pm::bll::UserManager uManager;

/// <summary>
/// Object of User structure
/// </summary>
pm::types::User activeUser;

/// <summary>
/// Prints login prompt
/// </summary>
void menu::mainMenu::loginMenu()
{
	std::string username, password;

	std::cout << "  ======================================" << std::endl;
	std::cout << "                  LOG IN            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "                  Enter             " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "       Username: "; std::getline(std::cin, username); std::cout << std::endl;
	std::cout << "       Password: ";  std::getline(std::cin, password); std::cout << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "  ======================================" << std::endl;

	if (uManager.loginUser(username, password))			// Checks if there is a user with such name and password, after which (if true) stores user
		activeUser = uManager.getActiveUser(username);

	else	// No such user exists
	{
		system("CLS");
		std::cout << " User does not exist. Please try to log in again." << std::endl << std::endl;
		mainMenu::loginMenu();
	}

	mainMenu::managementView();
}

/// <summary>
/// Prints management view menu
/// </summary>
void menu::mainMenu::managementView()
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	gotoXY(2, 0); std::cout << "======================================";
	gotoXY(12, 1); std::cout << "MANAGEMENT OPTIONS";
	gotoXY(2, 2); std::cout << "======================================";
	gotoXY(14, 4); std::cout << "Choose option";
	gotoXY(2, 14); std::cout << "======================================";
	gotoXY(9, 6); std::cout << "->";

	while (running)
	{
		gotoXY(12, 6); std::cout << "Users Management";
		gotoXY(12, 7); std::cout << "Teams Management";
		gotoXY(12, 8); std::cout << "Projects Management";
		gotoXY(12, 9); std::cout << "Task Managament";
		gotoXY(12, 10); std::cout << "Work Log Management";
		gotoXY(12, 11); std::cout << "View your profile";
		gotoXY(12, 12); std::cout << "Exit";

		system("pause>nul"); // The >nul bit causes it to print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 12)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 12) // Down arrow was pressed
		{
			gotoXY(9, y); std::cout << "  ";
			y++;
			gotoXY(9, y); std::cout << "->";
			menuItem++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && y != 6) // Up arrow was pressed
		{
			gotoXY(9, y); std::cout << "  ";
			y--;
			gotoXY(9, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))	// Enter key was pressed
		{ 
			switch (menuItem)
			{
			case 0:
				if (activeUser.privilege == 1)		// Only admins can access user management
					usersMenu::usersManagementView(activeUser);
				else
					gotoXY(13, 16); std::cout << "Access restricted!";
				break;
			case 1:
				if (activeUser.privilege == 1)		// Only admins can access teams management
					teamsMenu::teamsManagementView(activeUser);
				else
					gotoXY(13, 16); std::cout << "Access restricted!";
				break;
			case 2:
				projectsMenu::projectsManagementView(activeUser);
				break;
			case 3:
				tasksMenu::tasksManagementView();
				break;
			case 4:
				workLogsMenu::workLogsManagementView();
				break;
			case 5:
				currentUserInformation();
				break;
			case 6:
				system("CLS");
				std::cout << "Thanks for using my program! :)" << std::endl;
				exit(0);
				break;
			}
		}
	}
}

/// <summary>
/// Used to position character output at a particular place
/// </summary>
/// <param name="x">Used for X coord</param>
/// <param name="y">Used for Y coord</param>
void menu::mainMenu::gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

/// <summary>
/// Prints the current user's information
/// </summary>
void menu::mainMenu::currentUserInformation()
{
	system("CLS");

	char buffer[80];
	struct tm time;
	const time_t* rawTime;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               YOUR PROFILE        " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "            User Information        " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "     Username: " << activeUser.username << std::endl;
	std::cout << "     First name: " << activeUser.firstName << std::endl;
	std::cout << "     Last name: " << activeUser.lastName << std::endl;

	// Transform time_t to a readable format
	rawTime = &activeUser.dateOfCreation;
	localtime_s(&time, rawTime);
	strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
	std::cout << "     Created on: " << buffer << std::endl;
	std::cout << "     Id of creator: " << activeUser.idOfCreator << std::endl;

	// Transform time_t to a readable format
	rawTime = &activeUser.dateOfLastChange;
	localtime_s(&time, rawTime);
	strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
	std::cout << "     Last change on: " << buffer << std::endl;
	std::cout << "     Id of user who made change: " << activeUser.idOfChange << std::endl;
	std::cout << "     Email: " << activeUser.email << std::endl;
	std::cout << "     Privilege: ";

	if (activeUser.privilege == 0)
		std::cout << "user";

	else if (activeUser.privilege == 1)
		std::cout << "admin";

	std::cout << std::endl << std::endl << "  ======================================" << std::endl;
	std::cout << std::endl << "  Press any key to go back to menu...";
	(void)_getch();
	menu::mainMenu::managementView();
}
