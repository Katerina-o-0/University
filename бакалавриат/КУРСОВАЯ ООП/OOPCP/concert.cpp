#include "concert.h"

concert::concert(QString idc,QString nameconcert,QString pl, int place, int price)
{

    this->idc=idc;
    this->nameconcert=nameconcert;
    this->pl=pl;
    this->place=place;
    this->price=price;
}

QString concert :: get_idc()
{
    return idc;
}

QString concert :: get_nameconcert()
{
    return nameconcert;
}

QString concert :: get_pl()
{
    QString play;
    if(pl!="")
    {
        if(listforplay::get_instance()->find_pl(pl)!=0)
        {
            play=listforplay::get_instance()->find(pl);
        }
        return play;
    }
    return "спектакля нет";
}

int concert :: get_place()
{
    return place;
}

int concert :: get_price()
{
    return price;
}
