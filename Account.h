#ifndef BOOKINGAPP_ACCOUNT_H
#define BOOKINGAPP_ACCOUNT_H
#include <string>
#include "Structures.h"

std::string hashPassword(const std::string &password);
bool checkPassword(const std::string &password, const std::string &hash);
std::string searchHash(const std::string &email, const std::string &path);
bool searchItem(const std::string &item, const std::string &path);
bool authentification(const std::string &email);
void addUser(Person user);
bool createAccount();
Person instantiateUser(const std::string email);

#endif //BOOKINGAPP_ACCOUNT_H
