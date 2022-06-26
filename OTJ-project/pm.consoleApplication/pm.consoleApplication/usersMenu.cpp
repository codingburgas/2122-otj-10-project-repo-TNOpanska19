#include "pch.h"
#include <iostream>
#include <windows.h>
#include "mainMenu.h"
#include "usersMenu.h"
#include "teamsMenu.h"
#include "../pm.types/team.h"
#include "../pm.types/user.h"
#include "../pm.bll/teamManager.h"
#include "../pm.bll/userManager.h"

pm::bll::UserManager userManager;

void userMenu::usersManagementView(pm::types::User activeUser)
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	mainMenu::gotoXY(2, 0); std::cout << "======================================";
	mainMenu::gotoXY(13, 1); std::cout << "USERS MANAGEMENT";
	mainMenu::gotoXY(2, 2); std::cout << "======================================";
	mainMenu::gotoXY(15, 4); std::cout << "Choose option";

	mainMenu::gotoXY(2, 12); std::cout << "======================================";

	mainMenu::gotoXY(10, 6); std::cout << "->";

	while (running)
	{
		mainMenu::gotoXY(13, 6); std::cout << "Create new user";
		mainMenu::gotoXY(13, 7); std::cout << "Update user";
		mainMenu::gotoXY(13, 8); std::cout << "Remove user";
		mainMenu::gotoXY(13, 9); std::cout << "View all users";
		mainMenu::gotoXY(13, 10); std::cout << "Go back";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 10)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_DOWN) && y != 10) //down button pressed
		{
			mainMenu::gotoXY(10, y); std::cout << "  ";
			y++;
			mainMenu::gotoXY(10, y); std::cout << "->";
			menuItem++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			mainMenu::gotoXY(10, y); std::cout << "  ";
			y--;
			mainMenu::gotoXY(10, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed

			switch (menuItem)
			{
			case 0:
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
				mainMenu::managementView();
				break;
			}
		}
	}
}

void userMenu::createUserMenu(pm::types::User activeUser)
{
	system("CLS");

	std::string username, firstName, lastName, email, password;
	bool privilege;

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

	userManager.createUser(username, firstName, lastName, email, privilege, userManager.hashString(password), activeUser);
}