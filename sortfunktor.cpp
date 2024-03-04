#include "sortfunktor.h"

SortFunktor::SortFunktor(SortFunktor::SortierParameter parameter)
    :sortierParameter(parameter)
{

}

bool SortFunktor::operator()(shared_ptr<Booking> booking1, shared_ptr<Booking> booking2){
    if (sortierParameter == PRICE)
        return booking1->getPrice() < booking2->getPrice();
    else if (sortierParameter == ID)
        return booking1->getID() < booking2->getID();
    else if (sortierParameter == FROMDATE)
        return booking1->getFD() < booking2->getFD();
    else if (sortierParameter == TODATE)
        return booking1->getTD() < booking2->getTD();
    else if (sortierParameter == END)
        return booking1->getEndBearbeitung() > booking2->getEndBearbeitung();
    else
        return false;
}

bool SortFunktor::operator()(shared_ptr<Customer> customer1, shared_ptr<Customer> customer2)
{
    return customer1->getAbstand() < customer2->getAbstand();
}
