#pragma once

#include "pch.h"
#include "../pm.types/project.h"

namespace pm::dal
{
	struct ProjectStore
	{
		void getData();

		void addToProjects(std::string title, std::string description, time_t dateOfCreation, int idOfCreator, time_t dateOfLastChange, int idOfChange, std::vector<std::string> members);

		void createNewProject(pm::types::Project& project);
		/*
		void getData();


		int generateNewId();

		std::vector<pm::types::Team> getAll();

		void update(std::vector<pm::types::Team> teams);

		void remove(int delId);

		void assignUsers(int id, std::string user);
		*/
	};
}