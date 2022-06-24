#include "pch.h"
#include <conio.h>
#include "../pm.consoleApplication/mainMenu.h"
#include "userManager.h"

pm::dal::UserStore uStore;
pm::bll::UserManager userManager;
std::vector<pm::types::User> userList;

std::string pm::bll::UserManager::hashString(std::string password)
{
	MD5 md5;
	return md5(password);
}

bool pm::bll::UserManager::loginUser(std::string username, std::string password)
{
	uStore.getData();
	userList = userManager.getRegisteredUsers();

	std::string passHash = pm::bll::UserManager::hashString(password);

	for (int i = 0; i < userList.size(); i++)
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
   return uStore.getAll();
}

void pm::bll::UserManager::displayUsers()
{
	system("CLS");
	uStore.getData();
	userList = userManager.getRegisteredUsers();

	std::cout << "  =============================================" << std::endl;
	std::cout << "                    USER LIST                    " << std::endl;
	std::cout << "  =============================================" << std::endl;
	std::cout << "   id, username, first name, last name," << std::endl << "           email, privilage" << std::endl << std::endl;

	for (unsigned i = 0; i < userList.size(); i++)
	{
		std::cout << "  " << userList[i].id << ", " << userList[i].username << ", " << userList[i].firstName << ", " << userList[i].lastName << ", " 
			<< userList[i].email << ", " << userList[i].privilage << std::endl << std::endl;
	}

	std::cout << "  =============================================" << std::endl << std::endl; 
	std::cout << "  Press any key to go back to menu...";
	_getch();
	mainMenu::usersManagementView();
}

pm::types::User pm::bll::UserManager::getActiveUser(std::string username)
{
	uStore.getData();
	userList = userManager.getRegisteredUsers();

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
	uStore.remove(id);
	std::cout << std::endl << std::endl;

	std::cout << "  Press any key to go back to menu...";
	_getch();
	mainMenu::usersManagementView();
}

void pm::bll::UserManager::createUser(int id, std::string username, std::string firstName, std::string lastName, std::string email, bool privilage, std::string password)
{
	pm::types::User newUser;

	newUser.id = uStore.generateNewId();
	newUser.username = username;
	newUser.firstName = firstName;
	newUser.lastName = lastName;
	newUser.email = email;
	newUser.privilage = privilage;
	newUser.passwordHash = pm::bll::UserManager::hashString(password);

	uStore.createNewUser(newUser);

	mainMenu::usersManagementView();
}