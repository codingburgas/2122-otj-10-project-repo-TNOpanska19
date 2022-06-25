#include "pch.h"
#include <fstream>
#include <vector>
#include <string>
#include "userStore.h"
#include "../pm.types/user.h"

std::vector<pm::types::User> users;
pm::dal::UserStore userStore;

int pm::dal::UserStore::generateNewId()
{
	int maxId = 0;

	userStore.getData();
	users = userStore.getAll();

	for (auto user : users)
	{
		if (user.id > maxId)
		{
			maxId = user.id;
		}
	}

	return maxId + 1;
}

void pm::dal::UserStore::createNewUser(pm::types::User& user)
{
	std::ofstream file("../../data/Users.txt", std::ios::in | std::ios::ate);

	file << user.id << ',' << user.username << ',' << user.firstName << ',' << user.lastName << 
		',' << user.email << ',' << user.privilege << ',' << user.passwordHash << ',' << '\n';

	file.close();
}

void pm::dal::UserStore::remove(int delId)
{
	int index = -1;
	userStore.getData();

	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].id == delId)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		std::cout << std::endl << "     User with ID " << delId << " does not exist!";
		return;
	}

	users.erase(users.begin() + index);

	std::cout << std::endl << "     User successfully removed!";

	std::ofstream file("../../data/Users.txt", std::ios::in | std::ios::trunc);


	for (unsigned i = 0; i < users.size(); i++)
	{
		pm::types::User user = users[i];

		file << user.id << ',' << user.username << ',' << user.firstName << ',' << user.lastName <<
			',' << user.email << ',' << user.privilege << ',' << user.passwordHash << ',' << '\n';
	}

	file.close();
}

void pm::dal::UserStore::update(std::vector<pm::types::User> users)
{
	std::ofstream file("../../data/Users.txt", std::ios::in | std::ios::trunc);


	for (unsigned i = 0; i < users.size(); i++)
	{
		pm::types::User user = users[i];

		file << user.id << ',' << user.username << ',' << user.firstName << ',' << user.lastName <<
			',' << user.email << ',' << user.privilege << ',' << user.passwordHash << ',' << '\n';
	}

	file.close();
}

pm::types::User pm::dal::UserStore::getById(size_t id)
{
	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i].id == id)
		{
			return users[i];
		}
	}
}

std::vector<pm::types::User> pm::dal::UserStore::getAll()
{
	return std::vector<pm::types::User>(users);
}

void pm::dal::UserStore::getData()	// Starts reading the Records.txt file so it can input information into it
{
	std::ifstream file("../../data/Users.txt", std::fstream::in);
	users.clear();

	std::string id, userName, firstName, lastName, email, /* dateOfCreation, idOfCreator, dateOfLastChange, idOfChange, */ privilege, password, next;

	if (file.is_open())	// The file is successfully opened
	{
		while (std::getline(file, id, ','))
		{
			std::getline(file, userName, ',');
			std::getline(file, firstName, ',');
			std::getline(file, lastName, ',');
			std::getline(file, email, ',');

			/*std::getline(file, dateofcreation, ',');
			std::getline(file, idofcreator, ',');
			std::getline(file, dateoflastchange, ',');
			std::getline(file, idofchange, ',');*/

			std::getline(file, privilege, ',');
			std::getline(file, password, ',');
			std::getline(file, next, '\n');

			addToUsers(stoi(id), userName, firstName, lastName, email, stoi(privilege), password);
		}

		file.close();
	}

	else	// there is a problem with the file
	{
		std::cout << "Enable to open the file!" << std::endl;
	}
}

void pm::dal::UserStore::addToUsers(int id, std::string username, std::string firstName, std::string lastName, std::string email, bool privilege, std::string password)
{
	pm::types::User user;

	user.id = id;
	user.username = username;
	user.firstName = firstName;
	user.lastName = lastName;
	user.email = email;
	user.privilege = privilege;
	user.passwordHash = password;

	users.push_back(user);
}