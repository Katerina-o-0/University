#ifndef PLAY_H
#define PLAY_H
#include <iostream>
#include <QWidget>
#include <vector>
#include "listforactor.h"
#include "actor.h"
using namespace std;

class play
{
private:
    QString nameplay;//название спектакля
    QString idp;//id спектакля
    vector<QString> actors;//актёры
public:
    play(QString, QString, vector<QString>);
    QString get_nameplay(); //возврат названия спектакля
    QString get_idp(); //возврат id спектакля
    QString get_act(); //возврат актёров
};

#endif // PLAY_H
