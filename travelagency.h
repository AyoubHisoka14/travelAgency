#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H
#include "booking.h"
#include "travel.h"
#include "customer.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include"rentalcarreservation.h"
#include <vector>
#include<fstream>
#include<sstream>
#include <QFile>
#include "tableitem.h"
#include "airport.h"
#include "sortfunktor.h"
#include "graph.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <map>

class TravelAgency
{
public:
    string typ,Id,FD,TD,FDe,TDe,airline,hotel,town,PL,RL,company;
    string price;
    TravelAgency();
    string readFile();
    bool findCustomer(int eingabeID);
    bool findTravel(int eingabeID);
    string getStartDate(int eingabeID, int travel);
    string getEndDate(int eingabeID, int travel);
    int getTravelID(int eingabeID, int travel);
    string getCustomerVName(int eingabeID);
    string getCustomerNName(int eingabeID);
    int getSizeCustomerTravels(int eingabeID);
    int getNumberCustomerReservations(int eingabeID, int travelID);
    int getReservationID(int eingaebID, int travelID, int reservationNumber);
    string getReservationStartDate(int eingaebID, int travelID, int reservationNumber);
    string getReservationEndDate(int eingaebID, int travelID, int reservationNumber);
    double getReservationPreis(int eingaebID, int travelID, int reservationNumber);
    void search(int reseravationID);
    void json();
    string getAirportName(QString key);
    int getNumberOfReservations();
    int getReservationID(int index);
    int getNumberOfCustomers();
    double getCustomerAbstand(int index);
    string getCustomerLastName(int index);
    int getCustomerIdByName(string name);;

    char getTyp(int reservationID);
    int getID(int reservationID);
    string getFD(int reservationID);
    string getTD(int reservationID);
    double getPrice(int reservationID);

    string getFlightFDe(int reservationID);
    string getFlightTDe(int reservationID);
    string getAirline(int reservationID);
    string getHotel(int reservationID);
    string getTown(int reservationID);
    string getPL(int reservationID);
    string getRL(int reservationID);
    string getCompany(int reservationID);

    void setFD(int reservationID, string eingabe);
    void setTD(int reservationID, string eingabe);
    void setPrice(int reservationID, double eingabe);

    void setFlightFDe(int reservationID, string eingabe);
    void setFlightTDe(int reservationID, string eingabe);
    void setAirline(int reservationID, string eingabe);
    void setHotel(int reservationID, string eingabe);
    void setTown(int reservationID, string eingabe);
    void setPL(int reservationID, string eingabe);
    void setRL(int reservationID, string eingabe);
    void setCompany(int reservationID, string eingabe);

    int buchungAvis();
    int buchungUA();
    int buchungT(); //Mindestwert der Buchung ist 1000 euro

    int saveToJson(int sortierParameter, QString eingabeDatei);

    int newCustomer(string vName, string nNAme);
    int newTravel(int customerID);
    int newBooking(int travleId, char eingabeTyp, double eingabeP, string eingabeFD, string eingabeTD, string eingabe1, string eingabe2, int vorganger1, int vorganger2, string eingabe3=" ");

    bool checkRoundTrip(int travelID);
    bool checkEnoughHotels(int travelID);
    bool checkNoUselessHotels(int travelID);
    bool checkNoUselessRentalCars(int travelID);

    void relativenAbstand(string eingabe);




private:
    vector <shared_ptr<Booking>> bookings;
    vector <shared_ptr<FlightBooking>> flightBookings;
    vector <shared_ptr<HotelBooking>> hotelBookings;
    vector <shared_ptr<RentalcarReservation>> carBookings;
    vector <shared_ptr<Customer>> allCustomers;
    vector <shared_ptr<Travel>> allTravels;
    int F=0, H=0 , R=0;
    double gesamtWert=0.00;
    int reisen=0, buchungen=0;
    int company_Avis=0,united_Airlines=0,buchung_1000=0;   //for Uni Tests
    string line;
    map<QString, Airport> airportMap;

};

#endif // TRAVELAGENCY_H
