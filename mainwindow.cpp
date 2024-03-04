#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(shared_ptr<TravelAgency> travelAgency, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
    , myAgency(travelAgency)

{
    ui->setupUi(this);
    myAgency->json();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString output=QString::fromStdString(myAgency->readFile());
    QMessageBox msgBox;
    msgBox.setWindowTitle("Datei erfolgreich eingelesen");
    msgBox.setText(output);
    msgBox.exec();

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    ui->tableWidget_2->setColumnCount(0);
    ui->tableWidget_2->setRowCount(0);

    int sortierKriterium;
    QMessageBox box;
            box.setWindowTitle("Find Customer");
            box.setText("Suchkriterium auswahlen");

            QPushButton *idBut = box.addButton(tr("ID"), QMessageBox::YesRole);
            QPushButton *nameBut = box.addButton(tr("Name"),QMessageBox::YesRole);

            box.exec();
            if (box.clickedButton() == idBut)
            {
                int id=QInputDialog::getInt(this, "Customer Finden", "Customer-ID");

                if(myAgency->findCustomer(id))
                {
                    QString output;
                    output=QString::fromStdString(to_string(id));
                    ui->lineEdit_idCu->setText(output);
                    output=QString::fromStdString(myAgency->getCustomerVName(id));
                    ui->lineEdit_VN->setText(output);
                    output=QString::fromStdString(myAgency->getCustomerNName(id));
                    ui->lineEdit_NN->setText(output);
                    ui->tabWidget->setCurrentWidget(ui->tab_cunstomer);


                    eingabeID=id;
                    ui->tableWidget->setColumnCount(3);
                    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Startdatum", "Enddatum"});

                    for(int i=0;i<myAgency->getSizeCustomerTravels(id);i++)
                    {
                        ui->tableWidget->insertRow ( ui->tableWidget->rowCount());

                        QString output;
                        output=QString::fromStdString(to_string(myAgency->getTravelID(id, i)));
                        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 0, new tableitem(output));

                        output=QString::fromStdString(myAgency->getStartDate(id, i));
                        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 1, new tableitem(output));

                        output=QString::fromStdString(myAgency->getEndDate(id, i));
                        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 2, new tableitem(output));

                    }
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Fehler");
                    msgBox.setText("ID Nicht Gefunden");
                    msgBox.exec();


                }
            }
            else
            {
                QString name=QInputDialog::getText(this, "Find Customer", "Customer Last-Name");
                myAgency->relativenAbstand(name.toStdString());
                Test test;
                test.relativenAbstand(myAgency);
                test.setModal(true);
                test.exec();

                string customerName=test.getCustomerName().toStdString();
                int id=myAgency->getCustomerIdByName(customerName);

                QString output;
                output=QString::fromStdString(to_string(id));
                ui->lineEdit_idCu->setText(output);
                output=QString::fromStdString(myAgency->getCustomerVName(id));
                ui->lineEdit_VN->setText(output);
                output=QString::fromStdString(myAgency->getCustomerNName(id));
                ui->lineEdit_NN->setText(output);
                ui->tabWidget->setCurrentWidget(ui->tab_cunstomer);


                eingabeID=id;
                ui->tableWidget->setColumnCount(3);
                ui->tableWidget->setHorizontalHeaderLabels({"ID", "Startdatum", "Enddatum"});

                for(int i=0;i<myAgency->getSizeCustomerTravels(id);i++)
                {
                    ui->tableWidget->insertRow ( ui->tableWidget->rowCount());

                    QString output;
                    output=QString::fromStdString(to_string(myAgency->getTravelID(id, i)));
                    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 0, new tableitem(output));

                    output=QString::fromStdString(myAgency->getStartDate(id, i));
                    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 1, new tableitem(output));

                    output=QString::fromStdString(myAgency->getEndDate(id, i));
                    ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 2, new tableitem(output));

                }
            }











    //QString output=QString::fromStdString(to_string(2));

    //ui->tableWidget->clear();
    //ui->tableWidget->setRowCount(5);
    //ui->tableWidget->setColumnCount(5);
    //for (auto r=0; r<5; r++)
    {
        //ui->tableWidget->insertRow ( ui->tableWidget->rowCount() );
         //for (auto c=0; c<3; c++)
              //ui->tableWidget->setItem( r, c, new QTableWidgetItem(output));
    }


}


