#include "pch.h"
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

	file << user.id << ',';
	file << user.username << ',';
	file << user.firstName << ',';
	file << user.lastName << ',';
	file << user.email << ',';
	file << user.dateOfCreation << ',';
	file << user.idOfCreator << ',';
	file << user.dateOfLastChange << ',';
	file << user.idOfChange << ',';
	file << user.privilege << ',';
	file << user.passwordHash << ',' << '\n';

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

		userStore.createNewUser(user);
	}

	file.close();
}

void pm::dal::UserStore::update(std::vector<pm::types::User> users)
{
	std::ofstream file("../../data/Users.txt", std::ios::in | std::ios::trunc);


	for (unsigned i = 0; i < users.size(); i++)
	{
		pm::types::User user = users[i];

		userStore.createNewUser(user);
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

bool pm::dal::UserStore::getByUsername(std::string username)
{
	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i].username == username)
		{
			return true;
		}
	}

	return false;
}

std::vector<pm::types::User> pm::dal::UserStore::getAll()
{
	return std::vector<pm::types::User>(users);
}

void pm::dal::UserStore::getData()	// Starts reading the Records.txt file so it can input information into it
{
	std::ifstream file("../../data/Users.txt", std::fstream::in);
	users.clear();

	std::string id, userName, firstName, lastName, email, dateOfCreation, idOfCreator, dateOfLastChange, idOfChange, privilege, password, next;

	if (file.is_open())	// The file is successfully opened
	{
		while (std::getline(file, id, ','))
		{
			std::getline(file, userName, ',');
			std::getline(file, firstName, ',');
			std::getline(file, lastName, ',');
			std::getline(file, email, ',');
			std::getline(file, dateOfCreation, ',');
			std::getline(file, idOfCreator, ',');
			std::getline(file, dateOfLastChange, ',');
			std::getline(file, idOfChange, ',');
			std::getline(file, privilege, ',');
			std::getline(file, password, ',');
			std::getline(file, next, '\n');

			addToUsers(stoi(id), userName, firstName, lastName, email, stoi(dateOfCreation), stoi(idOfCreator), stoi(dateOfLastChange), stoi(idOfChange), stoi(privilege), password);
		}

		file.close();
	}

	else	// there is a problem with the file
	{
		std::cout << "Enable to open the file!" << std::endl;
	}
}

void pm::dal::UserStore::addToUsers(int id, std::string username, std::string firstName, std::string lastName, std::string email, time_t dateOfCreation, int idOdCreator, time_t dateOfLastChange, int idOfChange, bool privilege, std::string password)
{
	pm::types::User user;

	user.id = id;
	user.username = username;
	user.firstName = firstName;
	user.lastName = lastName;
	user.email = email;
	user.dateOfCreation = dateOfCreation;
	user.idOfCreator = idOdCreator;
	user.dateOfLastChange = dateOfLastChange;
	user.idOfChange = idOfChange;
	user.privilege = privilege;
	user.passwordHash = password;

	users.push_back(user);
}