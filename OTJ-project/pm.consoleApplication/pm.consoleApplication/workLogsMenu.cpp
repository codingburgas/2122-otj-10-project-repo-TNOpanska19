#include "pch.h"
#include "mainMenu.h"
#include "workLogsMenu.h"

void menu::workLogsMenu::workLogsManagementView()
{
	system("CLS");

	int menuItem = 0, y = 6;
	bool running = true;

	menu::mainMenu::gotoXY(2, 0); std::cout << "======================================";
	menu::mainMenu::gotoXY(12, 1); std::cout << "WORK LOG MANAGEMENT";
	menu::mainMenu::gotoXY(2, 2); std::cout << "======================================";
	menu::mainMenu::gotoXY(15, 4); std::cout << "Choose option";
	menu::mainMenu::gotoXY(2, 11); std::cout << "======================================";
	menu::mainMenu::gotoXY(11, 6); std::cout << "->";

	while (running)
	{
		menu::mainMenu::gotoXY(14, 6); std::cout << "Create work log";
		menu::mainMenu::gotoXY(14, 7); std::cout << "Update work log";
		menu::mainMenu::gotoXY(14, 8); std::cout << "Remove work log";
		menu::mainMenu::gotoXY(14, 9); std::cout << "Go back";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 9)
			continue;

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
			continue;

		if (GetAsyncKeyState(VK_DOWN) && y != 9) //down button pressed
		{
			menu::mainMenu::gotoXY(11, y); std::cout << "  ";
			y++;
			menu::mainMenu::gotoXY(11, y); std::cout << "->";
			menuItem++;
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			menu::mainMenu::gotoXY(11, y); std::cout << "  ";
			y--;
			menu::mainMenu::gotoXY(11, y); std::cout << "->";
			menuItem--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed
			switch (menuItem)
			{
			case 3:
				menu::mainMenu::managementView();
			default:
				menu::mainMenu::gotoXY(5, 13);  std::cout << "Feature currently unavailable!";
			}
		}
	}
}