void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{


     row = ui->tableWidget->currentRow();
     QTableWidgetItem *firstColumnInRow = ui->tableWidget->item(row, 0);
     QString text = firstColumnInRow->text();
     string travelID=text.toStdString();

     ui->tableWidget_2->setColumnCount(0);
     ui->tableWidget_2->setRowCount(0);

     ui->tableWidget_2->setColumnCount(4);
     ui->tableWidget_2->setHorizontalHeaderLabels({"ID", "Startdatum", "Enddatum", "Preis"});

     for(int i=0;i<myAgency->getNumberCustomerReservations(eingabeID, stoi(travelID));i++)
     {
         ui->tableWidget_2->insertRow ( ui->tableWidget_2->rowCount());

         QString output;
         output=QString::fromStdString(to_string(myAgency->getReservationID(eingabeID, stoi(travelID), i)));
         ui->tableWidget_2->setItem( ui->tableWidget_2->rowCount()-1, 0, new tableitem(output));

         output=QString::fromStdString(myAgency->getReservationStartDate(eingabeID, stoi(travelID), i));
         ui->tableWidget_2->setItem( ui->tableWidget_2->rowCount()-1, 1, new tableitem(output));

         output=QString::fromStdString(myAgency->getReservationEndDate(eingabeID, stoi(travelID), i));
         ui->tableWidget_2->setItem( ui->tableWidget_2->rowCount()-1, 2, new tableitem(output));

         output=QString::fromStdString(to_string(myAgency->getReservationPreis(eingabeID, stoi(travelID), i)));
         ui->tableWidget_2->setItem( ui->tableWidget_2->rowCount()-1, 3, new tableitem(output));
     }


}


void MainWindow::on_tableWidget_2_cellDoubleClicked(int row, int column)
{
    row = ui->tableWidget_2->currentRow();
    QTableWidgetItem *firstColumnInRow = ui->tableWidget_2->item(row, 0);
    QString text = firstColumnInRow->text();
    string ID=text.toStdString();
    int reseravationID=stoi(ID);
    buchungID=reseravationID;

    QString output,output2;
    if(myAgency->getTyp(reseravationID)=='F')
    {
        output=QString::fromStdString(to_string(myAgency->getID(reseravationID)));
        ui->lineEdit_idF->setText(output);

        output=QString::fromStdString(myAgency->getFD(reseravationID));
        QDate Date = QDate::fromString(output,"yyyyMMdd");
        ui->dateEdit_f->setDate(Date);

        output=QString::fromStdString(myAgency->getFlightFDe(reseravationID));
        ui->lineEdit_FDF->setText(output);

        output2=QString::fromStdString(myAgency->getAirportName(output));
        ui->lineEdit_fname1->setStyleSheet("color: black;");
        ui->lineEdit_fname1->setText(output2);

        output=QString::fromStdString(myAgency->getFlightTDe(reseravationID));
        ui->lineEdit_TDF->setText(output);

        output2=QString::fromStdString(myAgency->getAirportName(output));
        ui->lineEdit_fname2->setStyleSheet("color: black;");
        ui->lineEdit_fname2->setText(output2);

        output=QString::fromStdString(myAgency->getAirline(reseravationID));
        ui->lineEdit_airline->setText(output);

        output=QString::fromStdString(to_string(myAgency->getPrice(reseravationID)));
        ui->lineEdit_preisF->setText(output);

        ui->tabWidget->setCurrentWidget(ui->tab_flight);
    }
    else if(myAgency->getTyp(reseravationID)=='H')
    {
        output=QString::fromStdString(to_string(myAgency->getID(reseravationID)));
        ui->lineEdit_idH->setText(output);

        output=QString::fromStdString(myAgency->getFD(reseravationID));
        QDate Date1 = QDate::fromString(output,"yyyyMMdd");
        ui->dateEdit_vonH->setDate(Date1);

        output=QString::fromStdString(myAgency->getTD(reseravationID));
        QDate Date2 = QDate::fromString(output,"yyyyMMdd");
        ui->dateEdit_bisH->setDate(Date2);

        output=QString::fromStdString(myAgency->getHotel(reseravationID));
        ui->lineEdit_hotel->setText(output);

        output=QString::fromStdString(myAgency->getTown(reseravationID));
        ui->lineEdit_city->setText(output);


        output=QString::fromStdString(to_string(myAgency->getPrice(reseravationID)));
        ui->lineEdit_preisH->setText(output);

        ui->tabWidget->setCurrentWidget(ui->tab_hotel);

    }
    else if(myAgency->getTyp(reseravationID)=='R')
    {
        output=QString::fromStdString(to_string(myAgency->getID(reseravationID)));
        ui->lineEdit_idC->setText(output);

        output=QString::fromStdString(myAgency->getFD(reseravationID));
        QDate Date1 = QDate::fromString(output,"yyyyMMdd");
        ui->dateEdit_vonC->setDate(Date1);

        output=QString::fromStdString(myAgency->getTD(reseravationID));
        QDate Date2 = QDate::fromString(output,"yyyyMMdd");
        ui->dateEdit_bisC->setDate(Date2);

        output=QString::fromStdString(myAgency->getPL(reseravationID));
        ui->lineEdit_PU->setText(output);

        output=QString::fromStdString(myAgency->getRL(reseravationID));
        ui->lineEdit_R->setText(output);

        output=QString::fromStdString(myAgency->getCompany(reseravationID));
        ui->lineEdit_company->setText(output);

        output=QString::fromStdString(to_string(myAgency->getPrice(reseravationID)));
        ui->lineEdit_preisC->setText(output);

        ui->tabWidget->setCurrentWidget(ui->tab_car);
    }

}




