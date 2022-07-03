/*****************************************************************//**
 * \file   usersMenu.cpp
 * \brief  Source file for users management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "mainMenu.h"
#include "usersMenu.h"
#include "teamsMenu.h"
#include "../pm.types/team.h"
#include "../pm.types/user.h"
#include "../pm.bll/teamManager.h"
#include "../pm.bll/userManager.h"

/// <summary>
/// Object of mainMenu structure
/// </summary>
menu::mainMenu uMainMenu;

/// <summary>
/// Object of UserManager structure
/// </summary>
pm::bll::UserManager userManager;

/// <summary>
/// Prints users management view
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void menu::usersMenu::usersManagementView(pm::types::User activeUser)
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	uMainMenu.gotoXY(2, 0); std::cout << "======================================";
	uMainMenu.gotoXY(13, 1); std::cout << "USERS MANAGEMENT";
	uMainMenu.gotoXY(2, 2); std::cout << "======================================";
	uMainMenu.gotoXY(15, 4); std::cout << "Choose option";
	uMainMenu.gotoXY(2, 12); std::cout << "======================================";
	uMainMenu.gotoXY(10, 6); std::cout << "->";

	while (running)
	{
		uMainMenu.gotoXY(13, 6); std::cout << "Create new user";
		uMainMenu.gotoXY(13, 7); std::cout << "Update user";
		uMainMenu.gotoXY(13, 8); std::cout << "Remove user";
		uMainMenu.gotoXY(13, 9); std::cout << "View all users";
		uMainMenu.gotoXY(13, 10); std::cout << "Go back";

		system("pause>nul"); // The >nul bit causes it to print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 10)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 10) // Down arrow was pressed
		{
			uMainMenu.gotoXY(10, y); std::cout << "  ";
			y++;
			uMainMenu.gotoXY(10, y); std::cout << "->";
			menuItem++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 6) // Up arrow was pressed
		{
			uMainMenu.gotoXY(10, y); std::cout << "  ";
			y--;
			uMainMenu.gotoXY(10, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))	// Enter key was pressed
		{
			switch (menuItem)
			{
			case 0:
				system("CLS");
				createUserMenu(activeUser);
				break;
			case 1:
				userManager.updateUser(activeUser);
				break;
			case 2:
				userManager.removeUser(activeUser);
				break;
			case 3:
				userManager.displayUsers(activeUser);
				break;
			case 4:
				uMainMenu.managementView();
				break;
			}
		}
	}
}

/// <summary>
/// Prints create user prompt
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void menu::usersMenu::createUserMenu(pm::types::User activeUser)
{
	std::string username, firstName, lastName, email, password;
	int privilege;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               CREATE USER            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "                   Enter             " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "       Username: "; std::getline(std::cin, username); std::cout << std::endl;
	std::cout << "       First name: "; std::getline(std::cin, firstName); std::cout << std::endl;
	std::cout << "       Last name: "; std::getline(std::cin, lastName); std::cout << std::endl;
	std::cout << "       Email: "; std::getline(std::cin, email); std::cout << std::endl;
	std::cout << "       Privilege: "; std::cin >> privilege; std::cout << std::endl;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "       Password: ";  std::getline(std::cin, password); std::cout << std::endl;

	if (userManager.checkEmail(email) || (privilege != 0 && privilege != 1))
	{
		system("CLS"); 
		std::cout << " Some of the entered data was incorrect please try again!" << std::endl << std::endl;
		createUserMenu(activeUser); 
	}

	userManager.createUser(username, firstName, lastName, email, privilege, userManager.hashString(password), activeUser);
}