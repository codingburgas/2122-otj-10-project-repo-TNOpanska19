/*****************************************************************//**
 * \file   userStore.cpp
 * \brief  Source file for user storing
 * 
 * \author Tereza
 * \date   July 2022
 *********************************************************************/

#include "pch.h"
#include "userStore.h"
#include "../pm.types/user.h"

/// <summary>
/// Object of UserStore structure
/// </summary>
pm::dal::UserStore uStore;
/// <summary>
/// Vector of type User. Used to store users
/// </summary>
std::vector<pm::types::User> users;

/// <summary>
/// Used for getting user data from database (.txt file)
/// </summary>
void pm::dal::UserStore::getData()
{
	std::string id, userName, firstName, lastName, email, dateOfCreation, idOfCreator, dateOfLastChange, idOfChange, privilege, password, next;
	
	std::ifstream file("../../data/Users.txt", std::fstream::in);	// Open Users.txt
	users.clear();	// Clear vector of users so there is no repeating

	while (std::getline(file, id, '^'))
	{
		std::getline(file, userName, '^');
		std::getline(file, firstName, '^');
		std::getline(file, lastName, '^');
		std::getline(file, email, '^');
		std::getline(file, dateOfCreation, '^');
		std::getline(file, idOfCreator, '^');
		std::getline(file, dateOfLastChange, '^');
		std::getline(file, idOfChange, '^');
		std::getline(file, privilege, '^');
		std::getline(file, password, '^');
		std::getline(file, next, '\n');

		addToUsers(stoi(id), userName, firstName, lastName, email, stoi(dateOfCreation), stoi(idOfCreator), stoi(dateOfLastChange), stoi(idOfChange), stoi(privilege), password);
	}

	file.close();
}

/// <summary>
/// Used for adding a new user in database (.txt file)
/// </summary>
/// <param name="id">An integer argument ID of user</param>
/// <param name="username">A string argument username of user</param>
/// <param name="firstName">A string argument first name of user</param>
/// <param name="lastName">A string argument last name of user</param>
/// <param name="email">A string argument email of user</param>
/// <param name="dateOfCreation">A time_t argument date of user's creation</param>
/// <param name="idOdCreator">An integer argument ID of the creator of the user</param>
/// <param name="dateOfLastChange">A time_t argument date of last change made to a user</param>
/// <param name="idOfChange">An integer argument ID of the user who made the latest change</param>
/// <param name="privilege">A boolean argument privilege of user (0 - normal user, 1 - admin)</param>
/// <param name="password">A string argument (hashed) password of user</param>
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

/// <summary>
/// Used for creating a new user and adding them to the end of the database (.txt file)
/// </summary>
/// <param name="user">Argument of type User. The new user to be added in the database</param>
void pm::dal::UserStore::createNewUser(pm::types::User& user)
{
	std::ofstream file("../../data/Users.txt", std::ios::in | std::ios::ate);

	file << user.id << '^';
	file << user.username << '^';
	file << user.firstName << '^';
	file << user.lastName << '^';
	file << user.email << '^';
	file << user.dateOfCreation << '^';
	file << user.idOfCreator << '^';
	file << user.dateOfLastChange << '^';
	file << user.idOfChange << '^';
	file << user.privilege << '^';
	file << user.passwordHash << '^';
		
	file << '\n';

	file.close();
}

/// <summary>
/// Used for generating an ID for a new user so there aren't any repeating IDs
/// </summary>
/// <returns>ID for new user</returns>
int pm::dal::UserStore::generateNewId()
{
	int maxId = 0;

	uStore.getData();
	users = uStore.getAllUsers();

	for (auto user : users)
		if (user.id > maxId)
			maxId = user.id;

	return maxId + 1;
}

/// <summary>
/// Used for checking whether a user exists by given ID
/// </summary>
/// <param name="userId">An integer argument (supposedly) ID of a user</param>
/// <returns>True or false depending on whether user with given ID exists or not</returns>
bool pm::dal::UserStore::checkExistanceById(int userId)
{
	for (unsigned i = 0; i < users.size(); i++)
		if (users[i].id == userId)
			return true;

	return false;
}

/// <summary>
/// Used to get all currently existing users from database (.txt file)
/// </summary>
/// <returns>Vector of type User containing all created users</returns>
std::vector<pm::types::User> pm::dal::UserStore::getAllUsers()
{
	return std::vector<pm::types::User>(users);
}

/// <summary>
/// Used for updating users' data in database (.txt file)
/// </summary>
/// <param name="users">Vector of type User containing all users that should be in the database, including the updated ones</param>
void pm::dal::UserStore::update(std::vector<pm::types::User> users)
{
	std::ofstream file("../../data/Users.txt", std::ios::in | std::ios::trunc);	// Opens database (.txt file) and deletes all of it's contents so that new updated data can be added

	for (unsigned i = 0; i < users.size(); i++)
	{
		pm::types::User user = users[i];

		uStore.createNewUser(user);
	}

	file.close();
}

/// <summary>
/// Used for removing a particular user from the database (.txt file) by their given ID
/// </summary>
/// <param name="delId">An integer argument ID of user to be removed</param>
void pm::dal::UserStore::remove(int delId)
{
	int index = -1;
	uStore.getData();

	for (unsigned i = 0; i < users.size(); i++)
	{
		if (users[i].id == delId)	// User with given ID exists
		{
			index = i;
			break;
		}
	}

	if (index == -1)	// User with given ID does not exist
	{
		std::cout << std::endl << "     User with ID " << delId << " does not exist!";
		return;
	}

	users.erase(users.begin() + index);		// Removing the user from the vector containing all users

	std::cout << std::endl << "     User successfully removed!";

	std::ofstream file("../../data/Users.txt", std::ios::in | std::ios::trunc);


	for (unsigned i = 0; i < users.size(); i++)
	{
		pm::types::User user = users[i];

		uStore.createNewUser(user);
	}

	file.close();
}