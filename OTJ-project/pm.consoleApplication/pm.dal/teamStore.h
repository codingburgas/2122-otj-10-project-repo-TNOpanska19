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

		void getData();

		void addToTeams(int id, std::string title, /*std::string dateOfCreation, int idOfCreator, std::string dateOfLastChange, int idOfChange, */std::vector<std::string> members);

		std::vector<pm::types::Team> getAll();

		int generateNewId();

		void update(std::vector<pm::types::Team> teams);

		void remove(int delId);
	};
}