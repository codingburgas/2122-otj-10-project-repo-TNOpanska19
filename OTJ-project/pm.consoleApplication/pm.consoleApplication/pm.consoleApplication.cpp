#include <iostream>
#include <windows.h>
#include "mainMenu.h"
#include "../pm.bll/userManager.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "a";
	mainMenu::loginMenu();
}