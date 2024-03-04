#ifndef TRAVEL_H
#define TRAVEL_H
#include "booking.h"
#include "graph.h"
#include "algorithmen.cpp"
#include <memory>
#include <vector>
#include <algorithm>

class Travel
{
public:
    Travel(int eingabeID, int eingabeKID);
    void addBooking(shared_ptr<Booking> booking);
    string getStartDate();
    string getEndDate();
    int getID();
    int getNumberReservations();
    int getReservationId(int reservationNumber);
    string getReservationStartDate(int reservationNumber);
    string getReservationEndDate(int reservationNumber);
    double getReservationPreis(int reservationNumber);

    bool checkRoundTrip();
    bool checkEnoughHotels();
    bool checkNoUselessHotels();
    bool checkNoUselessRentalCars();



private:
    int id;
    int customerId;
    vector <shared_ptr<Booking>> travelBookings;
    Graph<shared_ptr<Booking>, 20> myGraph; //here i used a smart pointer but it did not work for some reason???

    int index=1;
};

#endif // TRAVEL_H
