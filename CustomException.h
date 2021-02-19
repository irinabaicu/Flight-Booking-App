#ifndef BOOKINGAPP_CUSTOMEXCEPTION_H
#define BOOKINGAPP_CUSTOMEXCEPTION_H
#include <exception>
#include <string.h>

struct MyException : public std::exception{
private:
    std::string message;
public:
    MyException(std::string message){
         this->message = message;
    }
    std::string what(){
        return message;
    }
};

#endif //BOOKINGAPP_CUSTOMEXCEPTION_H
