/*****************************************************************//**
 * \file   team.h
 * \brief  Header file for team type
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
	/// Structure for team type
	/// </summary>
	struct Team
	{
		int id{};
		std::string title;
		time_t dateOfCreation{};
		int idOfCreator{};
		time_t dateOfLastChange{};
		int idOfChange{};
		std::vector<int> members;
	};
}