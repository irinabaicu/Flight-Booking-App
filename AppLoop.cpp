#include <iostream>
#include "User.h"

void appLoop(User user){
    std::string command;
    while(true){
        std::cout << "Enter command (Press 'h' for help):" << std::endl;
        std::cin >> command;
        std::getchar();
        if(command == "h"){
            std::cout << "Commands: " << std::endl;
            std::cout << "->search\n->book\n->view\n->exit\n";
        }
        if(command == "search"){
            user.searchFlight();
        }
        if(command == "view"){
            user.viewFlights();
        }
        if(command == "book"){
            std::string flightNumber;
            std::cout << "Enter the flight number starting with a '#':" << std::endl;
            std::cin >> flightNumber;
            std::getchar();
            user.bookFlight(flightNumber);
        }
        if(command == "exit")
            break;
    }
};
