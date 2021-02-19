#include "Operator.h"
#include <iostream>
#include "fstream"
#include <sstream>


void Operator::confirmFlights() {
    BEGIN:
    try {
        std::ifstream file;
        file.open("unconfirmedflights.csv");
        std::string line;
        while (std::getline(file, line, '\n')) {
            std::string number, email;
            std::stringstream ss(line);
            std::getline(ss, email, ',');
            std::getline(ss, number, ',');
            std::cout << "User with email: " << email << " booked flight number: " << number << std::endl;
            INPUT:
            std::cout << "Confirm? (y/n): " << std::endl;
            char c;
            std::cin >> c;
            std::getchar();
            if (tolower(c) == 'y') {
                std::ofstream file2;
                file2.open("confirmedflights.csv", std::ios::app);
                file2 << email << ',' << number << '\n';
                file2.close();
                std::cout << "Flight confirmed..." << std::endl;
            } else if (tolower(c) == 'n') {
                std::cout << "Flight was not confirmed and has been erased from the file..." << std::endl;
            } else if (tolower(c) == 'x') {
                std::cout << "Fatal error, exiting programm...." << std::endl;
                exit(1);
            } else {
                std::cout << "Invalid input. Enter again." << std::endl;
                goto INPUT;
            }


        }
        file.close();
        std::ofstream file2;
        file2.open("unconfirmedflights.csv");
        file2.clear();
        file2.close();
        std::cout << "All flights have been reviewed. The content of the file has been erased." << std::endl;
    }
    catch(const std::ifstream::failure &e){
        std::cout << "File could not be opened... Try again? (y/n)" << std::endl;
        char c;
        std::cin >> c;
        std::getchar();
        if(tolower(c) == 'y'){
            goto BEGIN;
        }
    }
}

void Operator::deleteFlight(const std::string &flightNumber) {
    try {
        std::ifstream f1;
        std::ofstream f2("temp.csv");
        f1.open("flights.csv");
        std::string line;
        while (std::getline(f1, line, ',')) {
            if (line == flightNumber) {
                std::getline(f1, line, '\n');
                continue;
            }
            f2 << line << ',';
            std::getline(f1, line, '\n');
            f2 << line << '\n';
        }
        f1.close();
        f2.close();
        f1.open("temp.csv");
        f2.open("flights.csv", std::iostream::trunc);
        while (std::getline(f1, line, '\n')) {
            f2 << line << '\n';
        }
        f1.close();
        f2.close();
    }
    catch (std::iostream::failure &e) {
        std::cout << "Failed to open files..." << std::endl;
    }

}

void Operator::addFlight() {
    try {
        std::ofstream file;
        file.open("flights.csv", std::ios::app);
        //I will asume the operator is competent and will enter correct data
        std::cout << "Enter the flight information with the folowing formate: " << std::endl;
        std::cout << "#fN,Departure,Destination,DAY-departure,date-departure,MONTH,year,hour:minute-departure, ,"
                  << "DAY-destination,date-destination,MONTH,year,hour:minute-destination" << std::endl;
        std::string input;
        std::getline(std::cin, input, '\n');
        file << input << '\n';
        file.close();
    }
    catch(std::iostream::failure &e){
        std::cout << "Could not open file..." << std::endl;
    }
}

void Operator::viewFlights() {
    try {
        std::ifstream file;
        file.open("flights.csv");
        std::string line;
        while (std::getline(file, line, '\n')) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    catch(std::iostream::failure &e){
        std::cout << "Could not open file..." << std::endl;
    }
}