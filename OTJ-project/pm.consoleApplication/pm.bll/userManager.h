#pragma once

#include "pch.h"
#include "../pm.tools/md5.h"
#include "../pm.types/user.h"
#include "../pm.dal/userStore.h"

namespace pm::bll
{
	struct UserManager
	{
		pm::dal::UserStore mUserStore;

		std::string hashString(std::string str);

		bool loginUser(std::string username, std::string password);

		pm::types::User getActiveUser(std::string username);

		void createUser(std::string username, std::string firstName, std::string lastName, std::string email, bool privilege, std::string password, pm::types::User acttiveUser);

		void updateUser(pm::types::User activeUser);

		void removeUser(pm::types::User activeUser);

		std::vector<pm::types::User> getRegisteredUsers();

		void displayUsers(pm::types::User activeUser);
	};
}