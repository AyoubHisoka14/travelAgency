#include "travelagency.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"

TravelAgency::TravelAgency()
{
    ifstream datei;
    datei.open("bookings5.txt", ios::in);

    if (!datei) { // Fehlerabfrage
           cout<<"Nicht gefunden";
           exit(0);

       }

    stringstream lineStream;
    string stp1 , stp2 , stp3 , stp4 , stp5 , stp6 , stp7 , stp8, stp9, stp10, stp11, stp12, stp13, stp14;


    while (getline(datei, line)){
        if (line.empty()){ // si la ligne est vide (la fin du fichier)
            break;
        }
        stp12="0",stp13="0", stp14="0";
        lineStream.clear();
        lineStream<<line;
        getline(lineStream , stp1 , '|'); // type R , F, H
        getline(lineStream , stp2 , '|'); // ID
        getline(lineStream , stp3 , '|'); // price
        getline(lineStream , stp4 , '|'); //fromDate
        getline(lineStream , stp5 , '|'); //toDate
        getline(lineStream , stp6 , '|'); //ID der Reise
        getline(lineStream , stp7 , '|'); //ID des Kunden
        getline(lineStream , stp8 , ' '); //Vorname des Kunden
        getline(lineStream , stp9 , '|'); //Nachname des Kunden
        getline(lineStream , stp10 , '|'); //fromFlug or hotel or pickuplocation
        getline(lineStream , stp11 , '|'); //zielflug or townHotel or returnLocation
        getline(lineStream , stp12 , '|'); //flugLinie or CompanyCar
        getline(lineStream , stp13 , '|'); //Vorgänger 1
        getline(lineStream , stp14 , '|'); //Vorgänger 2



        int id = stoi(stp2); //convertir de string  vers int
        double preis = stof(stp3); //convetir de string vers double

        if(stp12=="Avis")
            company_Avis++;
        if(stp12=="United Airlines")
            united_Airlines++;
        if(preis>=1000)
            buchung_1000++;


        if(stp1 == "F"){
           shared_ptr<FlightBooking> fb = make_shared<FlightBooking>('F',id, preis, stp4, stp5, stp10, stp11 , stp12) ;

           if(stp13!="0")
               fb->setVorganger(stoi(stp13));
           if(stp14!="0")
               fb->setVorganger(stoi(stp14));

           bookings.push_back(fb);
           flightBookings.push_back(fb);
           gesamtWert += fb->getPrice();
           F++;

           bool gefunden=false;
           for(int i=0; i<allTravels.size(); i++) //hier wird geprüft, ob wir diese Reise schon haben
           {
               if(allTravels[i]->getID()==stoi(stp6))
               {
                    allTravels[i]->addBooking(fb);
                    gefunden=true;

                    if(stoi(stp6)==17)
                        buchungen++;

                    break;
               }
           }
           if(!gefunden)
           {
               shared_ptr<Travel> travel=  make_shared<Travel>(stoi(stp6), stoi(stp7));
               travel->addBooking(fb);
               allTravels.push_back(travel);

               if(stoi(stp7)==1)
                   reisen++;
               if(stoi(stp6)==17)
                   buchungen++;
           }

        }

        if(stp1 == "H"){
           shared_ptr<HotelBooking>hb = make_shared< HotelBooking>('H',id, preis, stp4, stp5, stp10, stp11) ;

           if(stp12!="0")
               hb->setVorganger(stoi(stp12));
           if(stp13!="0")
               hb->setVorganger(stoi(stp13));

           bookings.push_back(hb);
           hotelBookings.push_back(hb);
           gesamtWert += hb->getPrice();
           H++;

           bool gefunden=false;
           for(int i=0; i<allTravels.size(); i++)  //hier wird geprüft, ob wir diese Reise schon haben
           {
               if(allTravels[i]->getID()==stoi(stp6))
               {
                    allTravels[i]->addBooking(hb);
                    gefunden=true;

                    if(stoi(stp6)==17)
                        buchungen++;

                    break;
               }
           }
           if(!gefunden)
           {
               shared_ptr<Travel> travel= make_shared<Travel>(stoi(stp6), stoi(stp7));
               travel->addBooking(hb);
               allTravels.push_back(travel);

               if(stoi(stp7)==1)
                   reisen++;
               if(stoi(stp6)==17)
                   buchungen++;
           }
        }

        if(stp1 == "R"){
           shared_ptr<RentalcarReservation> cr = make_shared< RentalcarReservation>('R',id, preis, stp4, stp5, stp10, stp11 , stp12) ;

           if(stp13!="0")
               cr->setVorganger(stoi(stp13));
           if(stp14!="0")
               cr->setVorganger(stoi(stp14));

           bookings.push_back(cr);
           carBookings.push_back(cr);
           gesamtWert += cr->getPrice();
           R++;

           bool gefunden=false;
           for(int i=0; i<allTravels.size(); i++)  //hier wird geprüft, ob wir diese Reise schon haben
           {
               if(allTravels[i]->getID()==stoi(stp6))
               {
                    allTravels[i]->addBooking(cr);
                    gefunden=true;

                    if(stoi(stp6)==17)
                        buchungen++;

                    break;
               }
           }
           if(!gefunden)
           {
               shared_ptr<Travel> travel= make_shared< Travel>(stoi(stp6), stoi(stp7));
               travel->addBooking(cr);
               allTravels.push_back(travel);

               if(stoi(stp7)==1)
                   reisen++;
               if(stoi(stp6)==17)
                   buchungen++;
           }
        }

        bool gefunden=false;
        for(int i=0; i<allCustomers.size(); i++)  //hier wird geprüft, ob wir den Kunden schon haben
        {
             if(allCustomers[i]->getID()==stoi(stp7))
             {
                 if(allCustomers[i]->findTravel(stoi(stp6)))
                 {
                     gefunden=true;
                     break;
                 }
                 else
                 {
                     for(int j=0; j<allTravels.size(); j++)
                     {
                         if(allTravels[j]->getID()==stoi(stp6))
                         {
                             allCustomers[i]->addTravel(allTravels[j]);
                             break;
                         }
                     }
                     gefunden=true;
                     break;

                 }
             }
        }
        if(!gefunden)
        {
            shared_ptr<Customer> customer= make_shared<Customer>(stoi(stp7), stp8, stp9);
            for(int j=0; j<allTravels.size(); j++)
            {
                if(allTravels[j]->getID()==stoi(stp6))
                {
                    customer->addTravel(allTravels[j]);
                    break;
                }
            }
            allCustomers.push_back(customer);
        }


    }

}

