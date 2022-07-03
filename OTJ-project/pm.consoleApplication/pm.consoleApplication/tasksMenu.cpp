/*****************************************************************//**
 * \file   tasksMenu.cpp
 * \brief  Source file for tasks management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "mainMenu.h"
#include "tasksMenu.h"

/// <summary>
/// Prints tasks management view
/// </summary>
void menu::tasksMenu::tasksManagementView()
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	menu::mainMenu::gotoXY(2, 0); std::cout << "======================================";
	menu::mainMenu::gotoXY(13, 1); std::cout << "TASKS MANAGEMENT";
	menu::mainMenu::gotoXY(2, 2); std::cout << "======================================";
	menu::mainMenu::gotoXY(15, 4); std::cout << "Choose option";
	menu::mainMenu::gotoXY(2, 14); std::cout << "======================================";
	menu::mainMenu::gotoXY(9, 6); std::cout << "->";

	while (running)
	{
		menu::mainMenu::gotoXY(12, 6); std::cout << "Create new task";
		menu::mainMenu::gotoXY(12, 7); std::cout << "Update task";
		menu::mainMenu::gotoXY(12, 8); std::cout << "Remove task";
		menu::mainMenu::gotoXY(12, 9); std::cout << "Change task status";
		menu::mainMenu::gotoXY(12, 10); std::cout << "Change task assignee";
		menu::mainMenu::gotoXY(12, 11); std::cout << "Task details view";
		menu::mainMenu::gotoXY(12, 12); std::cout << "Go back";

		system("pause>nul"); // The >nul bit causes it to print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 12)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 12) // Down arrow was pressed
		{
			menu::mainMenu::gotoXY(9, y); std::cout << "  ";
			y++;
			menu::mainMenu::gotoXY(9, y); std::cout << "->";
			menuItem++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 6) // Up arrow was pressed
		{
			menu::mainMenu::gotoXY(9, y); std::cout << "  ";
			y--;
			menu::mainMenu::gotoXY(9, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))	// Enter key was pressed
		{ 
			switch (menuItem)
			{
			case 6:
				menu::mainMenu::managementView();
			default:
				menu::mainMenu::gotoXY(5, 16);  std::cout << "Feature currently unavailable!";
			}
		}
	}
}
