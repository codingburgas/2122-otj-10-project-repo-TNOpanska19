/*****************************************************************//**
 * \file   pm.consoleApplication.cpp
 * \brief  Main source file of the program
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "mainMenu.h"
#include "../pm.bll/userManager.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/// <summary>
/// Object of mainMenu structure
/// </summary>
menu::mainMenu app;

/// <summary>
/// Main entry point of the application
/// </summary>
/// <returns></returns>
int main()
{
	SetConsoleTextAttribute(hConsole, 11);

	app.loginMenu();
}