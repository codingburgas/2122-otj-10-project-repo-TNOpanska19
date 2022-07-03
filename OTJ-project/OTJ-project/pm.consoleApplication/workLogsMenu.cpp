/*****************************************************************//**
 * \file   workLogsMenu.cpp
 * \brief  Source file for work log management view
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "mainMenu.h"
#include "workLogsMenu.h"

/// <summary>
/// Object of mainMenu structure
/// </summary>
menu::mainMenu wMainMenu;

/// <summary>
/// Prints work log management view
/// </summary>
void menu::workLogsMenu::workLogsManagementView()
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	wMainMenu.gotoXY(2, 0); std::cout << "======================================";
	wMainMenu.gotoXY(12, 1); std::cout << "WORK LOG MANAGEMENT";
	wMainMenu.gotoXY(2, 2); std::cout << "======================================";
	wMainMenu.gotoXY(15, 4); std::cout << "Choose option";
	wMainMenu.gotoXY(2, 11); std::cout << "======================================";
	wMainMenu.gotoXY(11, 6); std::cout << "->";

	while (running)
	{
		wMainMenu.gotoXY(14, 6); std::cout << "Create work log";
		wMainMenu.gotoXY(14, 7); std::cout << "Update work log";
		wMainMenu.gotoXY(14, 8); std::cout << "Remove work log";
		wMainMenu.gotoXY(14, 9); std::cout << "Go back";

		system("pause>nul"); // The >nul bit causes it to print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 9)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 9) // Down arrow was pressed
		{
			wMainMenu.gotoXY(11, y); std::cout << "  ";
			y++;
			wMainMenu.gotoXY(11, y); std::cout << "->";
			menuItem++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 6) // Up arrow was pressed
		{
			wMainMenu.gotoXY(11, y); std::cout << "  ";
			y--;
			wMainMenu.gotoXY(11, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))	// Enter key was pressed
		{
			switch (menuItem)
			{
			case 3:
				wMainMenu.managementView();
			default:
				wMainMenu.gotoXY(5, 13);  std::cout << "Feature currently unavailable!";
			}
		}
	}
}
