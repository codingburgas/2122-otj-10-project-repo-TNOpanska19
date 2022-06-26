#include "pch.h"
#include <conio.h>
#include "../pm.consoleApplication/mainMenu.h"
#include "../pm.consoleApplication/usersMenu.h"
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

void pm::bll::UserManager::displayUsers(pm::types::User activeUser)
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
	userMenu::usersManagementView(activeUser);
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

void pm::bll::UserManager::removeUser(pm::types::User activeUser)
{
	system("CLS");
	int id;

	std::cout << "  ======================================" << std::endl;
	std::cout << "               REMOVE USER            " << std::endl;
	std::cout << "  ======================================" << std::endl;
	std::cout << "                                " << std::endl;

	std::cout << "     Remove user with Id: "; std::cin >> id;
	mUserStore.remove(id);
	std::cout << std::endl << std::endl; 
	
	std::cout << "  ======================================" << std::endl << std::endl;
	std::cout << "  Press any key to go back to menu...";
	_getch();
	userMenu::usersManagementView(activeUser);
}

void pm::bll::UserManager::createUser(std::string username, std::string firstName, std::string lastName, std::string email, bool privilege, std::string password, pm::types::User activeUser)
{
	pm::types::User newUser;

	std::cout << password << std::endl;

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

	userMenu::usersManagementView(activeUser);
}

void pm::bll::UserManager::updateUser(pm::types::User activeUser)
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

			userList[i].dateOfLastChange = time(NULL);
			userList[i].idOfChange = activeUser.id;

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
		std::cout << "     User with ID " << id << " does not exist!" << std::endl;
	}

	std::cout << std::endl << "  ======================================" << std::endl;
	std::cout << std::endl << "  Press any key to go back to menu...";
	_getch();
	userMenu::usersManagementView(activeUser);
}
