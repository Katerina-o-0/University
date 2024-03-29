//buyticket.cpp
#include "buyticket.h"
#include "ui_buyticket.h"
#include "listforticket.h"
#include "ticket.h"

buyticket::buyticket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::buyticket)
{
    ui->setupUi(this);
}

buyticket::~buyticket()
{
    delete ui;
}
 //для кнопки назад
void buyticket::on_pushButton_2_clicked()
{
    this->close();
    emit mainwind();
}
//купить
void buyticket::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
    listforticket* add = listforticket::get_instance();
    ui->textEdit->append((add->add(ui->lineEdit->text())));
    ui->lineEdit->clear();
}
//просмотреть купленные билеты
void buyticket::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
    listforticket* listforticket=listforticket::get_instance();
    int row = listforticket->get_size();
    if(row!=0)
    {
        for(int i =0; i<row;i++)
         {
            QString it = listforticket->forshow(i);
            ui->textEdit->append(it);
            ui->textEdit->append(" ");
         }
    }
    else
    {
        ui->textEdit->append("Нет купленных билетов");
    }

}
