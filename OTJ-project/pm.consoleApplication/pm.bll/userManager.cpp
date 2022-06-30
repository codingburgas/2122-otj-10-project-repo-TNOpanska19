#include "pch.h"
#include "../pm.consoleApplication/mainMenu.h"
#include "../pm.consoleApplication/usersMenu.h"
#include "userManager.h"

pm::bll::UserManager uUserManager;
std::vector<pm::types::User> userList;

std::string pm::bll::UserManager::hashString(std::string password)
{
	MD5 md5;
	return md5(password);
}

bool pm::bll::UserManager::loginUser(std::string username, std::string password)
{
	userList = uUserManager.getRegisteredUsers();

	std::string passHash = pm::bll::UserManager::hashString(password);

	for (unsigned i = 0; i < userList.size(); i++)
		if (userList[i].username == username && userList[i].passwordHash == passHash)
			return true;

	return false;
}

pm::types::User pm::bll::UserManager::getActiveUser(std::string username)
{
	userList = uUserManager.getRegisteredUsers();

	for (unsigned i = 0; i < userList.size(); i++)
		if (userList[i].username == username)
			return userList[i];
}

void pm::bll::UserManager::createUser(std::string username, std::string firstName, std::string lastName, std::string email, bool privilege, std::string password, pm::types::User activeUser)
{
	pm::types::User newUser;

	newUser.id = mUserStore.generateNewId();
	newUser.username = username;
	newUser.firstName = firstName;
	newUser.lastName = lastName;
	newUser.email = email;
	newUser.dateOfCreation = time(NULL);
	newUser.idOfCreator = activeUser.id;
	newUser.dateOfLastChange = time(NULL);
	newUser.idOfChange = activeUser.id;
	newUser.privilege = privilege;
	newUser.passwordHash = password;

	mUserStore.createNewUser(newUser);
	usersMenu::usersManagementView(activeUser);
}

bool pm::bll::UserManager::checkEmail(std::string email)
{
	if (email.find('@') != std::string::npos)
		return false;

	return true;
}

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

	while (!(std::cin >> id))
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
			userList[i].dateOfLastChange = time(NULL);
			userList[i].idOfChange = activeUser.id;

			flag = true;
			break;
		}
	}

	if (flag)
		mUserStore.update(userList);

	else
		std::cout << "     User with ID " << id << " does not exist!" << std::endl;

	std::cout << std::endl << "  ======================================" << std::endl;
	std::cout << std::endl << "  Press any key to go back to menu...";
	_getch();
	usersMenu::usersManagementView(activeUser);
}

void pm::bll::UserManager::removeUser(pm::types::User activeUser)
{
	system("CLS");
	int id;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               REMOVE USER            " << std::endl;
	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "     Remove user with Id: ";

	while (!(std::cin >> id))
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
	_getch();
	usersMenu::usersManagementView(activeUser);
}

std::vector<pm::types::User> pm::bll::UserManager::getRegisteredUsers()
{
	mUserStore.getData();
	userList.clear();
	return mUserStore.getAllUsers();
}

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

		rawTime = &userList[i].dateOfCreation;
		localtime_s(&time, rawTime);
		strftime(buffer, 80, "%d/%m/%y | %I:%M %p", &time);
		std::cout << "   Created on: " << buffer << std::endl;
		std::cout << "   Id of creator: " << userList[i].idOfCreator << std::endl;

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
	_getch();
	usersMenu::usersManagementView(activeUser);
}