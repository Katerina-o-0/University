//billboard.cpp
#include "billboard.h"
#include "ui_billboard.h"
#include "listforconcert.h"
#include "concert.h"

billboard::billboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::billboard)
{
    ui->setupUi(this);

}

billboard::~billboard()
{
    delete ui;
}
//для кнопки назад
void billboard::on_pushButton_2_clicked()
{
    this->close();
    emit mainwind();
}


//для кнопки обновить
void billboard::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
    listforconcert* listforconcert=listforconcert::get_instance();
    int row = listforconcert->get_size();
    if(row!=0)
    {
        for(int i =0; i<row;i++)
         {
            QString it = listforconcert->forshow(i);
            ui->textEdit->append(it);
            ui->textEdit->append(" ");
            ui->textEdit->append(" ");
         }
    }
    else
    {
        ui->textEdit->append("Нет спектаклей");
    }

}
