#pragma once

namespace mainMenu
{
	void loginMenu();

	void adminOptionsMenu();
}

// Za User.h

namespace pm::types
{
	struct User
	{
		int id;
		std::string username;
		std::string firstName;
		std::string lastName;
		std::string email;
		/*
		time_t dateOfCreation;
		size_t idOfCreator;
		time_t dateOfLastChange;
		size_t idOfChange;
		*/
		bool privilage;
		std::string passwordHash;
	};
}

// Za UserStore.h

namespace pm::dal
{
	struct UserStore
	{
		/*
		void create(pm::types::User& user);

		std::vector<pm::types::User> getAll();

		void remove(size_t id);

		void update(pm::types::User user);
		*/

		pm::types::User getById(size_t id);

		bool getByUsername(std::string username);

		void getData();

		void addToUsers(int id, std::string userName, std::string firstName, std::string lastName, std::string email, bool privilage, std::string password);

		void displayUsers();
	};
}

// Za userManager.h

namespace pm::bll
{
	struct UserManager
	{
		pm::dal::UserStore m_userStore;

		bool loginUser(std::string username, std::string password);
		/*

		std::string hashString(std::string str);

		void registerUser(std::string firstName, std::string lastName, uint8_t age, std::string email, std::string password);

		pm::types::User loginUser(std::string username, std::string password);

		std::vector<pm::types::User> getRegisteredUsers();

		void seedDatabase();

		void removeUser(size_t id);

		void updateUser(pm::types::User);
		*/
	};
}