string TravelAgency::readFile()
{
     return "Es wurden "+to_string(F)+" Flugbuchungen, "+to_string(R)+" MietwagenBuchungen und "+to_string(H)+" Hotelreservierungen im Gesamtwert von "+to_string(gesamtWert)+" Euro eingelesen\n"
             "Es wurden "+to_string(allTravels.size())+"Reisen und "+to_string(allCustomers.size())+" Kunden angelegt\n"
             "Der Kunde mit der ID 1 hat "+to_string(reisen)+" Reisen gebucht\n"
             "Zur Reise mit der ID 17 gehoren "+to_string(buchungen)+" Buchungen\n";
}

bool TravelAgency::findCustomer(int eingabeID)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return true;
    }
    return false;
}

bool TravelAgency::findTravel(int eingabeID)
{
    for(int i=0;i<allTravels.size(); i++)
    {
        if(allTravels[i]->getID()==eingabeID)
            return true;
    }
    return false;
}
string TravelAgency::getStartDate(int eingabeID, int travelNumber)
{
    for(int i=0; i<allCustomers.size(); i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getStartDate(travelNumber);
    }
}
string TravelAgency::getEndDate(int eingabeID, int travelNumber)
{
    for(int i=0; i<allCustomers.size(); i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getEndDate(travelNumber);
    }
}
int TravelAgency::getTravelID(int eingabeID, int travelNumber)
{
    for(int i=0; i<allCustomers.size(); i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getTravelID(travelNumber);
    }
}

string TravelAgency::getCustomerVName(int eingabeID)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getVName();
    }
}
int TravelAgency::getSizeCustomerTravels(int eingabeID)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
        {
            return allCustomers[i]->getSizeTravels();
        }

    }
}
string TravelAgency::getCustomerNName(int eingabeID)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getNName();
    }
}

int TravelAgency::getNumberCustomerReservations(int eingabeID, int travelID)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getNumberTravelReservations(travelID);
    }
}

int TravelAgency::getReservationID(int eingabeID, int travelID, int reservationNumber)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getReservationId(travelID, reservationNumber);
    }
}
int TravelAgency::getReservationID(int index)
{
    return allTravels[index]->getID();
}

string TravelAgency::getReservationStartDate(int eingabeID, int travelID, int reservationNumber)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getReservationStartDate(travelID, reservationNumber);
    }
}

