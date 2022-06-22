#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "mainMenu.h"
//#include "../pm.types/User.h"
//#include "../pm.bll/userManager.h"

std::vector<pm::types::User> users;

void mainMenu::loginMenu()
{
    pm::dal::UserStore u_store;
	pm::bll::UserManager u_manager;

    u_store.getData();
	// u.displayUsers();

	std::string username, password;

    std::cout << "  ==============================" << std::endl;
    std::cout << "             Log In             " << std::endl;
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
	}

	else
	{
		system("CLS");
		std::cout << " User does not exist. Please try to log in again." << std::endl << std::endl;
		mainMenu::loginMenu();
	}
}


void mainMenu::registerMenu()
{
    std::string firstName, lastName, email, password;
    int age;

    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::cout << "==============================" << std::endl;
    std::cout << "           REGISTER           " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "                              " << std::endl;
    std::cout << "             Enter           " << std::endl;
    std::cout << "     First Name: "; std::getline(std::cin, firstName);
    std::cout << "     Last Name: "; std::getline(std::cin, lastName);
    std::cout << "     Age: "; std::cin >> age;
    std::cout << "     Email: "; std::cin >> email;
    std::cout << "     Password: "; std::cin >> password;
    std::cout << "                              " << std::endl;
    std::cout << "==============================" << std::endl;

    // pm::bll::UserManager::registerUser(firstName, lastName, age, email, password);
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