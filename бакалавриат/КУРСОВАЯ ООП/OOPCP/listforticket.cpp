#include "listforticket.h"

listforticket* listforticket::instance = nullptr;

listforticket* listforticket :: get_instance()
{
    if(instance==nullptr)
        instance = new listforticket();
    return instance;
}

//возвращает кол-во элементов в списке
int listforticket::get_size()
{
    return tickets.size();
}

QString listforticket::add(QString idc)
{
 if(idc!="")
 {
     int id,price;
     if(tickets.size()==0)
     {
         id=1;
     }
     else
     {
         id=tickets.back()->get_id()+1;
     }
     if(listforconcert::get_instance()->find_pl(idc)!=0)
     {
         price=listforconcert::get_instance()->findprice(idc);
     }
     QString result=listforconcert::get_instance()->change(idc);
     ticket* act = new ticket(id, price);
     tickets.push_back(act);
     return result;
 }
 return "пустые поля";

}

QString listforticket:: forshow(int n) //просмотреть список концертов
{
    QString id=QString :: number(tickets[n]->get_id());
    QString price=QString :: number(tickets[n]->get_price());
    QString itog = "id: "+ id +"  Стоимость:  " + price;
    return itog;
}

int listforticket:: findprice() //найти спектакль
{
    int price;
    if (tickets.size()!=0)
    {

        for(int i=0; i<tickets.size(); i++)
        {
            price=price+tickets[i]->get_price();
        }
    }
    return price;
}