void MainWindow::on_pushButton_3_clicked()
{
    bool j=ui->lineEdit_idF->isModified();
    QDate x=ui->dateEdit_f->date();
    QString y=x.toString("yyyyMMdd");

    QString text;
    QDate date;

    bool modified=ui->lineEdit_FDF->isModified();
    if(modified)
    {
        text=ui->lineEdit_FDF->text();
        if(myAgency->getAirportName(text)=="0")
        {
            ui->lineEdit_fname1->setStyleSheet("color: red;");
            ui->lineEdit_fname1->setText("Iata-Code not found");
        }
        else
        {
            myAgency->setFlightFDe(buchungID, text.toStdString());
        }
    }
    modified=ui->lineEdit_TDF->isModified();
    if(modified)
    {
        text=ui->lineEdit_TDF->text();
        if(myAgency->getAirportName(text)=="0")
        {
            ui->lineEdit_fname2->setStyleSheet("color: red;");
            ui->lineEdit_fname2->setText("Iata-Code not found");
        }
        else
        {
            myAgency->setFlightTDe(buchungID, text.toStdString());
        }
    }
    modified=ui->lineEdit_airline->isModified();
    if(modified)
    {
        text=ui->lineEdit_airline->text();
        myAgency->setAirline(buchungID, text.toStdString());
    }
    modified=ui->lineEdit_preisF->isModified();
    if(modified)
    {
        text=ui->lineEdit_preisF->text();
        myAgency->setPrice(buchungID, stof(text.toStdString()));
    }

    modified=ui->lineEdit_hotel->isModified();
    if(modified)
    {
        text=ui->lineEdit_hotel->text();
        myAgency->setHotel(buchungID, text.toStdString());
    }
    modified=ui->lineEdit_city->isModified();
    if(modified)
    {
        text=ui->lineEdit_city->text();
        myAgency->setTown(buchungID, text.toStdString());
    }
    modified=ui->lineEdit_preisH->isModified();
    if(modified)
    {
        text=ui->lineEdit_preisH->text();
        myAgency->setPrice(buchungID, stof(text.toStdString()));
    }

    modified=ui->lineEdit_PU->isModified();
    if(modified)
    {
        text=ui->lineEdit_PU->text();
        myAgency->setPL(buchungID, text.toStdString());
    }
    modified=ui->lineEdit_R->isModified();
    if(modified)
    {
        text=ui->lineEdit_R->text();
        myAgency->setRL(buchungID, text.toStdString());
    }
    modified=ui->lineEdit_company->isModified();
    if(modified)
    {
        text=ui->lineEdit_company->text();
        myAgency->setCompany(buchungID, text.toStdString());
    }
    modified=ui->lineEdit_preisC->isModified();
    if(modified)
    {
        text=ui->lineEdit_preisC->text();
        myAgency->setPrice(buchungID, stof(text.toStdString()));
    }
}