string TravelAgency::getReservationEndDate(int eingabeID, int travelID, int reservationNumber)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getReservationEndDate(travelID, reservationNumber);
    }
}

double TravelAgency::getReservationPreis(int eingabeID, int travelID, int reservationNumber)
{
    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==eingabeID)
            return allCustomers[i]->getReservationPrice(travelID, reservationNumber);
    }
}





char TravelAgency::getTyp(int reservationID)
{
    for(int i=0; i<bookings.size();i++)
    {
        if(bookings[i]->getID()==reservationID)
            return bookings[i]->getTyp();
    }
}
int TravelAgency::getID(int reservationID)
{
    for(int i=0; i<bookings.size();i++)
    {
        if(bookings[i]->getID()==reservationID)
            return bookings[i]->getID();
    }
}
string TravelAgency::getFD(int reservationID)
{
    for(int i=0; i<bookings.size();i++)
    {
        if(bookings[i]->getID()==reservationID)
            return bookings[i]->getFD();
    }
}
string TravelAgency::getTD(int reservationID)
{
    for(int i=0; i<bookings.size();i++)
    {
        if(bookings[i]->getID()==reservationID)
            return bookings[i]->getTD();
    }
}
double TravelAgency::getPrice(int reservationID)
{
    for(int i=0; i<bookings.size();i++)
    {
        if(bookings[i]->getID()==reservationID)
            return bookings[i]->getPrice();
    }
}
string TravelAgency::getFlightFDe(int reseravtionID)
{
    for(int i=0;i<flightBookings.size();i++)
    {
        if(flightBookings[i]->getID()==reseravtionID)
            return flightBookings[i]->getFDe();
    }
}
string TravelAgency::getFlightTDe(int reseravtionID)
{
    for(int i=0;i<flightBookings.size();i++)
    {
        if(flightBookings[i]->getID()==reseravtionID)
            return flightBookings[i]->getTDe();
    }
}
string TravelAgency::getAirline(int reseravtionID)
{
    for(int i=0;i<flightBookings.size();i++)
    {
        if(flightBookings[i]->getID()==reseravtionID)
            return flightBookings[i]->getAirline();
    }
}
string TravelAgency::getHotel(int reseravtionID)
{
    for(int i=0;i<hotelBookings.size();i++)
    {
        if(hotelBookings[i]->getID()==reseravtionID)
            return hotelBookings[i]->getHotel();
    }
}
string TravelAgency::getTown(int reseravtionID)
{
    for(int i=0;i<hotelBookings.size();i++)
    {
        if(hotelBookings[i]->getID()==reseravtionID)
            return hotelBookings[i]->getTown();
    }
}
string TravelAgency::getPL(int reseravtionID)
{
    for(int i=0;i<carBookings.size();i++)
    {
        if(carBookings[i]->getID()==reseravtionID)
            return carBookings[i]->getPL();
    }
}
string TravelAgency::getRL(int reseravtionID)
{
    for(int i=0;i<carBookings.size();i++)
    {
        if(carBookings[i]->getID()==reseravtionID)
            return carBookings[i]->getRL();
    }
}
string TravelAgency::getCompany(int reseravtionID)
{
    for(int i=0;i<carBookings.size();i++)
    {
        if(carBookings[i]->getID()==reseravtionID)
            return carBookings[i]->getCompany();
    }
}


void TravelAgency::setFlightFDe(int reseravtionID,  string eingabe)
{
    for(int i=0;i<flightBookings.size();i++)
    {
        if(flightBookings[i]->getID()==reseravtionID)
            flightBookings[i]->setFDe(eingabe);
    }
}
void TravelAgency::setFlightTDe(int reseravtionID, string eingabe)
{
    for(int i=0;i<flightBookings.size();i++)
    {
        if(flightBookings[i]->getID()==reseravtionID)
             flightBookings[i]->setTDe(eingabe);
    }
}
void TravelAgency::setAirline(int reseravtionID, string eingabe)
{
    for(int i=0;i<flightBookings.size();i++)
    {
        if(flightBookings[i]->getID()==reseravtionID)
             flightBookings[i]->setAirline(eingabe);
    }
}
void TravelAgency::setHotel(int reseravtionID, string eingabe)
{
    for(int i=0;i<hotelBookings.size();i++)
    {
        if(hotelBookings[i]->getID()==reseravtionID)
             hotelBookings[i]->setHotel(eingabe);
    }
}
void TravelAgency::setTown(int reseravtionID, string eingabe)
{
    for(int i=0;i<hotelBookings.size();i++)
    {
        if(hotelBookings[i]->getID()==reseravtionID)
             hotelBookings[i]->setTown(eingabe);
    }
}
void TravelAgency::setPL(int reseravtionID, string eingabe)
{
    for(int i=0;i<carBookings.size();i++)
    {
        if(carBookings[i]->getID()==reseravtionID)
             carBookings[i]->setPL(eingabe);
    }
}
void TravelAgency::setRL(int reseravtionID, string eingabe)
{
    for(int i=0;i<carBookings.size();i++)
    {
        if(carBookings[i]->getID()==reseravtionID)
             carBookings[i]->setRL(eingabe);
    }
}
void TravelAgency::setCompany(int reseravtionID, string eingabe)
{
    for(int i=0;i<carBookings.size();i++)
    {
        if(carBookings[i]->getID()==reseravtionID)
             carBookings[i]->setCompany(eingabe);
    }
}

