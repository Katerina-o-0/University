//actor.cpp
#include "actor.h"

actor::actor(QString id, QString name)
{
    this->id = id;
    this->name = name;
}

//функция возврата имени атёра
QString actor::get_name()
{

    return name;
}

//функция возврата id актёра
QString actor::get_id()
{
    return id;
}
