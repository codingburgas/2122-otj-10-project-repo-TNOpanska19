#include "pch.h"
#include "mainMenu.h"
#include "teamsMenu.h"
#include "../pm.types/team.h"
#include "../pm.types/user.h"
#include "../pm.bll/teamManager.h"

pm::bll::TeamManager tManager;

void menu::teamsMenu::teamsManagementView(pm::types::User activeUser)
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	menu::mainMenu::gotoXY(2, 0); std::cout << "======================================";
	menu::mainMenu::gotoXY(13, 1); std::cout << "TEAMS MANAGEMENT";
	menu::mainMenu::gotoXY(2, 2); std::cout << "======================================";
	menu::mainMenu::gotoXY(15, 4); std::cout << "Choose option";
	menu::mainMenu::gotoXY(2, 13); std::cout << "======================================";
	menu::mainMenu::gotoXY(8, 6); std::cout << "->";

	while (running)
	{
		menu::mainMenu::gotoXY(11, 6); std::cout << "Create new team";
		menu::mainMenu::gotoXY(11, 7); std::cout << "Update team";
		menu::mainMenu::gotoXY(11, 8); std::cout << "Remove team";
		menu::mainMenu::gotoXY(11, 9); std::cout << "View all teams";
		menu::mainMenu::gotoXY(11, 10); std::cout << "Assign users to team";
		menu::mainMenu::gotoXY(11, 11); std::cout << "Go back";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 11)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 11) //down button pressed
		{
			menu::mainMenu::gotoXY(8, y); std::cout << "  ";
			y++;
			menu::mainMenu::gotoXY(8, y); std::cout << "->";
			menuItem++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			menu::mainMenu::gotoXY(8, y); std::cout << "  ";
			y--;
			menu::mainMenu::gotoXY(8, y); std::cout << "->";
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
				menu::mainMenu::managementView();
				break;
			}
		}
	}
}

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