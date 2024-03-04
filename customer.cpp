#include "customer.h"

Customer::Customer(int eingabeID, string eingabeVName, string eingabeNName)
    :id(eingabeID), vorName(eingabeVName), nachName(eingabeNName)
{

}
void Customer::addTravel(shared_ptr<Travel> travel)
{
    travelList.push_back(travel);
}
bool Customer::findTravel(int travelID)
{
    for(int i=0; i<travelList.size(); i++)
    {
        if(travelList[i]->getID()==travelID)
            return true;
    }
    return false;
}

int Customer::getID()
{
    return id;
}
string Customer::getVName()
{
    return vorName;
}
string Customer::getNName()
{
    return nachName;
}
int Customer::getSizeTravels()
{
    return travelList.size();
}
string Customer::getStartDate(int travelNumber)
{
    return travelList[travelNumber]->getStartDate();

}
string Customer::getEndDate(int travelNumber)
{
    return travelList[travelNumber]->getEndDate();
}
int Customer::getTravelID(int travelNumber)
{
    return travelList[travelNumber]->getID();
}
int Customer::getNumberTravelReservations(int travelID)
{
    for(int i=0;i<travelList.size();i++)
    {
        if(travelList[i]->getID()==travelID)
            return travelList[i]->getNumberReservations();
    }
}

int Customer::getReservationId(int travelID, int reseravtionNumber)
{
    for(int i=0;i<travelList.size();i++)
    {
        if(travelList[i]->getID()==travelID)
            return travelList[i]->getReservationId(reseravtionNumber);
    }
}

string Customer::getReservationStartDate(int travelID, int reseravtionNumber)
{
    for(int i=0;i<travelList.size();i++)
    {
        if(travelList[i]->getID()==travelID)
            return travelList[i]->getReservationStartDate(reseravtionNumber);
    }
}

string Customer::getReservationEndDate(int travelID, int reseravtionNumber)
{
    for(int i=0;i<travelList.size();i++)
    {
        if(travelList[i]->getID()==travelID)
            return travelList[i]->getReservationEndDate(reseravtionNumber);
    }
}

double Customer::getReservationPrice(int travelID, int reseravtionNumber)
{
    for(int i=0;i<travelList.size();i++)
    {
        if(travelList[i]->getID()==travelID)
            return travelList[i]->getReservationPreis(reseravtionNumber);
    }
}

void Customer::setAbstand(double eingabe)
{
    abstand=eingabe;
}

double Customer::getAbstand()
{
    return abstand;
}
