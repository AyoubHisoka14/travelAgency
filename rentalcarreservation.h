#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H

#include "booking.h"

class RentalcarReservation : public Booking
{
public:
    RentalcarReservation(char eingabeTyp,int eingabeID, double eingabeP, string eingabeFDate, string eingabeTDate, string eingabePL, string eingabeRL, string eingabeCompany);

    string showDetails();

    void setPL(string eingabe);

    string getPL();

    void setRL(string eingabe);

    string getRL();

    void setCompany(string eingabe);

    string getCompany();

    ~RentalcarReservation();


private:
    string pickupLocation;
    string returnLocation;
    string company;

};

#endif // RENTALCARRESERVATION_H
