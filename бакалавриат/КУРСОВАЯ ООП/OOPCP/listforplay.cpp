#include "listforplay.h"
#include <QString>
#include <QTextStream>

listforplay* listforplay::instance = nullptr;

listforplay* listforplay :: get_instance()
{
    if(instance==nullptr)
        instance = new listforplay();
    return instance;
}

//возвращает кол-во элементов в списке
int listforplay::get_size()
{
    return plays.size();
}

//добавление элемента в список
QString listforplay::add(QString idp, QString nameplay,QString act)
{
 if(idp!="" || nameplay!="" || act!="")
 {
     for(int i=0;i<plays.size();i++)
     {
         if(idp==plays[i]->get_idp())
         {
             return "Спектакль с таким id  уже существует";
         }
     }

     if(act.size()!=0)
     {
         QStringList w=act.split(",");
         vector<QString>d;
         for(int i=0;i<w.size();i++)
         {
            d.push_back(w[i]);
         }
         play* pl = new play(idp, nameplay,d);
         plays.push_back(pl);
         return "Спектакль добавлен";
     }
     return "ошибка ввода";
 }

 return "пустые поля";

}
//просмотр
QString listforplay::forshow(int n)
{
        QString idp = plays[n]->get_idp();
        QString nameplay = plays[n]->get_nameplay();
        QString actors=plays[n]->get_act();
        QString itog = "id: "+ idp +"  Название спектакля:  " + nameplay+"  актёры:  "+actors;
        return itog;
}

//удаление элемента из списка
QString listforplay::del(QString id)
{

    if(plays.size()!=0)
    {
        for (int i = 0; i < plays.size(); i++)
        {
            if (plays[i]->get_idp() == id)
            {
                plays.erase(plays.begin()+i);
                return "спектакль удалён";
            }
        }
        return "спектакля с таким id не существует";
    }
    return "Нет спектаклей";
}


QString listforplay:: find(QString id) //найти спектакль
{
    if (plays.size()!=0)
    {

        for(int i=0; i<plays.size(); i++)
        {
            if(plays[i]->get_idp()==id)
            {
               QString nameplay =plays[i]->get_nameplay();
                QString actors=plays[i]->get_act();
                return "id: "+id +"  Название спектакля:  "+ nameplay+"  актёры:  "+actors;
            }

        }
        return "спектакля с таким id не существует";
    }
    return "Нет спектаклей";
}

play* listforplay::find_pl(QString id)
{
    play* a;
    for(int i=0; i<plays.size(); i++)
    {
        if(plays[i]->get_idp()==id)
        {
            a = plays[i];
        }
    }

    return a;
}

void listforplay::fromfile()
{
    plays.clear();
    ifstream input;
    input.open("D:\\Documents\\OOPCP\\plays.txt");
    while(input)
    {
        string id,name,act;
        getline(input,id,';');
        getline(input,name,';');
        getline(input,act);
        this->add(QString::fromStdString(id),QString::fromStdString(name),QString::fromStdString(act));
    }
    input.close();
}

void listforplay::infile()
{
     QTextStream out(stdout);
     QString filename = "D:\\Documents\\OOPCP\\plays1.txt";
     QFile file(filename);
     // Открываем файл в режиме "Только для записи"
       if (file.open(QIODevice::WriteOnly))
       {
         QTextStream out(&file); // поток записываемых данных направляем в файл

                                 // Для записи данных в файл используем оператор <<
         for(int i=0; i<plays.size(); i++)
         {
             QString idp = plays[i]->get_idp();
             QString nameplay = plays[i]->get_nameplay();
             QString actors=plays[i]->get_act();
             QString itog = idp +";" + nameplay+";"+actors;

             out << itog<<"\r\n";
         }

       }

       // Закрываем файл
       file.close();
}
