#include "pch.h"
#include "userManager.h"

std::string pm::bll::UserManager::hashString(std::string str)
{
	
}

void pm::bll::UserManager::registerUser(std::string firstName, std::string lastName, uint8_t age, std::string email, std::string password)
{
	pm::types::User user;

	user.firstName = firstName;
	user.lastName = lastName;
	user.email = email;
	user.age = age;
	user.passwordHash = hashString(password);

	m_userStore.create(user);
}

pm::types::User pm::bll::UserManager::loginUser(std::string username, std::string password)
{
	auto user = m_userStore.getByEmail(username);

	std::string passHash = hashString(password);

	if (user.passwordHash != passHash)
	{
		throw std::logic_error("Invalid password!");
	}

	return user;
}

std::vector<pm::types::User> pm::bll::UserManager::getRegisteredUsers()
{
	auto users = m_userStore.getAll();
	return users;
}

void pm::bll::UserManager::seedDatabase()
{
	registerUser("fn1", "ln1", 16, "u1@lab.com", "1231");
	registerUser("fn2", "ln2", 17, "u2@lab.com", "1232");
	registerUser("fn3", "ln3", 18, "u3@lab.com", "1233");
	registerUser("fn4", "ln4", 19, "u4@lab.com", "1234");
}

void pm::bll::UserManager::removeUser(size_t id)
{
	m_userStore.remove(id);
}

void pm::bll::UserManager::updateUser(pm::types::User user)
{
	m_userStore.update(user);
}