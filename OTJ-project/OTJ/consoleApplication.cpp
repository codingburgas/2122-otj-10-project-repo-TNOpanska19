#include <iostream>
#include <windows.h>
#include "mainMenu.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	SetConsoleTextAttribute(hConsole, 11);

	mainMenu::loginMenu();
}