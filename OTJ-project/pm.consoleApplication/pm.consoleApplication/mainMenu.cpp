#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include "../pm.types/User.h"
#include "../pm.bll/userManager.h"
#include "mainMenu.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto

//pm::dal::UserStore uStore;
pm::bll::UserManager uManager;
pm::types::User activeUser;

void mainMenu::loginMenu()
{
	//uStore.getData();

	std::string username, password;

	std::cout << "  ==============================" << std::endl;
	std::cout << "             LOG IN             " << std::endl;
	std::cout << "  ==============================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "              Enter             " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "       Username: "; std::getline(std::cin, username); std::cout << std::endl;
	std::cout << "       Password: ";  std::getline(std::cin, password); std::cout << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "  ==============================" << std::endl;

	if (uManager.loginUser(username, password))
	{
		std::cout << "user exists";
		// get user functionality
	}

	else
	{
		system("CLS");
		std::cout << " User does not exist. Please try to log in again." << std::endl << std::endl;
		mainMenu::loginMenu();
	}

	mainMenu::usersManagementView();


	// takes user to register, update, remove users menu if actve user's privilage is 1


	/*
	int uid;
	std::cout << "Enter id: "; std::cin >> uid;

	pm::types::User userche = u_store.getById(uid);
	std::cout << std::endl << userche.id << " " << userche.username << " " << userche.firstName;
	*/
}


void mainMenu::usersManagementView()
{
	system("CLS");

	int menu_item = 0, y = 6;
	bool running = true;

	gotoXY(2, 0); std::cout << "===============================";
	gotoXY(9, 1); std::cout << "USERS MANAGEMENT";
	gotoXY(2, 2); std::cout << "===============================";
	gotoXY(11, 4); std::cout << "Choose option";

	gotoXY(6, 6); std::cout << "->";

	while (running)
	{
		gotoXY(9, 6); std::cout << "Create new user";
		gotoXY(9, 7); std::cout << "Update user";
		gotoXY(9, 8); std::cout << "Remove user";
		gotoXY(9, 9); std::cout << "View current user";
		gotoXY(9, 10); std::cout << "View all users";
		gotoXY(9, 11); std::cout << "Advanced options";
		gotoXY(9, 12); std::cout << "Exit";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && y + 1 > 12)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_UP) && y - 1 < 6)
		{
			continue;
		}

		if (GetAsyncKeyState(VK_DOWN) && y != 12) //down button pressed
		{
			gotoXY(6, y); std::cout << "  ";
			y++;
			gotoXY(6, y); std::cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && y != 6) //up button pressed
		{
			gotoXY(6, y); std::cout << "  ";
			y--;
			gotoXY(6, y); std::cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{ // Enter key pressed

			switch (menu_item) {

			case 0:
				mainMenu::createUserMenu();
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			}

			break;
		}

	}
}

void mainMenu::gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void mainMenu::createUserMenu()
{
	system("CLS");

	int id = 69;
	std::string username, firstName, lastName, email, password;
	bool privilage;

	std::cout << "  ==============================" << std::endl;
	std::cout << "           CREATE USER          " << std::endl;
	std::cout << "  ==============================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "              Enter             " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "       Username: "; std::getline(std::cin, username); std::cout << std::endl;
	std::cout << "       First name: "; std::getline(std::cin, firstName); std::cout << std::endl;
	std::cout << "       Last name: "; std::getline(std::cin, lastName); std::cout << std::endl;
	std::cout << "       Email: "; std::getline(std::cin, email); std::cout << std::endl;
	std::cout << "       Privilage: "; std::cin >> privilage; std::cout << std::endl;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "       Password: ";  std::getline(std::cin, password); std::cout << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "  ==============================" << std::endl;



	// uStore.addToUsers(id, username, firstName, lastName, email, privilage, uManager.hashString(password));
}