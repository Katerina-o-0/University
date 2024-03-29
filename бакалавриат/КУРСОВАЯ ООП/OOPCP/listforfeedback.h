//listforfeedback.h
#ifndef LISTFORFEEDBACK_H
#define LISTFORFEEDBACK_H
#include "feedback.h"
#include <QList>
#include <QFile>



using namespace std;

class listforfeedback
{
protected:
    vector<feedback*>fb;
    listforfeedback(){};
    static listforfeedback* instance;

public:
    static listforfeedback* get_instance();
    QString add(QString);//добавление элемента
    int get_size();//возвращается длина
    QString forshow(int n); //просмотреть список концертов
};

#endif // LISTFORFEEDBACK_H


//список актёров
//паттерн singleton


