#include "rentalcarreservation.h"

RentalcarReservation::RentalcarReservation(char eingabeTyp,int eingabeID, double eingabeP, string eingabeFDate, string eingabeTDate, string eingabePL, string eingabeRL, string eingabeCompany)
    :Booking(eingabeTyp,eingabeID, eingabeP, eingabeFDate, eingabeTDate), pickupLocation(eingabePL), returnLocation(eingabeRL), company(eingabeCompany)
{}


string RentalcarReservation::showDetails()
{
    return "Mietwagenreservierung " + to_string(getID()) + " mit " + company + ". Abholdatum am " + getFD() + " in " + pickupLocation + ". Ruckgabe am " + getTD() + " in " + returnLocation +". Preis : " + to_string(getPrice()) + " Euro";
}
void RentalcarReservation::setPL(string eingabe)
{
    pickupLocation=eingabe;
}
string RentalcarReservation::getPL()
{
    return pickupLocation;
}
void RentalcarReservation::setRL(string eingabe)
{
    returnLocation=eingabe;
}
string RentalcarReservation::getRL()
{
    return returnLocation;
}
void RentalcarReservation::setCompany(string eingabe)
{
    company=eingabe;
}
string RentalcarReservation::getCompany()
{
    return company;
}
RentalcarReservation::~RentalcarReservation(){}



