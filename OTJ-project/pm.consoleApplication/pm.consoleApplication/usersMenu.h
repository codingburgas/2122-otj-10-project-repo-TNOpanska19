#pragma once

#include "pch.h"
#include "../pm.types/user.h"

namespace usersMenu
{
	void usersManagementView(pm::types::User activeUser);

	void createUserMenu(pm::types::User activeUser);
}