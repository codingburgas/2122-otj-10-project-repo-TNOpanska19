#pragma once
#include <string>
#include <vector>
#include "pch.h"
#include "../pm.tools/md5.h"
#include "../pm.types/user.h"
#include "../pm.dal/userStore.h"

namespace pm::bll
{
	struct UserManager
	{
		//pm::dal::UserStore m_userStore;

		std::string hashString(std::string str);

		bool loginUser(std::string username, std::string password);

		std::vector<pm::types::User> getRegisteredUsers();

		void displayUsers();

		/*
		void registerUser(std::string firstName, std::string lastName, uint8_t age, std::string email, std::string password);

		pm::types::User loginUser(std::string username, std::string password);

		void seedDatabase();

		void removeUser(size_t id);

		void updateUser(pm::types::User);
		*/
	};
}