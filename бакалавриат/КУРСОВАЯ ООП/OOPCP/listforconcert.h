//listforconcert.h
#ifndef LISTFORCONCERT_H
#define LISTFORCONCERT_H
#include <vector>
#include "concert.h"
using namespace std;

//список актёров
//паттерн singleton
class listforconcert
{
protected:
    vector<concert*>con;
    listforconcert(){};
    static listforconcert* instance;
public:
    static listforconcert* get_instance();
    QString add(QString, QString,QString, QString, QString);//добавление элемента
    int get_size();//возвращается длина
    QString forshow(int n); //просмотреть список концертов
    QString del(QString); //удалить концерт
    QString find(QString); //найти концерт
    int findprice(QString); //найти концерт
    QString change(QString);
    concert* find_pl(QString);
    void fromfile();
    void infile();

};

#endif // LISTFORCONCERT_H
