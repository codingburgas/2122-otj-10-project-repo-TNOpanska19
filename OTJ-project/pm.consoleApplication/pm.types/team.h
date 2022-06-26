#pragma once

#include "pch.h"

namespace pm::types
{
	struct Team
	{
		int id;
		std::string title;
		time_t dateOfCreation;
		int idOfCreator;
		time_t dateOfLastChange;
		int idOfChange;
		std::vector<std::string> members;
	};
}