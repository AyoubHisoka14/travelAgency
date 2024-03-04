#include "travel.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "sortfunktor.h"

Travel::Travel(int eingabeID, int eingabeKID)
    :id(eingabeID), customerId(eingabeKID)
{

}

void Travel::addBooking(shared_ptr<Booking> booking)
{
    travelBookings.push_back(booking);
    myGraph.insertVertex(index, booking);

    if(index>1)
    {
        for(int i=1; i<=index;i++)
        {
            for(int y=0; y<myGraph.getVertexValue(i)->getAnzahlVorganger(); y++)
            {
                for(int z=1; z<=index; z++)
                {
                    if(myGraph.getVertexValue(z)->getID()==myGraph.getVertexValue(i)->getVorganger(y))
                    {
                        myGraph.insertEdge(z, i);
                        break;
                    }
                }
            }
        }
    }

    depthFirstSearch(myGraph);

    for(int i=1; i<=index;i++)
    {
        myGraph.getVertexValue(i)->setEndBearbeitung(myGraph.getEnd(i));
    }
    index++;

    SortFunktor sortFunktor = SortFunktor(SortFunktor::END);

    std::sort(travelBookings.begin(), travelBookings.end(), sortFunktor);



}

int Travel::getID()
{
    return id;
}
string Travel::getStartDate()
{
    int startDate=stoi(travelBookings[0]->getFD());
    for(int i=1;i<travelBookings.size();i++)
    {
        if(stoi(travelBookings[i]->getFD())<startDate)
            startDate=stoi(travelBookings[i]->getFD());
    }
    return to_string(startDate);
}
string Travel::getEndDate()
{
    int endDate=stoi(travelBookings[0]->getTD());
    for(int i=1;i<travelBookings.size();i++)
    {
        if(stoi(travelBookings[i]->getTD())>endDate)
            endDate=stoi(travelBookings[i]->getTD());
    }
    return to_string(endDate);
}
int Travel::getNumberReservations()
{
    return travelBookings.size();
}

int Travel::getReservationId(int reservationNumber)
{
    return travelBookings[reservationNumber]->getID();
}

string Travel::getReservationStartDate(int reservationNumber)
{
    return travelBookings[reservationNumber]->getFD();
}

string Travel::getReservationEndDate(int reservationNumber)
{
    return travelBookings[reservationNumber]->getTD();
}

double Travel::getReservationPreis(int reservationNumber)
{
    return travelBookings[reservationNumber]->getPrice();
}

bool Travel::checkRoundTrip()
{
    string startFlughafen, zielFlughafen;
    shared_ptr<FlightBooking> flightBooking=nullptr;


    for(int i=0; i<travelBookings.size(); i++)
    {
        if((flightBooking=dynamic_pointer_cast<FlightBooking >(travelBookings[i])))
        {
            startFlughafen=flightBooking->getFDe();
            break;
        }
    }
    for(int i=travelBookings.size()-1; i>=0; i--)
    {
        if((flightBooking=dynamic_pointer_cast<FlightBooking >(travelBookings[i])))
        {
            zielFlughafen=flightBooking->getTDe();
            break;
        }
    }

    return startFlughafen==zielFlughafen;
}

bool Travel::checkEnoughHotels()
{
    int fromDate, toDate;
    shared_ptr<FlightBooking> flightBooking=nullptr;
    shared_ptr<HotelBooking> hotelBooking=nullptr;
    int index; // To know from which Booking we gonna start the second Loop

    for(int i=0; i<travelBookings.size(); i++) //To get "TO DATE" of the first booking from type Flight or Hotel
    {
        if((flightBooking=dynamic_pointer_cast<FlightBooking >(travelBookings[i])) )
        {
            toDate=stoi(flightBooking->getTD());
            index=i;
            break;
        }
        else if((hotelBooking=dynamic_pointer_cast<HotelBooking >(travelBookings[i])))
        {
            toDate=stoi(hotelBooking->getTD());
            index=i;
            break;
        }
    }

    for(int i=index+1; i<travelBookings.size(); i++)
    {
        if((flightBooking=dynamic_pointer_cast<FlightBooking >(travelBookings[i])) )
        {
            if((toDate-stoi(flightBooking->getFD()))>=0)
                toDate=stoi(flightBooking->getTD());
            else
                return false;
        }
        else if((hotelBooking=dynamic_pointer_cast<HotelBooking >(travelBookings[i])))
        {
            if((toDate-stoi(hotelBooking->getFD()))>=0)
                toDate=stoi(hotelBooking->getTD());
            else
                return false;
        }
    }

    return true; //The Loop was succesfully executed
}

bool Travel::checkNoUselessHotels()
{
    int fromDate, toDate;
    shared_ptr<FlightBooking> flightBooking=nullptr;
    shared_ptr<HotelBooking> hotelBooking=nullptr;
    int index; // To know from which Booking we gonna start the second Loop

    for(int i=0; i<travelBookings.size(); i++) //To get "TO DATE" of the first booking from type Flight or Hotel
    {
        if((flightBooking=dynamic_pointer_cast<FlightBooking >(travelBookings[i])) )
        {
            toDate=stoi(flightBooking->getTD());
            index=i;
            break;
        }
        else if((hotelBooking=dynamic_pointer_cast<HotelBooking >(travelBookings[i])))
        {
            toDate=stoi(hotelBooking->getTD());
            index=i;
            break;
        }
    }

    for(int i=index+1; i<travelBookings.size(); i++)
    {
        if((flightBooking=dynamic_pointer_cast<FlightBooking >(travelBookings[i])) )
        {
            if((toDate-stoi(flightBooking->getFD()))<=0)
                toDate=stoi(flightBooking->getTD());
            else
                return false;
        }
        else if((hotelBooking=dynamic_pointer_cast<HotelBooking >(travelBookings[i])))
        {
            if((toDate-stoi(hotelBooking->getFD()))<=0)
                toDate=stoi(hotelBooking->getTD());
            else
                return false;
        }
    }

    return true; //The Loop was succesfully executed
}

bool Travel::checkNoUselessRentalCars()
{
    int toDate;
    int index;
    shared_ptr<RentalcarReservation> rentalCarReservation=nullptr;
    shared_ptr<FlightBooking> flightBooking=nullptr;

    for(int i=0; i<travelBookings.size(); i++) //To get "TO DATE" of the first booking from type RentalCar
    {
        if((rentalCarReservation=dynamic_pointer_cast<RentalcarReservation >(travelBookings[i])) )
        {
            toDate=stoi(rentalCarReservation->getTD());
            index=i;
            break;
        }
    }

    for(int i=index+1; i<travelBookings.size(); i++)
    {
        if((rentalCarReservation=dynamic_pointer_cast<RentalcarReservation >(travelBookings[i])) )
        {
            if((toDate-stoi(rentalCarReservation->getFD()))<=0)
                toDate=stoi(rentalCarReservation->getTD());
            else
                return false;
        }
        else if((flightBooking=dynamic_pointer_cast<FlightBooking >(travelBookings[i])) )
        {
            if((toDate-stoi(flightBooking->getFD()))<=0)
                toDate=stoi(flightBooking->getTD());
            else
                return false;
        }
    }

    return true; //The Loop was succesfully executed
}



















