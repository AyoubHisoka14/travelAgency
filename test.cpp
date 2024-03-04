#include "test.h"
#include "ui_test.h"

Test::Test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);
}

Test::~Test()
{
    delete ui;
}

void Test::tests(shared_ptr<TravelAgency> myAgency)
{
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"Reise", "Fehlendes Hotel", "Uberflussiges Hotel","Uberflussiger Mietwagen", "Kein Roundtrip"});

    for(int i=0;i<myAgency->getNumberOfReservations();i++)
    {
        ui->tableWidget->insertRow ( ui->tableWidget->rowCount());


        QString output;
        output=QString::fromStdString(to_string(myAgency->getReservationID(i)));
        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(output));

        if(myAgency->checkEnoughHotels(i))
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem("✅"));
        else
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem("❌"));

        if(myAgency->checkNoUselessHotels(i))
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem("✅"));
        else
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem("❌"));

        if(myAgency->checkNoUselessRentalCars(i))
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem("✅"));
        else
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem("❌"));

        if(myAgency->checkRoundTrip(i))
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem("✅"));
        else
            ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem("❌"));

    }
}

string Test::relativenAbstand(shared_ptr<TravelAgency> myAgency)
{
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"Name", "Relativen Abstand"});

    for(int i=0; i<myAgency->getNumberOfCustomers(); i++)
    {
        ui->tableWidget->insertRow ( ui->tableWidget->rowCount());

        QString output;

        output=QString::fromStdString(myAgency->getCustomerLastName(i));
        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(output));

        output=QString::fromStdString(to_string(myAgency->getCustomerAbstand(i)));
        ui->tableWidget->setItem( ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(output));

    }
    return "A";

}

void Test::on_tableWidget_cellDoubleClicked(int row, int column)
{
    row = ui->tableWidget->currentRow();
    QTableWidgetItem *firstColumnInRow = ui->tableWidget->item(row, 0);
    CustomerName = firstColumnInRow->text();
    this->close();
}

QString Test::getCustomerName()
{
    return CustomerName;
}
