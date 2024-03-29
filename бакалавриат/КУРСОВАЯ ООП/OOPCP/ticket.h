#ifndef TICKET_H
#define TICKET_H


class ticket
{
    int id;
    int price;
public:
    ticket(int,int);
    int get_id();
    int get_price();
};

#endif // TICKET_H
