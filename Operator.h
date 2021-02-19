#ifndef BOOKINGAPP_OPERATOR_H
#define BOOKINGAPP_OPERATOR_H
#include <string>
#include<cstdint>
#include "Structures.h"



class Operator {
private:
    OP oper;
public:
    Operator(const std::string &email, const std::string &password){
        oper.emailAdress = email;
        oper.password = password;
    };
    void confirmFlights(); //cauta in fisier si lala
    void addFlight();
    void deleteFlight(const std::string &flightNumber);
    void viewFlights();

};

#endif //BOOKINGAPP_OPERATOR_H
