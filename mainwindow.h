#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "travelagency.h"
#include "test.h"
#include <QMainWindow>
#include <QInputDialog>
#include <QString>
#include <QTableWidgetItem>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(shared_ptr<TravelAgency> travelAgency, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_tableWidget_2_cellDoubleClicked(int row, int column);

    void on_pushButton_3_clicked();

    void on_dateEdit_f_editingFinished();

    void on_dateEdit_vonH_editingFinished();

    void on_dateEdit_bisH_editingFinished();

    void on_dateEdit_vonC_editingFinished();

    void on_dateEdit_bisC_editingFinished();

    void on_pushButton_4_clicked();


    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    shared_ptr<TravelAgency> myAgency;
    int eingabeID;
    int buchungID;
};
#endif // MAINWINDOW_H
