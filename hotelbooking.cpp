#include "hotelbooking.h"

HotelBooking::HotelBooking(char eingabeTyp,int eingabeID, double eingabeP, string eingabeFDate, string eingabeTDate, string eingabeHotel, string eingabeTown)
    :Booking(eingabeTyp,eingabeID, eingabeP, eingabeFDate, eingabeTDate), hotel(eingabeHotel), town(eingabeTown)
{}

//HotelBooking();

string HotelBooking::showDetails()
{
    return "Hotelbuchung " + to_string(getID()) + " in " + hotel + " von " + getFD() + " bis zum " + getTD() + " Preis : " + to_string(getPrice()) + " Euro";
}
void HotelBooking::setHotel(string eingabe)
{
    hotel=eingabe;
}
string HotelBooking::getHotel()
{
    return hotel;
}
void HotelBooking::setTown(string eingabe)
{
    town=eingabe;
}
string HotelBooking::getTown()
{
    return town;
}
HotelBooking::~HotelBooking(){}


