#pragma once

#include "pch.h"
#include "../pm.types/user.h"

namespace userMenu
{
	void usersManagementView(pm::types::User activeUser);

	void createUserMenu(pm::types::User activeUser);
}