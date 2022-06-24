#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "mainMenu.h"
//#include "../pm.types/User.h"
//#include "../pm.bll/userManager.h"

std::vector<pm::types::User> users;
pm::dal::UserStore uStore;
pm::bll::UserManager uManager;

pm::types::User activeUser;

void mainMenu::loginMenu()
{
    uStore.getData();

	// u.displayUsers();

	/*
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

	if (u_manager.loginUser(username, password))
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

	mainMenu::adminOptionsMenu();
	// takes user to register, update, remove users menu if actve user's privilage is 1
	*/

	/*
	int uid;
	std::cout << "Enter id: "; std::cin >> uid;

	pm::types::User userche = u_store.getById(uid);
	std::cout << std::endl << userche.id << " " << userche.username << " " << userche.firstName;
	*/

	mainMenu::createUserMenu();
	uStore.displayUsers();
}


void mainMenu::adminOptionsMenu()
{
	system("CLS");

    std::cout << "  ==============================" << std::endl;
    std::cout << "               MENU             " << std::endl;
    std::cout << "  ==============================" << std::endl;
    std::cout << "                                " << std::endl;
    std::cout << "          Choose option         " << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "       1) Create new user     " << std::endl;
	std::cout << "       2) Update user           " << std::endl;
	std::cout << "       3) Remove user           " << std::endl;
	std::cout << "       4) View current user     " << std::endl;
	std::cout << "       5) View all users        " << std::endl;
	std::cout << "       6) Advanced options      " << std::endl;
	std::cout << "       7) Exit                  " << std::endl;
    std::cout << "                                " << std::endl;
    std::cout << "  ==============================" << std::endl;
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

	// hash the password

	uStore.addToUsers(id, username, firstName, lastName, email, privilage, password);
}

// za UserStore.cpp

bool pm::dal::UserStore::getByUsername(std::string username)
{
	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i].username == username)
		{
			return true;
		}
	}

	return false;
}

pm::types::User pm::dal::UserStore::getById(size_t id)
{
	pm::types::User rUser;

	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i].id == id)
		{
			return users[i];
		}
	}
}

void pm::dal::UserStore::getData()	// Starts reading the Records.txt file so it can input information into it
{
	std::ifstream file("Users.txt", std::fstream::in);

	std::string id, userName, firstName, lastName, email, /* dateOfCreation, idOfCreator, dateOfLastChange, idOfChange, */ privilage, password, next;

	if (file.is_open())	// The file is successfully opened
	{
		while (std::getline(file, id, ','))
		{
			std::getline(file, userName, ',');
			std::getline(file, firstName, ',');
			std::getline(file, lastName, ',');
			std::getline(file, email, ',');

			/*std::getline(file, dateofcreation, ',');
			std::getline(file, idofcreator, ',');
			std::getline(file, dateoflastchange, ',');
			std::getline(file, idofchange, ',');*/

			std::getline(file, privilage, ',');
			std::getline(file, password, ',');
			std::getline(file, next, '\n');

			// std::cout << id << std::endl;
			
			addToUsers(stoi(id), userName, firstName, lastName, email, stoi(privilage), password);
		}

		file.close();
	}

	else	// there is a problem with the file
	{
		std::cout << "Enable to open the file!" << std::endl;
	}
}

void pm::dal::UserStore::addToUsers(int id, std::string username, std::string firstName, std::string lastName, std::string email, bool privilage, std::string password)
{
	pm::types::User user;

	user.id = id;
	user.username = username;
	user.firstName = firstName;
	user.lastName = lastName;
	user.email = email;
	user.privilage = privilage;
	user.passwordHash = password;

	users.push_back(user);
}

void pm::dal::UserStore::displayUsers()
{
	for (unsigned i = 0; i < users.size(); i++)
	{
		std::cout << users[i].username << std::endl;
	}
}

// za userManager.cpp

bool pm::bll::UserManager::loginUser(std::string username, std::string password)
{
	// getByUsername will be bool and after that we'll check the password too, after which we'll find out if the user exists
	
	bool flag1 = m_userStore.getByUsername(username);

	/*
	std::string passHash = hashString(password);

	if (user.passwordHash != passHash)
	{
		throw std::logic_error("Invalid password!");
	}
	*/

	if (flag1 /* && flag2 */)
	{
		return true;
	}

	return false;
}