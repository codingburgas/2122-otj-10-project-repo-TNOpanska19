#include <fstream>
#include "pch.h"
#include "UserStore.h"

std::vector<pm::types::User> users;

// make get users functinality that will work with files

size_t generateNewId()
{
	size_t maxId = 0;

	for (auto user : users)
	{
		if (user.id > maxId)
		{
			maxId = user.id;
		}
	}
}

void pm::dal::UserStore::create(pm::types::User& user)
{
	auto it = std::find_if(users.begin(), users.end(),
		[&](pm::types::User u) {return u.email == user.email;  });

	if (it != users.end())
	{
		throw std::range_error("The user " + std::string(user.email) + "already exists!");
	}

	user.id = generateNewId();

	users.push_back(user);

	// add new user to file
}

pm::types::User pm::dal::UserStore::getById(size_t id)
{
	auto it = std::find_if(users.begin(), users.end(),
		[&](pm::types::User u) {return u.id == id; });

	if (it != users.end())
	{
		throw std::range_error(std::string("User with id ") + std::to_string(id) + std::string(" was not found!"));
	}

	return *it;
}

pm::types::User pm::dal::UserStore::getByEmail(std::string email)
{
	auto it = std::find_if(users.begin(), users.end(),
		[=](pm::types::User u) {return u.email == email; });

	if (it == users.end())
	{
		throw std::range_error("User not found!");
	}

	return *it;
}

std::vector<pm::types::User> pm::dal::UserStore::getAll()
{
	return std::vector<pm::types::User>(users);
}

void pm::dal::UserStore::remove(size_t id)
{
	for (auto it = users.begin(); it != users.end(); it++)
	{
		if ((*it).id == id)
		{
			users.erase(it);
			return;
		}
	}

	throw std::range_error(std::string("Users with id ") + std::to_string(id) + std::string(" was not found!"));
}

void pm::dal::UserStore::update(pm::types::User user)
{
	std::vector<pm::types::User>::iterator it;
	it = std::find_if(users.begin(), users.end(),
		[&](pm::types::User u) {return u.id == user.id; });

	if (it == users.end())
	{
		throw std::range_error("User with id " + std::to_string(user.id) + " was not found!");
	}

	auto& u = *it;
	u.firstName = user.firstName;
	u.lastName = user.lastName;
	u.email = user.email;
	u.age = user.age;
}

// finish with previous example

void pm::dal::UserStore::openFile()	// Starts reading the Records.txt file so it can input information into it
{
	std::string line;
	std::ifstream file("../Users.txt");

	if (file.is_open())	// The file is successfully opened
	{
		int i = 0;

		while (getline(file, line))
		{
			users.
		}
	}

	else	// There is a problem with the file
	{
		cout << "Enable to open the file!" << endl;
	}
}