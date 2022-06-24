#include "pch.h"
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