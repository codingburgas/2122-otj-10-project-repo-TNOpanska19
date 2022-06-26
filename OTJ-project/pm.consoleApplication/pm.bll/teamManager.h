#pragma once
#include <string>
#include <vector>
#include "pch.h"
#include "userManager.h"
#include "../pm.types/team.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/teamStore.h"

namespace pm::bll
{
	struct TeamManager
	{
		pm::dal::UserStore mUserStore;
		
		void createTeam(std::string title, pm::types::User activeUser);
		

		void displayTeams();

		std::vector<pm::types::Team> getRegisteredTeams();

		/*
		void displayTeams();

		void removeTeam();

		
		void updateTeam();
		*/
	};
}