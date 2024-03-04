#ifndef TEST_H
#define TEST_H

#include "travelagency.h";
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Test;
}

class Test : public QDialog
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();
    void tests(shared_ptr<TravelAgency> myAgency);
    string relativenAbstand(shared_ptr<TravelAgency> myAgency);
    QString getCustomerName();

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::Test *ui;
    QString CustomerName;
};

#endif // TEST_H
