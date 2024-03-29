#ifndef LISTFORPLAY_H
#define LISTFORPLAY_H
#include <vector>
#include "play.h"
#include <QList>
#include <QFile>
#include <iostream>
#include <fstream>

using namespace std;

//список актёров
//паттерн singleton
class listforplay
{
protected:
    vector <play*> plays;
    listforplay(){};
    static listforplay* instance;
public:
    static listforplay* get_instance();
    QString add(QString, QString,QString);//добавление элемента
    int get_size();//возвращается длина
    QString forshow(int n); //просмотреть список спектаклей
    QString del(QString); //удалить спектакль
    QString find(QString); //найти спектакль
    play* find_pl(QString);
    void fromfile();
    void infile();
};

#endif // LISTFORPLAY_H
