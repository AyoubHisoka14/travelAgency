#include "booking.h"

Booking::Booking(char eingabeTyp,int eingabeID, double eingabeP, string eingabeFD, string eingabeTD)
    :typ(eingabeTyp),id(eingabeID), price(eingabeP), fromDate(eingabeFD), toDate(eingabeTD)
{}

    void Booking::setTyp(char eingabe)
    {
        typ=eingabe;
    }
    void Booking::setID(string eingabe)
    {
        id=stoi(eingabe);
    }
    void Booking::setPrice(double eingabe)
    {
        price=eingabe;
    }
    void Booking::setFD(string eingabe)
    {
        fromDate=eingabe;
    }
    void Booking::setTD(string eingabe)
    {
        toDate=eingabe;
    }
    void Booking::setVorganger(int eingabe)
    {
        vorganger.push_back(eingabe);
    }

    void Booking::setEndBearbeitung(int eingabe)
    {
        endBearbeitung=eingabe;
    }

    char Booking::getTyp()
    {
        return typ;
    }
    int Booking::getID()
    {
        return id;
    }
    double Booking::getPrice()
    {
        return price;
    }
    string Booking::getFD()
    {
        return fromDate;
    }
    string Booking::getTD()
    {
        return toDate;
    }
    int Booking::getAnzahlVorganger()
    {
        return vorganger.size();
    }
    int Booking::getVorganger(int eingabe)
    {
        return vorganger[eingabe];
    }
    int Booking::getEndBearbeitung()
    {
        return endBearbeitung;
    }




