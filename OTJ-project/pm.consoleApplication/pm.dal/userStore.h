#pragma once

#include "../pm.types/user.h"

namespace pm::dal
{
	struct UserStore
	{
		int generateNewId();

		void createNewUser(pm::types::User& user);

		void remove(int delId);

		void update(std::vector<pm::types::User> users);

		pm::types::User getById(size_t id);

		bool getByUsername(std::string username);

		std::vector<pm::types::User> getAll();

		void getData();

		void addToUsers(int id, std::string username, std::string firstName, std::string lastName, std::string email, time_t dateOfCreation, int idOdCreator, time_t dateOfLastChange, int idOfChange, bool privilege, std::string password);
	};
}