void TravelAgency::setFD(int reservationID, string eingabe)
{
    for(int i=0;i<bookings.size();i++)
    {
        if(bookings[i]->getID()==reservationID)
            bookings[i]->setFD(eingabe);
    }
}
void TravelAgency::setTD(int reservationID, string eingabe)
{
    for(int i=0;i<bookings.size();i++)
    {
        if(bookings[i]->getID()==reservationID)
            bookings[i]->setTD(eingabe);
    }
}
void TravelAgency::setPrice(int reservationID, double eingabe)
{
    for(int i=0;i<bookings.size();i++)
    {
        if(bookings[i]->getID()==reservationID)
            bookings[i]->setPrice(eingabe);
    }
}
int TravelAgency::getNumberOfReservations()
{
    return allTravels.size();
}

void TravelAgency::json()
{

    QFile file(QString::fromStdString("c:/iatacodes.json"));
     file.open (QIODevice::ReadOnly | QIODevice::Text);
    QString json = file.readAll ();
     file.close ();
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    if(error.error != QJsonParseError::NoError){
     qDebug() << "Fehler beim parsen der JSON Datei" << error.errorString ();
     }

    //QJsonObject jsonObject = document.object();
    QJsonArray jsonArray = document.array();

    for(int i=0; i<jsonArray.count(); i++)
    {
        QJsonObject objekt=jsonArray[i].toObject();

        QString name=objekt.value("name").toString();
        QString country=objekt.value("iso_country").toString();
        QString muni=objekt.value("municipality").toString();
        QString code=objekt.value("iata_code").toString();

        airportMap[code]=Airport{name.toStdString(), country.toStdString(), muni.toStdString(), code.toStdString() };

    }

}

string TravelAgency::getAirportName(QString key)
{
    if(airportMap.find(key)==airportMap.end())
    {
        return "0";
    }
    else
    {
       Airport airport=airportMap[key];
       return airport.name;
    }
}

int TravelAgency::buchungAvis()
{
    return company_Avis;
}

int TravelAgency::buchungUA()
{
    return united_Airlines;
}

int TravelAgency::buchungT()
{
    return buchung_1000;
}

