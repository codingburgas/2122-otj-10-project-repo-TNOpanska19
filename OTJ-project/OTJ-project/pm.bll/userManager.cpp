/*****************************************************************//**
 * \file   userManager.cpp
 * \brief  Source file for user management
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "../pm.consoleApplication/mainMenu.h"
#include "../pm.consoleApplication/usersMenu.h"
#include "userManager.h"

/// <summary>
/// Object of usersMenu structure
/// </summary>
menu::usersMenu uMenuManager;

/// <summary>
/// Object of UserManager structure
/// </summary>
pm::bll::UserManager uUserManager;
/// <summary>
/// Vector of type User. Used to store users.
/// </summary>
std::vector<pm::types::User> userList;

/// <summary>
/// Hashes a given string
/// </summary>
/// <param name="password">A string argument to be hashed</param>
/// <returns>Hashed string</returns>
std::string pm::bll::UserManager::hashString(std::string password)
{
	MD5 md5;
	return md5(password);
}

/// <summary>
/// Checks if the given username and password belong to one of the existing users
/// </summary>
/// <param name="username">A string argument of entered username</param>
/// <param name="password">A string argument of entered password</param>
/// <returns>True or false A string argument the user exists and the entered information is correct</returns>
bool pm::bll::UserManager::loginUser(std::string username, std::string password)
{
	userList = uUserManager.getRegisteredUsers();

	std::string passHash = pm::bll::UserManager::hashString(password);	// Hashes entered password to compare to the hashed password from the file

	for (unsigned i = 0; i < userList.size(); i++)
		if (userList[i].username == username && userList[i].passwordHash == passHash)
			return true;

	return false;
}

/// <summary>
/// Returns the current logged in user
/// </summary>
/// <param name="username">A string argument username of current logged in user</param>
/// <returns>Current logged in user</returns>
pm::types::User pm::bll::UserManager::getActiveUser(std::string username)
{
	userList = uUserManager.getRegisteredUsers();

	for (unsigned i = 0; i < userList.size(); i++)
		if (userList[i].username == username)
			return userList[i];
}

/// <summary>
/// Used to create a new user
/// </summary>
/// <param name="username">A string argument username of new user</param>
/// <param name="firstName">A string argument first name of new user</param>
/// <param name="lastName">A string argument last name of new user</param>
/// <param name="email">A string argument email of new user</param>
/// <param name="privilege">A bool argument that shows privilege of new user. 0 - normal user and 1 - admin</param>
/// <param name="password">A string argument password of new user</param>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::UserManager::createUser(std::string username, std::string firstName, std::string lastName, std::string email, bool privilege, std::string password, pm::types::User activeUser)
{
	pm::types::User newUser;

	newUser.id = mUserStore.generateNewId();	// Generates new Id for new user
	newUser.username = username;
	newUser.firstName = firstName;
	newUser.lastName = lastName;
	newUser.email = email;
	newUser.dateOfCreation = time(NULL);	// Current time
	newUser.idOfCreator = activeUser.id;
	newUser.dateOfLastChange = time(NULL);	// Current time
	newUser.idOfChange = activeUser.id;
	newUser.privilege = privilege;
	newUser.passwordHash = password;

	mUserStore.createNewUser(newUser);
	uMenuManager.usersManagementView(activeUser);
}

/// <summary>
/// Checks whether the entered email fits criteria
/// </summary>
/// <param name="email">A string argument email for new user creation</param>
/// <returns>True or false depending on whether email fits criteria</returns>
bool pm::bll::UserManager::checkEmail(std::string email)
{
	if (email.find('@') != std::string::npos)
		return false;

	return true;
}

/// <summary>
/// Used for updating user data with given ID
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::UserManager::updateUser(pm::types::User activeUser)
{
	system("CLS");

	int id;
	bool flag = false;
	std::string password;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               UPDATE USER            " << std::endl;
	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "     Update user with id: ";

	while (!(std::cin >> id))	// Checks whether entered ID is a number
	{
		system("CLS");

		std::cout << " ID needs to be a number!" << std::endl << std::endl;
		std::cout << "  ======================================" << std::endl;
		std::cout << "               UPDATE USER            " << std::endl;
		std::cout << "  ======================================" << std::endl << std::endl;
		std::cout << "     Update user with id: ";

		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	std::cout << std::endl;

	userList = uUserManager.getRegisteredUsers();

	// Goes through all users to see whether entered one exists
	for (unsigned i = 0; i < userList.size(); i++)
	{
		if (userList[i].id == id)
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "                                " << std::endl;
			std::cout << "     Update username: "; std::getline(std::cin, userList[i].username); std::cout << std::endl;
			std::cout << "     Update first name: "; std::getline(std::cin, userList[i].firstName); std::cout << std::endl;
			std::cout << "     Update last name: "; std::getline(std::cin, userList[i].lastName); std::cout << std::endl;
			std::cout << "     Update email: "; std::getline(std::cin, userList[i].email); std::cout << std::endl;
			std::cout << "     Update privilege: "; std::cin >> userList[i].privilege; std::cout << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "     Update password: ";  std::getline(std::cin, password);
			userList[i].passwordHash = hashString(password);
			userList[i].dateOfLastChange = time(NULL);	// Change time of last change to current time
			userList[i].idOfChange = activeUser.id;		// Change id of person who made the last change to the currently logged-in user's

			flag = true;
			break;
		}
	}

	if (flag)	// User with given ID exists
		mUserStore.update(userList);
		
	else		// User with given ID does not exist
		std::cout << "     User with ID " << id << " does not exist!" << std::endl;

	std::cout << std::endl << "  ======================================" << std::endl;
	std::cout << std::endl << "  Press any key to go back to menu...";
	(void)_getch();
	uMenuManager.usersManagementView(activeUser);
}

/// <summary>
/// Used to remove user with given ID
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::UserManager::removeUser(pm::types::User activeUser)
{
	system("CLS");
	int id;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               REMOVE USER            " << std::endl;
	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "     Remove user with Id: ";

	while (!(std::cin >> id))	// Checks whether entered ID is a number
	{
		system("CLS");

		std::cout << " ID needs to be a number!" << std::endl << std::endl;
		std::cout << "  ======================================" << std::endl;
		std::cout << "               REMOVE USER            " << std::endl;
		std::cout << "  ======================================" << std::endl << std::endl;
		std::cout << "     Remove user with Id: ";

		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	mUserStore.remove(id);
	std::cout << std::endl << std::endl;

	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	(void)_getch();
	uMenuManager.usersManagementView(activeUser);
}

/// <summary>
/// Used to get all registered users
/// </summary>
/// <returns>Vector of all registered users</returns>
std::vector<pm::types::User> pm::bll::UserManager::getRegisteredUsers()
{
	mUserStore.getData();
	userList.clear();
	return mUserStore.getAllUsers();
}

/// <summary>
/// Used to display all registered users
/// </summary>
/// <param name="activeUser">Logged-in user</param>
void pm::bll::UserManager::displayUsers(pm::types::User activeUser)
{
	system("CLS");
	userList = uUserManager.getRegisteredUsers();

	char buffer[80];
	struct tm time;
	const time_t* rawTime;

	std::cout << "  ========================================================" << std::endl;
	std::cout << "                         USER LIST                    " << std::endl;
	std::cout << "  ========================================================" << std::endl << std::endl;

	for (unsigned i = 0; i < userList.size(); i++)
	{
		std::cout << "   Id: " << userList[i].id << std::endl;
		std::cout << "   Username: " << userList[i].username << std::endl;
		std::cout << "   First name: " << userList[i].firstName << std::endl;
		std::cout << "   Last name: " << userList[i].lastName << std::endl;

		// Transform time_t to a readable format
		rawTime = &userList[i].dateOfCreation;
		localtime_s(&time, rawTime);
		strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
		std::cout << "   Created on: " << buffer << std::endl;
		std::cout << "   Id of creator: " << userList[i].idOfCreator << std::endl;
		
		// Transform time_t to a readable format
		rawTime = &userList[i].dateOfLastChange;
		localtime_s(&time, rawTime);
		strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
		std::cout << "   Last change on: " << buffer << std::endl;
		std::cout << "   Id of user who made change: " << userList[i].idOfChange << std::endl;
		std::cout << "   Email: " << userList[i].email << std::endl;
		std::cout << "   Privilege: " << userList[i].privilege << std::endl << std::endl;
	}

	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	(void)_getch();
	uMenuManager.usersManagementView(activeUser);
}