#pragma once
#include <time.h>
#include <string>
#include "pch.h"

namespace pm::types
{
	struct User
	{
		int id;
		std::string username;
		std::string firstName;
		std::string lastName;
		std::string email;
		/*
		time_t dateOfCreation;
		size_t idOfCreator;
		time_t dateOfLastChange;
		size_t idOfChange;
		*/
		bool privilege;
		std::string passwordHash;
	};
}