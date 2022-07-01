#pragma once

#include "pch.h"
#include "../pm.types/user.h"

namespace menu::usersMenu
{
	void usersManagementView(pm::types::User activeUser);

	void createUserMenu(pm::types::User activeUser);
}