/*****************************************************************//**
 * \file   user.h
 * \brief  Header file for user type
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#pragma once

#include "pch.h"

/// <summary>
/// Namespace for types
/// </summary>
namespace pm::types
{
	/// <summary>
	/// Structure for user type
	/// </summary>
	struct User
	{
		int id;
		std::string username;
		std::string firstName;
		std::string lastName;
		std::string email;
		time_t dateOfCreation;
		size_t idOfCreator;
		time_t dateOfLastChange;
		size_t idOfChange;
		bool privilege;
		std::string passwordHash;
	};
}