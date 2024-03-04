#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    shared_ptr<TravelAgency> travelAgency = make_shared<TravelAgency>();
    MainWindow w(travelAgency);
    //Test test;
    //QTest::qExec(&test);
    w.show();
    return a.exec();
}
