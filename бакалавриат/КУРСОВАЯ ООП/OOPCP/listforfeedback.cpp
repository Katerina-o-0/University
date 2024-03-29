#include "listforfeedback.h"

listforfeedback* listforfeedback::instance = nullptr;

listforfeedback* listforfeedback :: get_instance()
{
    if(instance==nullptr)
        instance = new listforfeedback();
    return instance;
}

//возвращает кол-во элементов в списке
int listforfeedback::get_size()
{
    return fb.size();
}

QString listforfeedback::add(QString idc)
{
 if(idc!="")
 {
     int id;
     if(fb.size()==0)
     {
         id=1;
     }
     else
     {
         id=fb.back()->get_id()+1;
     }
     feedback* pl = new feedback(id, idc);
     fb.push_back(pl);
     return "Отзыв добавлен";


 }
 return "пустые поля";

}

QString listforfeedback:: forshow(int n) //просмотреть список концертов
{
    QString id=QString :: number(fb[n]->get_id());
    QString price=fb[n]->get_fb();
    QString itog = "id: "+ id +"  Отзыв:  " + price;
    return itog;
}
