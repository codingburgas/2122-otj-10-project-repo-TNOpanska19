#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include "../pm.types/User.h"
#include "../pm.bll/userManager.h"
#include "mainMenu.h"
#include "teamsMenu.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

pm::bll::UserManager uManager;
pm::types::User activeUser;

void mainMenu::loginMenu()
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

	if (uManager.loginUser(username, password))
	{
		std::cout << "user exists";
		activeUser = uManager.getActiveUser(username);
	}

	else
	{
		system("CLS");
		std::cout << " User does not exist. Please try to log in again." << std::endl << std::endl;
		mainMenu::loginMenu();
	}

	if (activeUser.privilege == 1)
	{
		mainMenu::managementView();
	}

	else
	{
		currentUserInformation();
	}
}

void mainMenu::managementView()
{
	system("CLS");

	int menu_item = 0, y = 6;
	bool running = true;

	gotoXY(2, 0); std::cout << "======================================";
	gotoXY(12, 1); std::cout << "MANAGEMENT OPTIONS";
	gotoXY(2, 2); std::cout << "======================================";
	gotoXY(15, 4); std::cout << "Choose option";

	gotoXY(2, 13); std::cout << "======================================";

	gotoXY(10, 6); std::cout << "->";

	while (running)
	{
		gotoXY(13, 6); std::cout << "Users Management";
		gotoXY(13, 7); std::cout << "Teams Management";
		gotoXY(13, 8); std::cout << "Projects Management";
		gotoXY(13, 9); std::cout << "Task Managament";
		gotoXY(13, 10); std::cout << "Work Log Management";
		gotoXY(13, 11); std::cout << "Exit";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 11)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_DOWN) && y != 11) //down button pressed
		{
			gotoXY(10, y); std::cout << "  ";
			y++;
			gotoXY(10, y); std::cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			gotoXY(10, y); std::cout << "  ";
			y--;
			gotoXY(10, y); std::cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed

			switch (menu_item)
			{
			case 0:
				mainMenu::usersManagementView();
				break;
			case 1:
				teamMenu::teamsManagementView();
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				system("CLS");
				std::cout << "Thanks for using my program! :)" << std::endl;
				exit(0);
				break;
			}
		}
	}
}

void mainMenu::usersManagementView()
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	gotoXY(2, 0); std::cout << "======================================";
	gotoXY(13, 1); std::cout << "USERS MANAGEMENT";
	gotoXY(2, 2); std::cout << "======================================";
	gotoXY(15, 4); std::cout << "Choose option";

	gotoXY(2, 13); std::cout << "======================================";

	gotoXY(10, 6); std::cout << "->";

	while (running)
	{
		gotoXY(13, 6); std::cout << "Create new user";
		gotoXY(13, 7); std::cout << "Update user";
		gotoXY(13, 8); std::cout << "Remove user";
		gotoXY(13, 9); std::cout << "View profile";
		gotoXY(13, 10); std::cout << "View all users";
		gotoXY(13, 11); std::cout << "Go back";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 11)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_DOWN) && y != 11) //down button pressed
		{
			gotoXY(10, y); std::cout << "  ";
			y++;
			gotoXY(10, y); std::cout << "->";
			menuItem++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			gotoXY(10, y); std::cout << "  ";
			y--;
			gotoXY(10, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed

			switch (menuItem)
			{
			case 0:
				createUserMenu();
				break;
			case 1:
				uManager.updateUser();
				break;
			case 2:
				uManager.removeUser();
				break;
			case 3:
				currentUserInformation();
				break;
			case 4:
				uManager.displayUsers();
				break;
			case 5:
				mainMenu::managementView();
				break;
			}
		}
	}
}

void mainMenu::gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void mainMenu::createUserMenu()
{
	system("CLS");

	int id = 69;
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

	uManager.createUser(id, username, firstName, lastName, email, privilege, uManager.hashString(password));
}

void mainMenu::currentUserInformation()
{
	system("CLS");

	std::cout << "  ======================================" << std::endl;
	std::cout << "               YOUR PROFILE        " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "            User Information        " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "       Username: " << activeUser.username << std::endl;
	std::cout << "       First name: " << activeUser.firstName << std::endl;
	std::cout << "       Last name: " << activeUser.lastName << std::endl;
	std::cout << "       Email: " << activeUser.email << std::endl;
	std::cout << "       Privilege: ";

	if (activeUser.privilege == 0)
		std::cout << "user";

	else if (activeUser.privilege == 1)
		std::cout << "admin";

	std::cout << std::endl << std::endl << "  ======================================" << std::endl;

	if (activeUser.privilege == 1)
	{
		std::cout << "  Press any key to go back to menu...";
		_getch();
		mainMenu::usersManagementView();
	}
}
