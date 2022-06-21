#include <fstream>
#include "pch.h"
#include "UserStore.h"

std::vector<pm::types::User> users;

// make get users functinality that will work with files

/*
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
*/

// finish with previous example

void pm::dal::UserStore::getData()	// Starts reading the Records.txt file so it can input information into it
{
	std::ifstream file("../Users.txt", std::fstream::in);

	std::string id, firstName, lastName, email, age, password, next;

	if (file.is_open())	// The file is successfully opened
	{
		while (std::getline(file, id, ','))
		{
			std::getline(file, firstName, ',');
			std::getline(file, lastName, ',');
			std::getline(file, email, ',');
			std::getline(file, age, ',');
			std::getline(file, password, ',');
			std::getline(file, next, '\n');

			addToUsers(stoi(id), firstName, lastName, email, stoi(age), password);
		}

		file.close();
	}

	else	// There is a problem with the file
	{
		std::cout << "Enable to open the file!" << std::endl;
	}
}

void pm::dal::UserStore::addToUsers(int id, std::string firstName, std::string lastName, std::string email, int age, std::string password)
{
	pm::types::User user;

	user.id = id;
	user.firstName = firstName;
	user.lastName = lastName;
	user.email = email;
	user.age = age;
	user.passwordHash = password;

	users.push_back(user);
}