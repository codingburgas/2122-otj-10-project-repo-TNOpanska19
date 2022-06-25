#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../pm.types/team.h"

namespace pm::dal
{
	struct TeamStore
	{
		void createNewTeam(pm::types::Team& team);

		/*
		int generateNewId();


		void remove(int delId);

		void update(std::vector<pm::types::User> users);

		pm::types::User getById(size_t id);

		// bool getByUsername(std::string username, int password);

		std::vector<pm::types::User> getAll();

		void getData();

		void addToUsers(int id, std::string username, std::string firstName, std::string lastName, std::string email, bool privilege, std::string password);
		*/	
	};
}