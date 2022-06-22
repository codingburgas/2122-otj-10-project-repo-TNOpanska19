#pragma once
#include <time.h>
#include "pch.h"

namespace pm::types
{
	struct User
	{
		size_t id;
		std::string userName;
		std::string firstName;
		std::string lastName;
		std::string email;
		/*
		time_t dateOfCreation;
		size_t idOfCreator;
		time_t dateOfLastChange;
		size_t idOfChange;
		*/
		bool privilage;
		std::string passwordHash;
	};
}