#ifndef BOOKINGAPP_USER_H
#define BOOKINGAPP_USER_H

#include <cstdint>
#include <string>
#include <vector>
#include "Structures.h"
#include "Operator.h"

class User {
private:
    Person user;
public:
    User(Person user): user(user){}
    static bool searchFlight(); //afiseaza un calendar.
    void bookFlight(const std::string &flightNumber);
    void viewFlights();
};



#endif //BOOKINGAPP_USER_H