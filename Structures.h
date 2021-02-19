#ifndef BOOKINGAPP_STRUCTURES_H
#define BOOKINGAPP_STRUCTURES_H

struct timeNDate{
    std::string time;
    uint16_t year;
    uint8_t date;
    std::string day;
    std::string month;
};

struct Flight{
    std::string destination;
    std::string departure;
    timeNDate departureTime;
    timeNDate destinationTime;
};

struct OP{
public:
    std::string emailAdress;
    std::string password;
};

struct Person :public OP{
public:
    std::string firstName;
    std::string lastName;
    Person(const std::string &email, const std::string &password,
           const std::string &lastName, const std::string &firstName){
        this->emailAdress = email;
        this->password = password;
        this->firstName = firstName;
        this->lastName = lastName;
    }
    Person(){}
};
#endif //BOOKINGAPP_STRUCTURES_H
