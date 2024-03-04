#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include "travel.h"
#include <vector>

using namespace std;

class Customer
{
public:
    Customer(int eingabeID, string eingabeVName, string eingabeNName);
    void addTravel(shared_ptr<Travel> travel);
    bool findTravel(int travleID);
    int getID();
    string getVName();
    string getNName();
    string getStartDate(int travelNumber);
    string getEndDate(int travelNumber);
    int getTravelID(int travelNumber);
    int getSizeTravels();
    int getNumberTravelReservations(int travelID);
    int getReservationId(int travelID, int reservationNumber);
    string getReservationStartDate(int travelID, int reservationNumber);
    string getReservationEndDate(int travelID, int reservationNumber);
    double getReservationPrice(int travelID, int reservationNumber);

    void setAbstand(double eingabe);
    double getAbstand();



private:
    int id;
    string vorName, nachName;
    vector <shared_ptr<Travel>> travelList;
    double abstand;

};

#endif // CUSTOMER_H
