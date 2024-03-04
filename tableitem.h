#ifndef TABLEITEM_H
#define TABLEITEM_H


#include <QTableWidgetItem>

class tableitem : public QTableWidgetItem
{

public:
    tableitem();
    tableitem(const QString item):QTableWidgetItem(item){}
    bool operator <(const QTableWidgetItem &other )const
    {
        QString str1 = text();
        QString str2 = other.text();

        return str1.toDouble() < str2.toDouble();
    }
};
#endif // TABLEITEM_H
