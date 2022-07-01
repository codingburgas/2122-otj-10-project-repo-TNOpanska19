#pragma once

#include "pch.h"
#include "../pm.types/user.h"

namespace menu::projectsMenu
{
	void projectsManagementView(pm::types::User activeUser);

	void createProjectMenu(pm::types::User activeUser);
}