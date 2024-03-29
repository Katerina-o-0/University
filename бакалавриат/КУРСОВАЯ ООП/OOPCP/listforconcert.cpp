#include "listforconcert.h"
#include <QTextStream>
listforconcert* listforconcert::instance = nullptr;

listforconcert* listforconcert :: get_instance()
{
    if(instance==nullptr)
        instance = new listforconcert();
    return instance;
}

//возвращает кол-во элементов в списке
int listforconcert::get_size()
{
    return con.size();
}

QString listforconcert::add(QString idc, QString nameconcert,QString pl,QString place,QString price)
{
 if(idc!="" || nameconcert!="" || pl!="" || place!=""|| price!="")
 {
     for(int i=0;i<con.size();i++)
     {
         if(idc==con[i]->get_idc())
         {
             return "Концерт с таким id  уже существует";
         }
     }
     int p= place.toInt();
     int pr= price.toInt();
     concert* act = new concert(idc, nameconcert,pl,p,pr);
     con.push_back(act);
     return "Концерт добавлен";
 }
 return "пустые поля";

}


QString listforconcert:: forshow(int n) //просмотреть список концертов
{
    QString idp = con[n]->get_idc();
    QString nameconcert = con[n]->get_nameconcert();
    QString pl=con[n]->get_pl();
    QString place=QString :: number(con[n]->get_place());
    QString price=QString :: number(con[n]->get_price());
    QString itog = "id: "+ idp +"  Дата и время:  " + nameconcert+"  Спектакль:  "+pl+"   Кол-во мест:  "+place+"  Стоимость(руб):  "+price;
    return itog;
}

//удаление элемента из списка
QString listforconcert::del(QString id)
{

    if(con.size()!=0)
    {
        for (int i = 0; i < con.size(); i++)
        {
            if (con[i]->get_idc() == id)
            {
                con.erase(con.begin()+i);
                return "концерт удалён";
            }
        }
        return "концерт с таким id не существует";
    }
    return "Нет концертов";
}



QString listforconcert:: find(QString id) //найти спектакль
{
    if (con.size()!=0)
    {

        for(int i=0; i<con.size(); i++)
        {
            if(con[i]->get_idc()==id)
            {
               QString nameconcert =con[i]->get_nameconcert();
                QString pl=con[i]->get_pl();
                QString place=QString :: number(con[i]->get_place());
                QString price=QString :: number(con[i]->get_price());
                return "id: "+ id +"  Дата и время:  " + nameconcert+"  Спектакль:  "+pl+"   Кол-во мест:  "+place+"  Стоимость(руб):  "+price;

            }

        }
        return "спектакля с таким id не существует";
    }
    return "Нет спектаклей";
}
void listforconcert::fromfile()
{
    con.clear();
    ifstream input;
    input.open("D:\\Documents\\OOPCP\\concert.txt");
    while(input)
    {
        string id,name,play,place,price;
        getline(input,id,';');
        getline(input,name,';');
        getline(input,play,';');
        getline(input,place,';');
        getline(input,price);
        this->add(QString::fromStdString(id),QString::fromStdString(name),QString::fromStdString(play),QString::fromStdString(place),QString::fromStdString(price));
    }
    input.close();
}

void listforconcert::infile()
{
     QTextStream out(stdout);
     QString filename = "D:\\Documents\\OOPCP\\concert1.txt";
     QFile file(filename);
     // Открываем файл в режиме "Только для записи"
       if (file.open(QIODevice::WriteOnly))
       {
         QTextStream out(&file); // поток записываемых данных направляем в файл

                                 // Для записи данных в файл используем оператор <<
         for(int i=0; i<con.size(); i++)
         {
             QString idp = con[i]->get_idc();
             QString nameconcert = con[i]->get_nameconcert();
             QString pl=con[i]->get_pl();
             QString place=QString :: number(con[i]->get_place());
             QString price=QString :: number(con[i]->get_price());
             QString itog = idp +";" + nameconcert+";"+pl+";"+place+";"+price;


             out << itog<<"\r\n";
         }

       }
       // Закрываем файл
       file.close();
}

concert* listforconcert::find_pl(QString id)
{
    concert* a;
    for(int i=0; i<con.size(); i++)
    {
        if(con[i]->get_idc()==id)
        {
            a = con[i];
        }
    }

    return a;
}

int listforconcert:: findprice(QString id) //найти спектакль
{
    int price;
    if (con.size()!=0)
    {

        for(int i=0; i<con.size(); i++)
        {
            if(con[i]->get_idc()==id)
            {
                price=con[i]->get_price();

            }

        }
    }
    return price;
}
QString listforconcert:: change(QString id) //найти спектакль
{
    int plac;
    if (con.size()!=0)
    {
        for(int i=0; i<con.size(); i++)
        {
            if(con[i]->get_idc()==id)
            {
                plac=con[i]->get_place();
                if(plac!=0)
                {
                    con[i]->get_place()-1;
                    return"Билет куплен";
                }
                return"Билетов нет";
            }

        }
        return "концерта с таким id нет";
    }
return "концертов нет";
}
