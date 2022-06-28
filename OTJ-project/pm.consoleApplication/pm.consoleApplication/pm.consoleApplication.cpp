#include "pch.h"
#include "mainMenu.h"
#include "../pm.bll/userManager.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "D";
	mainMenu::loginMenu();
}