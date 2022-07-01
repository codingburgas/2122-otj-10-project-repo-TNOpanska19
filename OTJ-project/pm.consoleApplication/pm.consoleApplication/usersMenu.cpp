#include "pch.h"
#include "mainMenu.h"
#include "usersMenu.h"
#include "teamsMenu.h"
#include "../pm.types/team.h"
#include "../pm.types/user.h"
#include "../pm.bll/teamManager.h"
#include "../pm.bll/userManager.h"

pm::bll::UserManager userManager;

void menu::usersMenu::usersManagementView(pm::types::User activeUser)
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	menu::mainMenu::gotoXY(2, 0); std::cout << "======================================";
	menu::mainMenu::gotoXY(13, 1); std::cout << "USERS MANAGEMENT";
	menu::mainMenu::gotoXY(2, 2); std::cout << "======================================";
	menu::mainMenu::gotoXY(15, 4); std::cout << "Choose option";
	menu::mainMenu::gotoXY(2, 12); std::cout << "======================================";
	menu::mainMenu::gotoXY(10, 6); std::cout << "->";

	while (running)
	{
		menu::mainMenu::gotoXY(13, 6); std::cout << "Create new user";
		menu::mainMenu::gotoXY(13, 7); std::cout << "Update user";
		menu::mainMenu::gotoXY(13, 8); std::cout << "Remove user";
		menu::mainMenu::gotoXY(13, 9); std::cout << "View all users";
		menu::mainMenu::gotoXY(13, 10); std::cout << "Go back";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 10)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 10) //down button pressed
		{
			menu::mainMenu::gotoXY(10, y); std::cout << "  ";
			y++;
			menu::mainMenu::gotoXY(10, y); std::cout << "->";
			menuItem++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			menu::mainMenu::gotoXY(10, y); std::cout << "  ";
			y--;
			menu::mainMenu::gotoXY(10, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed
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
				menu::mainMenu::managementView();
				break;
			}
		}
	}
}

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