#pragma once

#include "pch.h"

namespace pm::types
{
	struct Project
	{
		std::string title;
		std::string description;
		time_t dateOfCreation;
		int idOfCreator;
		time_t dateOfLastChange;
		int idOfChange;
		std::vector<std::string> teams;
	};
}