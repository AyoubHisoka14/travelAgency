#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H
#include "booking.h"

class FlightBooking: public Booking
{
public:
    FlightBooking(char eingabeTyp,int eingabeID, double eingabeP, string eingabeFDate, string eingabeTDate, string eingabeFDe, string eingabeTDe, string eingabeAL);
    virtual string showDetails();

    void setFDe(string eingabe);

    string getFDe();

    void setTDe(string eingabe);

    string getTDe();

    void setAirline(string eingabe);

    string getAirline();


    ~FlightBooking();

private:
    string fromDestination;
    string toDestination;
    string airline;
};

#endif // FLIGHTBOOKING_H
