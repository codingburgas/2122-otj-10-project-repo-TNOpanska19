#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../pm.types/User.h"

namespace pm::dal
{
	struct UserStore
	{
		int generateNewId();

		void createNewUser(pm::types::User& user);

		void remove(int delId);

		void update(std::vector<pm::types::User> users);

		pm::types::User getById(size_t id);

		// bool getByUsername(std::string username, int password);

		std::vector<pm::types::User> getAll();

		void getData();

		void addToUsers(int id, std::string username, std::string firstName, std::string lastName, std::string email, bool privilage, std::string password);
	};
}