void MainWindow::on_dateEdit_f_editingFinished()
{
    QString text;
    QDate date;
    date=ui->dateEdit_f->date();
    text=date.toString("yyyyMMdd");
    myAgency->setFD(buchungID,text.toStdString());
    myAgency->setTD(buchungID,text.toStdString());
}


void MainWindow::on_dateEdit_vonH_editingFinished()
{
    QString text;
    QDate date;
    date=ui->dateEdit_vonH->date();
    text=date.toString("yyyyMMdd");
    myAgency->setFD(buchungID,text.toStdString());
}


void MainWindow::on_dateEdit_bisH_editingFinished()
{
    QString text;
    QDate date;
    date=ui->dateEdit_bisH->date();
    text=date.toString("yyyyMMdd");
    myAgency->setTD(buchungID,text.toStdString());
}


void MainWindow::on_dateEdit_vonC_editingFinished()
{
    QString text;
    QDate date;
    date=ui->dateEdit_vonC->date();
    text=date.toString("yyyyMMdd");
    myAgency->setFD(buchungID,text.toStdString());
}


void MainWindow::on_dateEdit_bisC_editingFinished()
{
    QString text;
    QDate date;
    date=ui->dateEdit_bisC->date();
    text=date.toString("yyyyMMdd");
    myAgency->setTD(buchungID,text.toStdString());
}




void MainWindow::on_pushButton_4_clicked()
{
    int sortierKriterium;
    QMessageBox box;
            box.setWindowTitle("Sortieren");
            box.setText("Sortierenkriterium auswahlen");

            QPushButton *idBtn = box.addButton(tr("ID"), QMessageBox::YesRole);
            QPushButton *priceBut = box.addButton(tr("Price"),QMessageBox::YesRole);
            QPushButton *fdBut = box.addButton(tr("fromDate"),QMessageBox::YesRole);
            QPushButton *tdBut = box.addButton(tr("toDate"),QMessageBox::YesRole);

            box.exec();
            if (box.clickedButton() == idBtn)
                sortierKriterium=0;
            else if (box.clickedButton() == priceBut)
                sortierKriterium=1;
            else if (box.clickedButton() == fdBut)
                sortierKriterium=2;
            else
                sortierKriterium=3;


    QString file_name=QFileDialog::getOpenFileName(this,"Open File","C:/");


    bool x=myAgency->saveToJson(sortierKriterium, file_name);

    if(x)
    {
        QMessageBox::information(this, "Datei wurde erfolgreich eingelesen", "Datei erfolgreich erstellt");
    }
    else
    {
        QMessageBox::warning(this,"Fehler", "Es gab einen Fehler" );
    }

}



void MainWindow::on_pushButton_5_clicked()
{
    QString vName=QInputDialog::getText(this, "New Customer", "Customer-First Name");
    QString nName=QInputDialog::getText(this, "New Customer", "Customer-Last Name");

    if(vName.isEmpty() || nName.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "You did not enter your full Name");
    }
    else
    {
        string vN=vName.toStdString();
        string nN=nName.toStdString();

        int newID=myAgency->newCustomer(vN, nN);
        QMessageBox::information(this, "New Customer", "New Customer was added with the ID : "+QString::number(newID));
    }

}


