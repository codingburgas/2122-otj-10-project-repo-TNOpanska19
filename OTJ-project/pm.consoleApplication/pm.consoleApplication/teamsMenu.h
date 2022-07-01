#pragma once

#include "pch.h"
#include "../pm.types/user.h"

namespace menu::teamsMenu
{
	void teamsManagementView(pm::types::User activeUser);

	void createTeamMenu(pm::types::User activeUser);
}