int TravelAgency::saveToJson(int sortierParameter, QString eingabeDatei)
{
    //Zuerst das Sortieren
    SortFunktor sortFunktor = SortFunktor(SortFunktor::ID);
    switch(sortierParameter)
    {
    case 0:  sortFunktor=SortFunktor (SortFunktor::ID); break;
    case 1:  sortFunktor=SortFunktor (SortFunktor::PRICE); break;
    case 2:  sortFunktor=SortFunktor (SortFunktor::FROMDATE); break;
    case 3:  sortFunktor=SortFunktor (SortFunktor::TODATE); break;
    }
    std::sort(bookings.begin(), bookings.end(), sortFunktor);

    //Jetzt alle sortierten Buchungen in einer Json-Datei abspeichern

    shared_ptr<FlightBooking> flightBooking=nullptr;
    shared_ptr<HotelBooking> hotelBooking=nullptr;
    shared_ptr<RentalcarReservation> rentalCarReservation=nullptr;



    QJsonDocument jsonDocument;
    QJsonArray jsonArrayBuchungen;
    QJsonArray jsonArrayFlugBuchungen;
    QJsonArray jsonArrayHotelBuchungen;
    QJsonArray jsonArrayCarBuchungen;

    for (int i=0; i<bookings.size();i++){
        shared_ptr<FlightBooking> flightBooking=nullptr;
        shared_ptr<HotelBooking> hotelBooking=nullptr;
        shared_ptr<RentalcarReservation> rentalCarReservation=nullptr;

        if((flightBooking=dynamic_pointer_cast<FlightBooking >(bookings[i]))){

           QJsonObject jsonObjektFlugBuchung;

           jsonObjektFlugBuchung ["airline"]= QString::fromStdString(flightBooking->getAirline());
           jsonObjektFlugBuchung ["fromDate"]= QString::fromStdString(flightBooking->getFD());
           jsonObjektFlugBuchung ["fromDest"]= QString::fromStdString(flightBooking->getFDe());
           jsonObjektFlugBuchung ["id"]= flightBooking->getID();
           jsonObjektFlugBuchung ["price"]= flightBooking->getPrice();
           jsonObjektFlugBuchung ["toDate"]= QString::fromStdString(flightBooking->getTD());
           jsonObjektFlugBuchung ["toDest"]= QString::fromStdString(flightBooking->getTDe());

           //jsonArrayFlugBuchungen.push_back(jsonObjektFlugBuchung);
           jsonArrayBuchungen.push_back(jsonObjektFlugBuchung);

        }

        else if((hotelBooking=dynamic_pointer_cast<HotelBooking>(bookings[i])))
        {
            QJsonObject jsonObjektHotelBuchung;

            jsonObjektHotelBuchung ["fromDate"]= QString::fromStdString(hotelBooking->getFD());
            jsonObjektHotelBuchung ["hotel"]= QString::fromStdString(hotelBooking->getHotel());
            jsonObjektHotelBuchung ["id"]= hotelBooking->getID();
            jsonObjektHotelBuchung ["price"]= hotelBooking->getPrice();
            jsonObjektHotelBuchung ["toDate"]= QString::fromStdString(hotelBooking->getTD());
            jsonObjektHotelBuchung ["town"]= QString::fromStdString(hotelBooking->getTown());


            //jsonArrayHotelBuchungen.push_back(jsonObjektHotelBuchung);
            jsonArrayBuchungen.push_back(jsonObjektHotelBuchung);
        }

        else if((rentalCarReservation=dynamic_pointer_cast<RentalcarReservation>(bookings[i])))
        {
            QJsonObject jsonObjektCarBuchung;

            jsonObjektCarBuchung ["company"]= QString::fromStdString(rentalCarReservation->getCompany());
            jsonObjektCarBuchung ["fromDate"]= QString::fromStdString(rentalCarReservation->getFD());
            jsonObjektCarBuchung ["id"]= rentalCarReservation->getID();
            jsonObjektCarBuchung ["pickupLocation"]= QString::fromStdString(rentalCarReservation->getPL());
            jsonObjektCarBuchung ["price"]= rentalCarReservation->getPrice();
            jsonObjektCarBuchung ["returnLocation"]= QString::fromStdString(rentalCarReservation->getRL());
            jsonObjektCarBuchung ["toDate"]= QString::fromStdString(rentalCarReservation->getTD());

            //jsonArrayCarBuchungen.push_back(jsonObjektCarBuchung);
            jsonArrayBuchungen.push_back(jsonObjektCarBuchung);
        }

    }

    jsonDocument.setArray(jsonArrayBuchungen);
    QString dateiName=eingabeDatei;
    QFile jsondatei(dateiName);
    if(!jsondatei.open(QIODevice::WriteOnly))
        return 0;
    jsondatei.write(jsonDocument.toJson());


    return 1;


}

int TravelAgency::newCustomer(string vName, string nNAme)
{
    int newID=-1;
    for(int i=0; i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()>newID)
            newID=allCustomers[i]->getID();
    }

    shared_ptr<Customer> customer= make_shared<Customer>(++newID,vName, nNAme);
    allCustomers.push_back(customer);

    return newID;
}

int TravelAgency::newTravel(int customerId)
{
    int newID=-1;
    for(int i=0; i<allTravels.size(); i++)
    {
        if(allTravels[i]->getID()>newID)
            newID=allTravels[i]->getID();
    }

    shared_ptr<Travel> travel= make_shared<Travel>(++newID, customerId);
    allTravels.push_back(travel);

    for(int i=0;i<allCustomers.size();i++)
    {
        if(allCustomers[i]->getID()==customerId)
        {
            allCustomers[i]->addTravel(travel);
            break;
        }
    }

    return newID;

 }

