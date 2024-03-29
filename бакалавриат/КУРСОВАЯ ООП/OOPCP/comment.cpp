//commnt.cpp
#include "comment.h"
#include "ui_comment.h"
#include "listforfeedback.h"
#include "feedback.h"

comment::comment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comment)
{
    ui->setupUi(this);
}

comment::~comment()
{
    delete ui;
}

//для кнопки назад
void comment::on_pushButton_2_clicked()
{
   this->close();
   emit mainwind();
}
//для кнопки "посмотреть"
void comment::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
    listforfeedback* listforfeedback=listforfeedback::get_instance();
    int row = listforfeedback->get_size();
    if(row!=0)
    {
        for(int i =0; i<row;i++)
         {
            QString it = listforfeedback->forshow(i);
            ui->textEdit->append(it);
            ui->textEdit->append(" ");
         }
    }
    else
    {
        ui->textEdit->append("Нет отзывов");
    }
}
//для кнопки добавить
void comment::on_pushButton_3_clicked()
{

    ui->textEdit->clear();
    listforfeedback* add = listforfeedback::get_instance();
    ui->textEdit->append((add->add(ui->lineEdit->text())));
    ui->lineEdit->clear();
}
