#pragma once

#include "../pm.types/user.h"

namespace pm::dal
{
	struct UserStore
	{
		void getData();

		void addToUsers(int id, std::string username, std::string firstName, std::string lastName, std::string email, time_t dateOfCreation, int idOdCreator, time_t dateOfLastChange, int idOfChange, bool privilege, std::string password);

		void createNewUser(pm::types::User& user);

		int generateNewId();

		pm::types::User getById(size_t id);

		bool getByUsername(std::string username);

		std::vector<pm::types::User> getAllUsers();

		void update(std::vector<pm::types::User> users);

		void remove(int delId);
	};
}