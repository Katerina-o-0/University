//listforactor.h
#ifndef LISTFORACTOR_H
#define LISTFORACTOR_H
#include <vector>
#include "actor.h"
#include <QFile>
#include <iostream>
#include <fstream>
using namespace std;
//список актёров
//паттерн singleton
class listforactor
{
protected:
    vector <actor*> base;
    listforactor(){};
    static listforactor* instance;

public:
    static listforactor* get_instance();
    QString add(QString id, QString name); //добавить элемент
    int get_size();//возвращается длина
    QString forshow(int n); //просмотреть список актёров
    QString find(QString); //найти актёра
    QString del(QString); //удалить актёра
    actor* find_act(QString);//найти актёра
    void fromfile();//загрузить из ф
    void infile();//загрузить в файл
};
#endif // LISTFORACTOR_H