int TravelAgency::newBooking(int travelId, char eingabeTyp, double eingabeP, string eingabeFD, string eingabeTD, string eingabe1, string eingabe2, int vorganger1, int vorganger2, string eingabe3)
{
    int newID=-1;
    for(int i=0;i<bookings.size();i++)
    {
        if(bookings[i]->getID()>newID)
            newID=bookings[i]->getID();
    }

    for(int i=0; i<allTravels.size(); i++)
    {
        if(allTravels[i]->getID()==travelId)
        {
            if(eingabeTyp=='F')
            {
                shared_ptr<FlightBooking> flight = make_shared<FlightBooking> (eingabeTyp, ++newID, eingabeP, eingabeFD, eingabeTD, eingabe1, eingabe2, eingabe3);
                if(vorganger1!=0)
                    flight->setVorganger(vorganger1);
                if(vorganger2!=0)
                    flight->setVorganger(vorganger2);
                allTravels[i]->addBooking(flight);
                bookings.push_back(flight);
                flightBookings.push_back(flight);
                break;
            }
            else if(eingabeTyp=='H')
            {
                shared_ptr<HotelBooking> hotel = make_shared<HotelBooking> (eingabeTyp, ++newID, eingabeP, eingabeFD, eingabeTD, eingabe1, eingabe2);
                if(vorganger1!=0)
                    hotel->setVorganger(vorganger1);
                if(vorganger2!=0)
                    hotel->setVorganger(vorganger2);
                allTravels[i]->addBooking(hotel);
                bookings.push_back(hotel);
                hotelBookings.push_back(hotel);
                break;
            }
            else if(eingabeTyp=='R')
            {
                shared_ptr<RentalcarReservation> car = make_shared<RentalcarReservation> (eingabeTyp, ++newID, eingabeP, eingabeFD, eingabeTD, eingabe1, eingabe2, eingabe3);
                if(vorganger1!=0)
                    car->setVorganger(vorganger1);
                if(vorganger2!=0)
                    car->setVorganger(vorganger2);
                allTravels[i]->addBooking(car);
                bookings.push_back(car);
                carBookings.push_back(car);
                break;
            }

        }
    }

    return newID;
}

bool TravelAgency::checkRoundTrip(int travelID)
{
    return allTravels[travelID]->checkRoundTrip();
}

bool TravelAgency::checkEnoughHotels(int travelID)
{
    return allTravels[travelID]->checkEnoughHotels();
}

bool TravelAgency::checkNoUselessHotels(int travelID)
{
    return allTravels[travelID]->checkNoUselessHotels();
}

bool TravelAgency::checkNoUselessRentalCars(int travelID)
{
    return allTravels[travelID]->checkNoUselessRentalCars();
}

void TravelAgency::relativenAbstand(string string2)
{
    string string1;

    for(int i=0; i<allCustomers.size(); i++)
    {
        string1=allCustomers[i]->getNName();
        int array[string1.size()+1][string2.size()+1];

        for(int y=0; y<string1.size()+1; y++)
        {
            for(int z=0; z<string2.size()+1; z++)
            {
                if(y==0 && z==0)
                    array[y][z]=0;
                else if(z==0)
                    array[y][z]=y;
                else if(y==0)
                    array[y][z]=z;
                else
                {
                    if(string1[y]==string2[z])
                        array[y][z]=array[y-1][z-1];
                    else
                    {
                        if((array[y-1][z-1]+1)<(array[y][z-1]+1) && (array[y-1][z-1]+1)<array[y-1][z]+1)
                            array[y][z]=array[y-1][z-1]+1;
                        else if((array[y][z-1]+1)<(array[y-1][z-1]+1) && (array[y][z-1]+1)<(array[y-1][z]+1))
                            array[y][z]=array[y][z-1]+1;
                        else
                            array[y][z]=array[y-1][z]+1;
                    }

                }
            }
        }
        double x=array[string1.size()][string2.size()];
        double abstand=x/(string1.size()+string2.size());
        allCustomers[i]->setAbstand(abstand);
    }

    SortFunktor sortFunktor = SortFunktor(SortFunktor::ID);

    std::sort(allCustomers.begin(), allCustomers.end(), sortFunktor);
}

int TravelAgency::getNumberOfCustomers()
{
    return allCustomers.size();
}

double TravelAgency::getCustomerAbstand(int index)
{
    return allCustomers[index]->getAbstand();
}

string TravelAgency::getCustomerLastName(int index)
{
    return allCustomers[index]->getNName();
}

int TravelAgency::getCustomerIdByName(string name)
{
    for(int i=0; i<allCustomers.size(); i++)
    {
        if(allCustomers[i]->getNName()==name)
            return allCustomers[i]->getID();
    }
}
