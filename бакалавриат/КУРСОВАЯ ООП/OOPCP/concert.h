//concert.h
#ifndef CONCERT_H
#define CONCERT_H
#include <iostream>
#include <QWidget>
#include <vector>
#include "listforplay.h"
#include "play.h"
using namespace std;

class concert
{
private:
    QString nameconcert;//название концерат
    QString idc; //id концерта
    QString pl; //id спектакля
    int place; //кол-во мест
    int price; //стоимость билетов

public:
    concert(QString, QString, QString,int,int);
    QString get_nameconcert();
    QString get_idc();
    QString get_pl();
    int get_place();
    int get_price();
};

#endif // CONCERT_H
