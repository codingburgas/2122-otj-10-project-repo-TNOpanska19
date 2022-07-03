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
/// Object of mainMenu structure
/// </summary>
menu::mainMenu tsMainMenu;

/// <summary>
/// Prints tasks management view
/// </summary>
void menu::tasksMenu::tasksManagementView()
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	tsMainMenu.gotoXY(2, 0); std::cout << "======================================";
	tsMainMenu.gotoXY(13, 1); std::cout << "TASKS MANAGEMENT";
	tsMainMenu.gotoXY(2, 2); std::cout << "======================================";
	tsMainMenu.gotoXY(15, 4); std::cout << "Choose option";
	tsMainMenu.gotoXY(2, 14); std::cout << "======================================";
	tsMainMenu.gotoXY(9, 6); std::cout << "->";

	while (running)
	{
		tsMainMenu.gotoXY(12, 6); std::cout << "Create new task";
		tsMainMenu.gotoXY(12, 7); std::cout << "Update task";
		tsMainMenu.gotoXY(12, 8); std::cout << "Remove task";
		tsMainMenu.gotoXY(12, 9); std::cout << "Change task status";
		tsMainMenu.gotoXY(12, 10); std::cout << "Change task assignee";
		tsMainMenu.gotoXY(12, 11); std::cout << "Task details view";
		tsMainMenu.gotoXY(12, 12); std::cout << "Go back";

		system("pause>nul"); // The >nul bit causes it to print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 12)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 12) // Down arrow was pressed
		{
			tsMainMenu.gotoXY(9, y); std::cout << "  ";
			y++;
			tsMainMenu.gotoXY(9, y); std::cout << "->";
			menuItem++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 6) // Up arrow was pressed
		{
			tsMainMenu.gotoXY(9, y); std::cout << "  ";
			y--;
			tsMainMenu.gotoXY(9, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))	// Enter key was pressed
		{ 
			switch (menuItem)
			{
			case 6:
				tsMainMenu.managementView();
			default:
				tsMainMenu.gotoXY(5, 16);  std::cout << "Feature currently unavailable!";
			}
		}
	}
}
