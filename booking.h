#ifndef BOOKING_H
#define BOOKING_H
#include <iostream>
#include <vector>
using namespace std;

class Booking
{
public:
    Booking(char eingabeTyp,int eingabeID, double eingabeP, string eingabeFD, string eingabeTD);
    //virtual ~Booking();
    virtual string showDetails()=0;


    void setTyp(char eingabe);

    void setID(string eingabe);

    void setPrice(double eingabe);

    void setFD(string eingabe);

    void setTD(string eingabe);

    void setVorganger(int eingabe);

    void setEndBearbeitung(int eingabe);



    char getTyp();

    int getID();

    double getPrice();

    string getFD();

    string getTD();

    int getAnzahlVorganger();

    int getVorganger(int eingabe);

    int getEndBearbeitung();


private:
    char typ;
    int id;
    double price;
    string fromDate;
    string toDate;
    int endBearbeitung;
    int kunde; //id des Kunden, wem gehört dieses Booking
    int reise; //id der Reise, zu der dieses Booking gehört
    vector<int> vorganger;
};

#endif // BOOKING_H
