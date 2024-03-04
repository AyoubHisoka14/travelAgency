#include "flightbooking.h"

FlightBooking::FlightBooking(char eingabeTyp,int eingabeID, double eingabeP, string eingabeFDate, string eingabeTDate, string eingabeFDe, string eingabeTDe, string eingabeAL)
    :Booking(eingabeTyp,eingabeID, eingabeP, eingabeFDate, eingabeTDate), fromDestination(eingabeFDe), toDestination(eingabeTDe), airline(eingabeAL)
{

}

string FlightBooking::showDetails()
{
    return  "Flugbuchung " +to_string(getID()) +  " von " + fromDestination + " nach " + toDestination + " mit " + airline + " am " + getFD() + ". Preis : " + to_string(getPrice()) + " Euro";
}
void FlightBooking::setFDe(string eingabe)
{
    fromDestination=eingabe;
}
string FlightBooking::getFDe()
{
    return fromDestination;
}
void FlightBooking::setTDe(string eingabe)
{
    toDestination=eingabe;
}
string FlightBooking::getTDe()
{
    return toDestination;
}
void FlightBooking::setAirline(string eingabe)
{
    airline=eingabe;
}
string FlightBooking::getAirline()
{
    return airline;
}

FlightBooking::~FlightBooking()
{

}
