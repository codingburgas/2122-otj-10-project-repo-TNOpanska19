#include "pch.h"
#include "mainMenu.h"
#include "tasksMenu.h"

void tasksMenu::tasksManagementView()
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	mainMenu::gotoXY(2, 0); std::cout << "======================================";
	mainMenu::gotoXY(13, 1); std::cout << "TASKS MANAGEMENT";
	mainMenu::gotoXY(2, 2); std::cout << "======================================";
	mainMenu::gotoXY(15, 4); std::cout << "Choose option";
	mainMenu::gotoXY(2, 14); std::cout << "======================================";
	mainMenu::gotoXY(9, 6); std::cout << "->";

	while (running)
	{
		mainMenu::gotoXY(12, 6); std::cout << "Create new task";
		mainMenu::gotoXY(12, 7); std::cout << "Update task";
		mainMenu::gotoXY(12, 8); std::cout << "Remove task";
		mainMenu::gotoXY(12, 9); std::cout << "Change task status";
		mainMenu::gotoXY(12, 10); std::cout << "Change task assignee";
		mainMenu::gotoXY(12, 11); std::cout << "Task details view";
		mainMenu::gotoXY(12, 12); std::cout << "Go back";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 12)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 12) //down button pressed
		{
			mainMenu::gotoXY(9, y); std::cout << "  ";
			y++;
			mainMenu::gotoXY(9, y); std::cout << "->";
			menuItem++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			mainMenu::gotoXY(9, y); std::cout << "  ";
			y--;
			mainMenu::gotoXY(9, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed
			switch (menuItem)
			{
			case 6:
				mainMenu::managementView();
			default:
				mainMenu::gotoXY(5, 16);  std::cout << "Feature currently unavailable!";
			}
		}
	}
}
