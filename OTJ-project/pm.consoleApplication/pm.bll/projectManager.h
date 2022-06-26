#pragma once

#include "pch.h"
#include "userManager.h"
#include "../pm.types/project.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/teamStore.h"

namespace pm::bll
{
	struct ProjectManager
	{
		void createProject(std::string title, std::string description, pm::types::User activeUser);

		void removeProject(pm::types::User activeUser);

		void displayProjects(pm::types::User activeUser);

		//std::vector<pm::types::Project> getRegisteredProjects();

		/*
		pm::dal::UserStore mUserStore;

		void createTeam(std::string title, pm::types::User activeUser);

		void updateTeam(pm::types::User activeUser);


		std::vector<pm::types::Team> getRegisteredTeams();

		bool getTeamById(int id);

		void assignUsersToTeam(pm::types::User activeUser);

		void displayTeams(pm::types::User activeUser);
		*/
	};
}