//actor.h
#ifndef ACTOR_H
#define ACTOR_H
#include <QWidget>

class actor
{
private:
    QString name; //имя актёра
    QString id; //идентификатор актёра
public:
    actor(QString, QString);
    QString get_name(); //возврат имени актёра
    QString get_id(); //возврат id актёра
};

#endif // ACTOR_H
