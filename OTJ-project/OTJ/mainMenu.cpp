#include <iostream>
#include "mainMenu.h"
#include "../pm.types/User.h"
#include "../pm.dal/UserStore.h"
#include "../pm.bll/userManager.h"

void mainMenu::displayMenu()
{
    std::cout << "==============================" << std::endl;
    std::cout << "             MENU             " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "                              " << std::endl;
    std::cout << "         1) Login             " << std::endl;
    std::cout << "         2) Register          " << std::endl;
    std::cout << "         3) Exit              " << std::endl;
    std::cout << "                              " << std::endl;
    std::cout << "==============================" << std::endl;

    std::cout << std::endl << "Select >> ";

    choice(mainMenu::inputChoice());
}

int mainMenu::inputChoice()   // Takes the user's choice
{
    int user_choice;
    bool check_num = false;

    while (check_num == false)
    {
        if (std::cin >> user_choice)
        {
            if (user_choice > 3 || user_choice < 1) // Invalid input
            {
                std::cout << std::endl << "You entered an invalid operation. Please try again." << std::endl << std::endl;
                std::cout << "Select >> ";
                check_num = false;
            }

            else    // Valid input
            {
                check_num = true;
            }
        }

        else    // The user entered a character
        {
            std::cout << std::endl << "You entered an invalid operation. Please try again." << std::endl;
            std::cout << "Select >> ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            check_num = false;
        }
    }

    return user_choice;
}

void mainMenu::choice(int user_choice)    // Takes the user to the different operations depending on their choice
{
    system("CLS");

    switch (user_choice)
    {
    case 1:
        break;

    case 2:
        mainMenu::registerMenu();
        break;

    case 3:
        system("CLS");
        // cout << "Thank you for using our program! :)" << endl;
        exit(0);
    }
}

void mainMenu::registerMenu()
{
    std::string firstName, lastName, email, password;
    int age;

    std::cin.clear();
    std::cin.ignore(1000, '\n');

    std::cout << "==============================" << std::endl;
    std::cout << "           REGISTER           " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout << "                              " << std::endl;
    std::cout << "             Enter           " << std::endl;
    std::cout << "     First Name: "; std::getline(std::cin, firstName);
    std::cout << "     Last Name: "; std::getline(std::cin, lastName);
    std::cout << "     Age: "; std::cin >> age;
    std::cout << "     Email: "; std::cin >> email;
    std::cout << "     Password: "; std::cin >> password;
    std::cout << "                              " << std::endl;
    std::cout << "==============================" << std::endl;

    pm::bll::UserManager::registerUser(firstName, lastName, age, email, password);
}