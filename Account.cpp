#include <iostream>
#include <fstream>
#include <cstdint>
#include "Structures.h"
#include "Account.h"
#include "CustomException.h"
#include <sstream>
#include <regex>
#define KEY 73

/*
 * *********************************PASSWORD*************************************************************
 * */

bool checkPassword(const std::string &password)
{

    // For checking if password length
    // is between 8 and 15
    if (!((password.length() >= 8) &&
          (password.length() <= 15)))
        return false;

    // To check space
    if (password.find(" ") !=
        std::string::npos)
        return false;

    if (true)
    {
        int count = 0;

        // Check digits from 0 to 9
        for(int i = 0; i <= 9; i++)
        {

            // To convert int to string
            std::string str1 = std::to_string(i);

            if (password.find(str1) !=
                std::string::npos)
                count = 1;
        }
        if (count == 0)
            return false;
    }

    // For special characters
    if (!((password.find("@") != std::string::npos) ||
          (password.find("#") != std::string::npos) ||
          (password.find("!") != std::string::npos) ||
          (password.find("~") != std::string::npos) ||
          (password.find("$") != std::string::npos) ||
          (password.find("%") != std::string::npos) ||
          (password.find("^") != std::string::npos) ||
          (password.find("&") != std::string::npos) ||
          (password.find("*") != std::string::npos) ||
          (password.find("(") != std::string::npos) ||
          (password.find(")") != std::string::npos) ||
          (password.find("-") != std::string::npos) ||
          (password.find("+") != std::string::npos) ||
          (password.find("/") != std::string::npos) ||
          (password.find(":") != std::string::npos) ||
          (password.find(".") != std::string::npos) ||
          (password.find(",") != std::string::npos) ||
          (password.find("<") != std::string::npos) ||
          (password.find(">") != std::string::npos) ||
          (password.find("?") != std::string::npos) ||
          (password.find("|") != std::string::npos)))
        return false;

    if (true)
    {
        int count = 0;

        // Checking capital letters
        for(int i = 65; i <= 90; i++)
        {

            // Type casting
            char c = (char)i;
            std::string str1(1, c);

            if (password.find(str1) !=
                std::string::npos)
                count = 1;
        }
        if (count == 0)
            return false;
    }

    if (true)
    {
        int count = 0;

        // Checking small letters
        for(int i = 90; i <= 122; i++)
        {

            // Type casting
            char c = (char)i;
            std::string str1(1, c);

            if (password.find(str1) !=
                std::string::npos)
                count = 1;
        }
        if (count == 0)
            return false;
    }

    // If all conditions fails
    return true;
}
std::string hashPassword(const std::string &password){
    std::string hash;
    for(uint8_t byte : password){
        if(byte % 7 == 0)
            hash.push_back(byte+KEY/2);
        else
            hash.push_back(byte+KEY);
    }
    return hash;
}

bool checkPassword(const std::string &password, const std::string &hash){
    if(hashPassword(password) == hash)
        return true;
    return false;
}

std::string searchHash(const std::string &email, const std::string &path){
    std::ifstream file;
    try{
        file.open(path);
        std::string cell;
        while(std::getline(file, cell, '\n')){
            std::stringstream ss(cell);
            std::getline(ss, cell, ',');
            if(cell == email) {
                std::getline(ss, cell, ',');
                file.close();
                return cell;
            }
        }
        cell = "";
        file.close();
        return cell;

    }
    catch(const std::ifstream::failure& e){
        std::cout << "Could not load server. Try again later."; //nu s-a deschis "baza de date"
    }

}

//*************************************************SEARCH*******************************************************

bool searchItem(const std::string &item, const std::string &path){
    std::ifstream file;
    try{
        file.open(path);
        std::string line;
        while(std::getline(file, line,',')){
            if(line == item) {
                return true;
            }
            std::getline(file, line, '\n');
        }
        return false;

    }
    catch(const std::ifstream::failure& e){
        std::cout << "Could not load server. Try again later."<< std::endl; //nu s-a deschis "baza de date"
    }

}


//*********************************************AUTHENTIFICATION***************************************************

bool checkEmail(const std::string& email)
{
    const std::regex pattern
            ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, pattern);
}

bool authentification(const std::string &email){
    try{
        std::string password;
        std::cout << "Enter your password:" << std::endl;
        std::cin >> password;
        std::getchar();
        std::string hash = searchHash(email, "user.csv");
        if(hash.length() == 0)
            throw(MyException("NO USER FOUND!"));
        if(!checkPassword(password, hash))
            throw(MyException("INCORRECT PASSWORD!"));
        std::cout << "Authentification complete! You can now use the app." << std::endl;
        return true;

    }
    catch(MyException &e){
        std::cout << e.what() << std::endl;
        return false;
    }
    //creare exceptii complexe pentru a le pride separat
}

void addUser(Person user){
    std::ofstream file;
    try{
        file.open("user.csv", std::ios::app);
        file << user.emailAdress << "," << hashPassword(user.password)
        << "," << user.firstName << "," << user.lastName << "\n";
    }
    catch (const std::ofstream::failure& e) {
        std::cout << "Could not load server. Try again later." << std::endl;
    }
}

//***********************************************CREATION*********************************************************

bool createAccount(){
    try{
        std::string lastName, firstName;
        std::cout << "Enter your last name: "<< std::endl;
        std::cin >> lastName;
        std::getchar();
        std::cout << "Enter your first name: " << std::endl;
        std::cin >> firstName;
        std::getchar();
        std::cout << "Enter your email: " << std::endl;
        std::string email;
        std::cin >> email;
        std::getchar();
        if(!checkEmail(email))
            throw(MyException("INVALID EMAIL!"));
        if(searchItem(email,"user.csv")) //search if already exists
            throw(MyException("EMAIL USED!"));
        std::cout << "Enter your password: "<< std::endl;
        std::string password;
        std::cin >> password;
        std::getchar();
        if(!checkPassword(password))
            throw(MyException("PASSWORD MUST HAVE BETWEEN 8 AND 15 CHARACTERS,AT LEAST 1 CAPITAL LETTER, AT LEAST 1 SMALL LETTER,AT LEAST 1 NUMBER AND AT LEAST ONE SPECIAL CHARACTER!"));
        std::cout << "Account created succsesfully. Enjoy!" <<std::endl;
        Person user(email, password, lastName, firstName);
        addUser(user);
        return true;

    }
    catch(MyException &e){
        std::cout << e.what() << std::endl;
        return false;
    }
}

Person instantiateUser(const std::string email) {
    std::ifstream file;
    try {
        file.open("user.csv");
        std::string line;
        while (std::getline(file, line, ',')) {
            if (line == email) {
                std::getline(file, line, '\n');
                std::stringstream ss(line);
                std::string firstName, lastName, password;
                char c;
                ss >> password >> c >> firstName >> c >> lastName;
                Person person(email, password, lastName, firstName);
                return person;
            }
            std::getline(file,line,'\n');
        }
        Person person;
        return person;
    }
    catch (const std::ifstream::failure &e) {
        std::cout << "Could not load server. Try again later." << std::endl; //nu s-a deschis "baza de date"
        Person person;
        return person;
    }
}