#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../pm.types/User.h"

namespace pm::dal
{
	struct UserStore
	{
		/*
		void create(pm::types::User& user);

		pm::types::User getById(size_t id);

		pm::types::User getByEmail(std::string email);

		std::vector<pm::types::User> getAll();

		void remove(size_t id);

		void update(pm::types::User user);
		*/

		void getData();

		void addToUsers(int id, std::string userName, std::string firstName, std::string lastName, std::string email, bool privilage, std::string password);
	};
}