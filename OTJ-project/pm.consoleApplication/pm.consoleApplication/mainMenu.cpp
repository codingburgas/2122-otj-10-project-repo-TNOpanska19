#include "pch.h"
#include "../pm.types/user.h"
#include "../pm.bll/userManager.h"
#include "mainMenu.h"
#include "usersMenu.h"
#include "teamsMenu.h"
#include "projectsMenu.h"

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
		activeUser = uManager.getActiveUser(username);
	}

	else
	{
		system("CLS");
		std::cout << " User does not exist. Please try to log in again." << std::endl << std::endl;
		mainMenu::loginMenu();
	}

	mainMenu::managementView();
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

	gotoXY(2, 14); std::cout << "======================================";

	gotoXY(10, 6); std::cout << "->";

	while (running)
	{
		gotoXY(13, 6); std::cout << "Users Management";
		gotoXY(13, 7); std::cout << "Teams Management";
		gotoXY(13, 8); std::cout << "Projects Management";
		gotoXY(13, 9); std::cout << "Task Managament";
		gotoXY(13, 10); std::cout << "Work Log Management";
		gotoXY(13, 11); std::cout << "View your profile";
		gotoXY(13, 12); std::cout << "Exit";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 12)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_DOWN) && y != 12) //down button pressed
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
				if (activeUser.privilege == 1)
					usersMenu::usersManagementView(activeUser);
				else
					gotoXY(13, 16); std::cout << "Access restricted!";
				break;
			case 1:
				if (activeUser.privilege == 1)
					teamsMenu::teamsManagementView(activeUser);
				else
					gotoXY(13, 16); std::cout << "Access restricted!";
				break;
			case 2:
				projectsMenu::projectsManagementView(activeUser);
				break;
			case 3:
				break;
			case 4:
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

void mainMenu::gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void mainMenu::currentUserInformation()
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

	rawTime = &activeUser.dateOfCreation;
	localtime_s(&time, rawTime);
	strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
	std::cout << "     Created on: " << buffer << std::endl;
	std::cout << "     Id of creator: " << activeUser.idOfCreator << std::endl;

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
	_getch();
	mainMenu::managementView();
}
