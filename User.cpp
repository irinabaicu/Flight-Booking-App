#include "User.h"
#include <fstream>
#include <iostream>
#include <sstream>

#define KEY 73

bool User::searchFlight() {
    std::cout << "Enter departure country: " <<std::endl;
    std::string departureCountry;
    std::cin >> departureCountry;
    std::getchar();
    std::cout << "Enter destination country: " <<std::endl;
    std::string destinationCountry;
    std::cin >> destinationCountry;
    std::getchar();
    std::ifstream file;
    try{
        file.open("flights.csv");
        std::string line;
        bool departureFound = false, destinationFound = false;
        while(std::getline(file, line,'\n')){
            std::stringstream SS(line);
            std::string flightNumber;
            std::getline(SS, flightNumber, ',');
            std::getline(SS, line, ',');
            departureFound = false;
            if(line == departureCountry) {
                departureFound = true;
                std::getline(SS, line, ',');
                if(line == destinationCountry) {
                    destinationFound = true;
                    std::cout << flightNumber ;
                    std::cout << "  ####  " << departureCountry << " : ";
                    std::getline(SS, line, ' ');
                    std::stringstream ss(line);
                    while(std::getline(ss, line, ','))
                        std::cout << line << " ";
                    std::cout << "------>" << destinationCountry << " : ";
                    std::string garbage;
                    std::getline(SS,garbage,',');
                    std::getline(SS, line, '\n');
                    std::stringstream sss(line);
                    while(std::getline(sss, line, ','))
                        std::cout << line << " ";
                    std::cout << "  ####  " << std::endl;
                }
            }
        }
        if(!departureFound){
            std::cout << "No flights from " << departureCountry << " available at the moment." <<std::endl;
            return false;
        }
        else if(!destinationFound){
            std::cout << "No flight from " << departureCountry << " to "
                      << destinationCountry << "." <<std::endl;
            return false;
        }
        return true;
    }

    catch(const std::ifstream::failure& e){
        std::cout << "Could not load server. Try again later."<< std::endl; //nu s-a deschis "baza de date"
        return false;
    }
}

void User::bookFlight(const std::string &flightNumber) {
    try {
        BOOK:
        std::ifstream file;
        Flight flight;
        file.open("flights.csv");
        std::string line;
        bool found = false;
        while (std::getline(file, line, ',')) {
            if (line == flightNumber) {
                found = true;
                std::getline(file, line, '\n');
                std::stringstream ss(line);
                char c;
                std::string data;
                std::getline(ss, flight.departure, ',');
                std::getline(ss, flight.destination, ',');
                std::getline(ss, flight.departureTime.day, ',');
                std::getline(ss,data, ',');
                std::stringstream converter(data);
                converter >> flight.departureTime.date;
                std::getline(ss, flight.departureTime.month, ',');
                std::getline(ss, data, ',');
                converter.clear();
                converter.str(data);
                converter >> flight.departureTime.year;
                std::getline(ss, flight.departureTime.time, ',');
                /*file >> flight.departure >> c >> flight.destination >> c >> flight.departureTime.day >> c
                     >> flight.departureTime.date >> c >> flight.departureTime.month >> c >> flight.departureTime.year
                     >> c >> flight.departureTime.time;*/
                std::getline(ss, data, ',');
                std::getline(ss, flight.destinationTime.day, ',');
                std::getline(ss,data, ',');
                converter.clear();
                converter.str(data);
                converter >> flight.destinationTime.date;
                std::getline(ss, flight.destinationTime.month, ',');
                std::getline(ss, data, ',');
                converter.clear();
                converter.str(data);
                converter >> flight.destinationTime.year;
                std::getline(ss, flight.destinationTime.time, ',');
                /*file >> flight.destinationTime.day >> c >> flight.destinationTime.date >> c
                     >> flight.destinationTime.month
                     >> c >> flight.destinationTime.year >> c >> flight.destinationTime.time;*/
            }
            std::getline(file, line, '\n');
        }
        file.close();
        if(found) {
            std::ofstream file2;
            file2.open("unconfirmedflights.csv", std::ios::app);
            file2 << this->user.emailAdress << ',' << flightNumber << ',' << flight.departure << ','
                  << flight.destination << ',' <<
                  flight.departureTime.day << ',' << flight.departureTime.date << ',' << flight.departureTime.month
                  << ',' << flight.departureTime.year << ',' << flight.departureTime.time << ',' << " ,";
            file2 << flight.destinationTime.day << ',' << flight.destinationTime.date << ','
                  << flight.destinationTime.month
                  << ',' << flight.destinationTime.year << ',' << flight.destinationTime.time << '\n';
            std::cout << "Your flight is booked.\nPlease wait until an operator has reviewed your reservation"
                      << std::endl;
            file2.close();
        }
        else {

            std::cout << "The flight with the code " << flightNumber << " does not exist. Do you want to try again?" <<
                      "(y/n)" << std::endl;
            char c;
            std::cin >> c;
            std::getchar();
            if (c == 'y')
                goto BOOK;
        }
    }
    catch (const std::ifstream::failure &e) {
    std::cout << "We are sorry. This service is not available" <<
              "at the momment. Please, try again later." << std::endl;
    }
}

void User::viewFlights() {
    std::ifstream file;
    file.open("confirmedflights.csv");
    std::string line;
    std::vector<std::string> flights;
    while(std::getline(file,line,',')){
        if(line == this->user.emailAdress) {
            std::getline(file, line, '\n');
            flights.push_back(line);
        }
        std::getline(file, line, '\n');
    }
    if(flights.size()){
        std::cout << "Your flights are: " << std::endl;
        for(std::string flight : flights){
            std:: cout << flight << std::endl;
        }
        std::cout << std::endl;
    }
    else{
        std::cout << "You have no flights at the moment." << std::endl;
    }
}