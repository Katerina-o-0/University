#include "play.h"

play::play(QString idp, QString nameplay, vector<QString>actors)
{
      this->nameplay = nameplay;
      this->idp = idp;
      this->actors=actors;
}

//функция возврата имени атёра
QString play::get_nameplay()
{
    return nameplay;
}

//функция возврата id актёра
QString play::get_idp()
{
    return idp;
}

 QString play :: get_act() //возврат актёров
 {
     QString actor;
     if(actors.size()!=0)
     {
         for(int i=0;i<actors.size();i++)
         {
             if(listforactor::get_instance()->find_act(actors[i])!=0)
             {
                 actor=actor+"  " + listforactor::get_instance()->find(actors[i]);
             }
         }
         return actor;
     }
     return "актёров нет";

 }
