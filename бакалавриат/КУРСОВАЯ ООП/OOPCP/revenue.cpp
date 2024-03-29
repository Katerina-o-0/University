#include "revenue.h"
#include "ui_revenue.h"
#include "listforticket.h"
#include "ticket.h"
revenue::revenue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::revenue)
{
    ui->setupUi(this);
}

revenue::~revenue()
{
    delete ui;
}
//для кнопки назад
void revenue::on_pushButton_2_clicked()
{
   this->close();
   emit mainwind();
}

//для подсчета выручки
void revenue::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
    listforticket* listforticket=listforticket::get_instance();
    int row = listforticket->get_size();
    if(row!=0)
    {
        for(int i =0; i<row;i++)
         {
            int rev=listforticket::get_instance()->findprice();

            QString it =QString :: number(rev)+" руб.";
            ui->textEdit->append(it);
            ui->textEdit->append(" ");
         }
    }
    else
    {
        ui->textEdit->append("нет выручки");
    }
}