void MainWindow::on_pushButton_6_clicked()
{
    bool customerFound=false,travelFound=false;
    int travelId;
    int newBookingid;

    QMessageBox msgBox;
    msgBox.setWindowTitle("New Travel");
    msgBox.setText("Do you wanna add a new Travel");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes)
    {
      int customerID=QInputDialog::getInt(this, "Customer", "Customer-ID");
      customerFound=myAgency->findCustomer(customerID);

      if(customerFound)
      {
          travelId=myAgency->newTravel(customerID);
      }
      else
      {
          QMessageBox::warning(this, "Warning", "Customer not found");
      }
    }
    else
    {
      travelId=QInputDialog::getInt(this, "Travel", "Travel-ID");
      travelFound=myAgency->findTravel(travelId);

      if(!travelFound)
      {
        QMessageBox::warning(this, "Warning", "Travel not found");
      }

    }

    if(customerFound || travelFound)
    {
        char typ;
                  QMessageBox box;
                  box.setWindowTitle("New Booking");
                  box.setText("What is the type of the new Booking");

                  QPushButton *flight = box.addButton(tr("Flight"), QMessageBox::YesRole);
                  QPushButton *hotel = box.addButton(tr("Hotel"),QMessageBox::YesRole);
                  QPushButton *car = box.addButton(tr("Car Reservation"),QMessageBox::YesRole);

                  box.exec();
                  if (box.clickedButton() == flight)
                      typ='F';
                  else if (box.clickedButton() == hotel)
                      typ='H';
                  else
                      typ='R';

                  if(typ=='F')
                  {
                      double price=QInputDialog::getDouble(this, "New Booking", "Price");
                      QString FD=QInputDialog::getText(this, "New Booking", "From Date in the form yyyyMMdd");
                      QString TD=QInputDialog::getText(this, "New Booking", "To Date in the form yyyyMMdd");
                      QString FDe=QInputDialog::getText(this, "New Booking", "From Destination");
                      QString TDe=QInputDialog::getText(this, "New Booking", "To Destination");
                      QString airline=QInputDialog::getText(this, "New Booking", "Airline");
                      int vorganger1=QInputDialog::getInt(this, "New Booking", "Vorganger 1");
                      int vorganger2=QInputDialog::getInt(this, "New Booking", "Vorganger 2");

                      newBookingid=myAgency->newBooking(travelId, typ, price, FD.toStdString(), TD.toStdString(), FDe.toStdString(), TDe.toStdString(),vorganger1, vorganger2, airline.toStdString());
                  }
                  else if(typ=='H')
                  {
                      double price=QInputDialog::getDouble(this, "New Booking", "Price");
                      QString FD=QInputDialog::getText(this, "New Booking", "From Date in the form yyyyMMdd");
                      QString TD=QInputDialog::getText(this, "New Booking", "To Date in the form yyyyMMdd");
                      QString hotel=QInputDialog::getText(this, "New Booking", "Hotel");
                      QString town=QInputDialog::getText(this, "New Booking", "Town");
                      int vorganger1=QInputDialog::getInt(this, "New Booking", "Vorganger 1");
                      int vorganger2=QInputDialog::getInt(this, "New Booking", "Vorganger 2");

                      newBookingid=myAgency->newBooking(travelId, typ, price, FD.toStdString(), TD.toStdString(), hotel.toStdString(), town.toStdString(), vorganger1, vorganger2);
                  }
                  else
                  {
                      double price=QInputDialog::getDouble(this, "New Booking", "Price");
                      QString FD=QInputDialog::getText(this, "New Booking", "From Date in the form yyyyMMdd");
                      QString TD=QInputDialog::getText(this, "New Booking", "To Date in the form yyyyMMdd");
                      QString FDe=QInputDialog::getText(this, "New Booking", "Pick-Up Location");
                      QString TDe=QInputDialog::getText(this, "New Booking", "Return Location");
                      QString company=QInputDialog::getText(this, "New Booking", "Company");
                      int vorganger1=QInputDialog::getInt(this, "New Booking", "Vorganger 1");
                      int vorganger2=QInputDialog::getInt(this, "New Booking", "Vorganger 2");

                      newBookingid=myAgency->newBooking(travelId, typ, price, FD.toStdString(), TD.toStdString(), FDe.toStdString(), TDe.toStdString(),vorganger1, vorganger2, company.toStdString());
                  }


                  if(customerFound)
                      QMessageBox::information(this, "Information", "New Travel id: "+QString::number(travelId)+" and new Booking id: "+QString::number(newBookingid)+" were added");
                  else if(travelFound)
                      QMessageBox::information(this, "Information", "New Booking id: "+QString::number(newBookingid)+" was added");


    }
}


void MainWindow::on_pushButton_7_clicked()
{
    Test test;
    test.tests(myAgency);
    test.setModal(true);
    test.exec();

}

