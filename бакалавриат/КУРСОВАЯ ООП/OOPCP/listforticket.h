#ifndef LISTFORTICKET_H
#define LISTFORTICKET_H
#include <vector>
#include "concert.h"
#include "listforconcert.h"
#include "ticket.h"
using namespace std;

//список актёров
//паттерн singleton
class listforticket
{
    vector<ticket*>tickets;
    listforticket(){};
    static listforticket* instance;
public:
    static listforticket* get_instance();
    QString add(QString);//добавление элемента
    int get_size();//возвращается длина
    QString forshow(int n); //просмотреть список концертов
    QString del(QString); //удалить концерт
    QString find(QString); //найти концерт
    void fromfile();
    void infile();
    int findprice(); //найти концерт
};

#endif // LISTFORTICKET_H
