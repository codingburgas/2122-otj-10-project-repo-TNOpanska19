/*****************************************************************//**
 * \file   userStore.h
 * \brief  Header file for user storing
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "../pm.types/user.h"

 /// <summary>
 /// Namespace for data access layer
 /// </summary>
namespace pm::dal
{
	/// <summary>
	/// Structure for user storing
	/// </summary>
	struct UserStore
	{
		void getData();

		void addToUsers(int id, std::string username, std::string firstName, std::string lastName, std::string email, time_t dateOfCreation, int idOdCreator, time_t dateOfLastChange, int idOfChange, bool privilege, std::string password);

		void createNewUser(pm::types::User& user);

		int generateNewId();

		bool checkExistanceById(int userId);

		std::vector<pm::types::User> getAllUsers();

		void update(std::vector<pm::types::User> users);

		void remove(int delId);
	};
}