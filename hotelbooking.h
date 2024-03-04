#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H

#include "booking.h"

class HotelBooking : public Booking
{
public:
    HotelBooking(char eingabeTyp,int eingabeID, double eingabeP, string eingabeFDate, string eingabeTDate, string eingabeHotel, string eingabeTown);

    string showDetails();

    void setHotel(string eingabe);

    string getHotel();

    void setTown(string eingabe);

    string getTown();

    ~HotelBooking();


private:
    string hotel;
    string town;
};

#endif // HOTELBOOKING_H
