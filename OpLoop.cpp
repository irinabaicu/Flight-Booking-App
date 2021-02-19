
#include <iostream>
#include "Operator.h"
#include "Account.h"

void opLoop(Operator op){
    std::string command;
    while(true){
        std::cout << "Enter command (Press 'h' for help):" << std::endl;
        std::cin >> command;
        std::getchar();
        if(command == "h"){
            std::cout << "Commands: " << std::endl;
            std::cout << "->validate\n->add\n->delete\n->view\n->exit\n";
        }
        if(command == "validate"){
            op.confirmFlights();
        }
        if(command == "add"){
            op.addFlight();
        }
        if(command == "delete"){
            std::cout << "Enter the flight number starting with '#' which " <<
                         "corresponds to the flight you want to delete:" << std::endl;
            std::cin >> command;
            std::getchar();
            op.deleteFlight(command);
        }
        if(command == "view"){
            op.viewFlights();
        }
        if(command == "exit"){
            break;
        }
    }
};