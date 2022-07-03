/*****************************************************************//**
 * \file   project.h
 * \brief  Header file for project type
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
	/// Structure for project type
	/// </summary>
	struct Project
	{
		std::string title;
		std::string description;
		time_t dateOfCreation;
		int idOfCreator;
		time_t dateOfLastChange;
		int idOfChange;
		std::vector<int> teams;
	};
}