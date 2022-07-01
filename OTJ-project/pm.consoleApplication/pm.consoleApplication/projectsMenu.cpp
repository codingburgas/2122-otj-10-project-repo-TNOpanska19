#include "projectsMenu.h"
#include "mainMenu.h"
#include "usersMenu.h"
#include "teamsMenu.h"
#include "../pm.types/team.h"
#include "../pm.types/user.h"
#include "../pm.bll/teamManager.h"
#include "../pm.bll/userManager.h"
#include "../pm.bll/projectManager.h"

pm::bll::ProjectManager pManager;

void menu::projectsMenu::projectsManagementView(pm::types::User activeUser)
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	menu::mainMenu::gotoXY(2, 0); std::cout << "======================================";
	menu::mainMenu::gotoXY(11, 1); std::cout << "PROJECTS MANAGEMENT";
	menu::mainMenu::gotoXY(2, 2); std::cout << "======================================";
	menu::mainMenu::gotoXY(15, 4); std::cout << "Choose option";
	menu::mainMenu::gotoXY(2, 13); std::cout << "======================================";
	menu::mainMenu::gotoXY(8, 6); std::cout << "->";

	while (running)
	{
		menu::mainMenu::gotoXY(11, 6); std::cout << "Create new project";
		menu::mainMenu::gotoXY(11, 7); std::cout << "Update project";
		menu::mainMenu::gotoXY(11, 8); std::cout << "Remove project";
		menu::mainMenu::gotoXY(11, 9); std::cout << "View your projects";
		menu::mainMenu::gotoXY(11, 10); std::cout << "Assign teams to project";
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
				projectsMenu::createProjectMenu(activeUser);
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
				menu::mainMenu::managementView();
				break;
			}
		}
	}
}

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