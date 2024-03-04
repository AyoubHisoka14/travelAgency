#ifndef SORTFUNKTOR_H
#define SORTFUNKTOR_H

#include "booking.h"
#include "customer.h"
#include <memory>

class SortFunktor
{
public:
    enum SortierParameter{
        ID=0, PRICE=1, FROMDATE=2, TODATE=3, END=4
    };
    SortFunktor(SortFunktor::SortierParameter parameter = ID);
    bool operator()(shared_ptr<Booking> booking1, shared_ptr<Booking> booking2);
    bool operator()(shared_ptr<Customer> customer1, shared_ptr<Customer> customer2);
private:
   SortFunktor::SortierParameter sortierParameter = ID;
};

#endif // SORTFUNKTOR_H
