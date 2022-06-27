#pragma once

#include "pch.h"
#include "../pm.types/team.h"

namespace pm::dal
{
	struct TeamStore
	{
		void getData();

		void addToTeams(int id, std::string title, time_t dateOfCreation, int idOfCreator, time_t dateOfLastChange, int idOfChange, std::vector<std::string> members);

		void createNewTeam(pm::types::Team& team);

		int generateNewId();

		std::vector<pm::types::Team> getAllTeams();

		void update(std::vector<pm::types::Team> teams);

		void remove(int delId);

		void assignUsers(int id, int userId);
	};
}