#include "ticket.h"

ticket::ticket(int id,int price)
{
    this->id=id;
    this->price=price;
}

int ticket::get_id()
{
    return id;
}

int ticket::get_price()
{
    return price;
}
