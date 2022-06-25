#include "pch.h"
#include <conio.h>
#include "../pm.consoleApplication/mainMenu.h"
#include "userManager.h"

pm::bll::UserManager mUserManager;
std::vector<pm::types::User> userList;

std::string pm::bll::UserManager::hashString(std::string password)
{
	MD5 md5;
	return md5(password);
}

bool pm::bll::UserManager::loginUser(std::string username, std::string password)
{
	mUserStore.getData();
	userList = mUserManager.getRegisteredUsers();

	std::string passHash = pm::bll::UserManager::hashString(password);

	for (unsigned i = 0; i < userList.size(); i++)
	{
		if (userList[i].username == username)
		{
			if (userList[i].passwordHash == passHash)
			{
				return true;
			}
		}
	}

	return false;
}

std::vector<pm::types::User> pm::bll::UserManager::getRegisteredUsers()
{
   return mUserStore.getAll();
}

void pm::bll::UserManager::displayUsers()
{
	system("CLS");
	mUserStore.getData();
	userList = mUserManager.getRegisteredUsers();

	std::cout << "  ========================================================" << std::endl;
	std::cout << "                         USER LIST                    " << std::endl;
	std::cout << "  ========================================================" << std::endl << std::endl;
	std::cout << "   id, username, first name, last name, email, privilege" << std::endl << std::endl << std::endl;

	for (unsigned i = 0; i < userList.size(); i++)
	{
		std::cout << "   " << userList[i].id << ", " << userList[i].username << ", " << userList[i].firstName << ", " << userList[i].lastName << ", " 
			<< userList[i].email << ", " << userList[i].privilege << std::endl << std::endl;
	}

	std::cout << "  ========================================================" << std::endl << std::endl; 
	std::cout << "  Press any key to go back to menu...";
	_getch();
	mainMenu::usersManagementView();
}

pm::types::User pm::bll::UserManager::getActiveUser(std::string username)
{
	mUserStore.getData();
	userList = mUserManager.getRegisteredUsers();

	for (unsigned i = 0; i < userList.size(); i++)
	{
		if (userList[i].username == username)
		{
			return userList[i];
		}
	}
}

void pm::bll::UserManager::removeUser()
{
	system("CLS");
	int id;

	std::cout << "Delete user with Id: "; std::cin >> id;
	mUserStore.remove(id);
	std::cout << std::endl << std::endl;

	std::cout << "  Press any key to go back to menu...";
	_getch();
	mainMenu::usersManagementView();
}

void pm::bll::UserManager::createUser(int id, std::string username, std::string firstName, std::string lastName, std::string email, bool privilege, std::string password)
{
	pm::types::User newUser;

	newUser.id = mUserStore.generateNewId();
	newUser.username = username;
	newUser.firstName = firstName;
	newUser.lastName = lastName;
	newUser.email = email;
	newUser.privilege = privilege;
	newUser.passwordHash = pm::bll::UserManager::hashString(password);

	mUserStore.createNewUser(newUser);

	mainMenu::usersManagementView();
}

void pm::bll::UserManager::updateUser()
{
	system("CLS");

	int id;
	bool flag = false;
	std::string password;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               UPDATE USER            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;
	std::cout << "     Update user with id: "; std::cin >> id;
	std::cout << std::endl;

	userList.clear();
	userList = mUserManager.getRegisteredUsers();

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

			flag = true;
			break;
		}
	}

	if (flag)
	{
		mUserStore.update(userList);
	}

	else
	{
		std::cout << "     User does not exist!" << std::endl;
	}



	std::cout << std::endl << "  ======================================" << std::endl;

	std::cout << std::endl << "  Press any key to go back to menu...";
	_getch();
	mainMenu::usersManagementView();
}
