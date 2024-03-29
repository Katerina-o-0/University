//listforactor.cpp
#include "listforactor.h"
#include <QTextStream>

listforactor* listforactor::instance = nullptr;

listforactor* listforactor :: get_instance()
{
    if(instance==nullptr)
        instance = new listforactor();
    return instance;
}

QString listforactor::add(QString id, QString name)
{
    if(id!="" || name!="")
    {
        for(int i=0; i<base.size(); i++)
        {
            if(id==base[i]->get_id())
            {
                return "актёр с таким id уже существует";
            }
        }
        actor* act = new actor(id, name);
        base.push_back(act);
        return "актёр добавлен";
    }
    return "пустые поля";

}

//возвращает кол-во элементов в списке
int listforactor::get_size()
{
    return base.size();
}



QString listforactor::forshow(int n)
{
        QString id = base[n]->get_id();
        QString name = base[n]->get_name();
        QString itog = "id: "+ id +"  ФИО:  " + name;
        return itog;

}

QString listforactor :: find(QString id)
{
    if (base.size()!=0)
    {
        QString actor;
        for(int i=0; i<base.size(); i++)
        {
            if(base[i]->get_id()==id)
            {
                actor = base[i]->get_name();
                return "id: "+id +"  ФИО:  "+ actor;
            }

        }
        return "актёра с таким id не существует";
    }
    return "Нет актёров";

 }

//удаление элемента из списка
QString listforactor::del(QString id)
{

    if(base.size()!=0)
    {
        for (int i = 0; i < base.size(); i++)
        {
            if (base[i]->get_id() == id)
            {
                base.erase(base.begin()+i);
                return "актёр удалён";
            }
        }
        return "актёра с таким id не существует";
    }
    return "Нет актёров";
}
 actor*  listforactor :: find_act (QString id)
 {
     actor* a;
     for(int i=0; i<base.size(); i++)
     {
         if(base[i]->get_id()==id)
         {
             a = base[i];
         }
     }

     return a;
 }

void listforactor::fromfile()
{
    base.clear();
    ifstream input;
    input.open("D:\\Documents\\OOPCP\\actor.txt");
    while(input)
    {
        string id,name;
        getline(input,id,',');
        getline(input,name);
        this->add(QString::fromStdString(id),QString::fromStdString(name));
    }
    input.close();

}

void listforactor::infile()
{
     QTextStream out(stdout);
     QString filename = "D:\\Documents\\OOPCP\\act.txt";
     QFile file(filename);
     // Открываем файл в режиме "Только для записи"
       if (file.open(QIODevice::WriteOnly))
       {
         QTextStream out(&file); // поток записываемых данных направляем в файл

                                 // Для записи данных в файл используем оператор <<
         for(int i=0; i<base.size(); i++)
         {
             QString id = base[i]->get_id();
             QString name = base[i]->get_name();
             QString itog = id +"," + name;
             out << itog<<"\r\n";
         }

       }

       // Закрываем файл
       file.close();


}
