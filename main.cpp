#include "User.h"
#include "Operator.h"
#include "Account.h"
#include <iostream>

void appLoop(User user);
void opLoop(Operator op);
bool checkEmail(const std::string& email);


int main() {
    MAIN:
    std::cout << "Enter the main menu? (y/n)" << std::endl;
    char input;
    std:: cin >> input;
    if(tolower(input) == 'y') {
        std::cout << "Welcome! Do you already have an account? (y/n)" << std::endl;
        std::cin >> input;
        std::getchar();
        if (tolower(input) == 'y') {
            LOGIN:
            std::string email;
            std::cout << "Enter your email:" << std::endl;
            std::cin >> email;
            std::getchar();
            if (email == "admin") {
                std::cout << "Enter your password: " << std::endl;
                std::string password;
                std::cin >> password;
                std::getchar();
                if(password == "admin") {
                    Operator op("admin", hashPassword("admin"));
                    opLoop(op);
                    goto MAIN;
                }
                else{
                    std::cout << "INCORRECT PASSWORD." << std::endl << "Try again? (y/n)" << std::endl;
                    char c;
                    std::cin >> c;
                    std::getchar();
                    if(tolower(c) == 'y')
                        goto LOGIN;
                    else
                        goto MAIN;
                }
            }
            if(!checkEmail(email)) {
                std::cout << "INVALID EMAIL!" << std::endl;
                goto FAILED;
            }
            if (authentification(email)) {
                User user(instantiateUser(email));
                appLoop(user);
                goto MAIN;
            }
            else{
                FAILED:
                std::cout << "Authentification failed... Try again? (y/n)" << std::endl;
                char c;
                std::cin >> c;
                std::getchar();
                if(tolower(c) == 'y')
                    goto LOGIN;
                else
                    goto MAIN;
            }

        }
        if (tolower(input) == 'n') {
            CREATE:
            if(createAccount())
                goto LOGIN;
            else{
                std::cout << "We failed to create your account. Do you want to try again? (y/n)" <<std::endl;
                char c;
                std::cin >> c;
                std::getchar();
                if(tolower(c) == 'y')
                    goto CREATE;
                else
                    goto MAIN;
            }
        }
    }
    std::cout << "Exiting application... Good bye!" << std::endl;
    return 0;
}