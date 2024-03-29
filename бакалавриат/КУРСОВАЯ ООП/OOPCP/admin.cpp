//admin.cpp
#include "admin.h"
#include "ui_admin.h"
#include "listforactor.h"
#include "actor.h"
#include "listforplay.h"
#include "listforconcert.h"
#include "concert.h"
#include "play.h"

admin::admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;
}
//для кнопки назад
void admin::on_pushButton_2_clicked()
{
    this->close();
    emit mainwind();
}
//добавить
void admin::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
    listforactor* add=listforactor::get_instance();
    ui->textEdit->append((add->add(ui->lineEdit->text(),ui->lineEdit_2->text())));
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}
//просмотреть
void admin::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
    listforactor* listforactor=listforactor::get_instance();
    int row = listforactor->get_size();
    if(row!=0)
    {
        for(int i =0; i<row;i++)
         {
            QString it = listforactor->forshow(i);
            ui->textEdit->append(it);
         }
    }
    else
    {
        ui->textEdit->append("Нет актёров");
    }

}
//поиск
void admin::on_pushButton_5_clicked()
{
    ui->textEdit->clear();
    listforactor* fin=listforactor::get_instance();
    QString it = fin->find(ui->lineEdit->text());
    ui->textEdit->append(it);
    ui->lineEdit->clear();
}
//удалить
void admin::on_pushButton_6_clicked()
{
    ui->textEdit->clear();
    listforactor* rem = listforactor::get_instance();
    QString it = rem->del(ui->lineEdit->text());
    ui->textEdit->append(it);
    ui->lineEdit->clear();
}

//добавить спектакль
void admin::on_pushButton_7_clicked()
{
    ui->textEdit->clear();
    listforplay* add = listforplay::get_instance();
    ui->textEdit->append((add->add(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text())));
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}
//посмотреть спектакли
void admin::on_pushButton_8_clicked()
{
    ui->textEdit->clear();
    listforplay* listforplay=listforplay::get_instance();
    int row = listforplay->get_size();
    if(row!=0)
    {
        for(int i =0; i<row;i++)
         {
            QString it = listforplay->forshow(i);
            ui->textEdit->append(it);
            ui->textEdit->append(" ");

         }
    }
    else
    {
        ui->textEdit->append("Нет спектаклей");
    }

}
//удалениеспектаклей
void admin::on_pushButton_9_clicked()
{
    ui->textEdit->clear();
    listforplay* rem = listforplay::get_instance();
    QString it = rem->del(ui->lineEdit->text());
    ui->textEdit->append(it);
    ui->lineEdit->clear();
}
//поиск спектаклей
void admin::on_pushButton_10_clicked()
{
    ui->textEdit->clear();
    listforplay* fin=listforplay::get_instance();
    QString it = fin->find(ui->lineEdit->text());
    ui->textEdit->append(it);
    ui->lineEdit->clear();
}
//добавить концерт
void admin::on_pushButton_11_clicked()
{
    ui->textEdit->clear();
    listforconcert* add = listforconcert::get_instance();
    ui->textEdit->append((add->add(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text(),ui->lineEdit_5->text())));
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

//посмотреть концерты
void admin::on_pushButton_12_clicked()
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
//поиск концерта
void admin::on_pushButton_13_clicked()
{
    ui->textEdit->clear();
    listforconcert* fin=listforconcert::get_instance();
    QString it = fin->find(ui->lineEdit->text());
    ui->textEdit->append(it);
    ui->lineEdit->clear();
}
//удаление концерта
void admin::on_pushButton_14_clicked()
{
    ui->textEdit->clear();
    listforconcert* rem = listforconcert::get_instance();
    QString it = rem->del(ui->lineEdit->text());
    ui->textEdit->append(it);
    ui->lineEdit->clear();
}
//добавление актёров из файла
void admin::on_pushButton_15_clicked()
{
    ui->textEdit->clear();
    listforactor* fil = listforactor::get_instance();
    fil->fromfile();
    ui->textEdit->append("актёры добавлены");
}

void admin::on_pushButton_16_clicked()
{
    ui->textEdit->clear();
    listforplay* fil = listforplay::get_instance();
    fil->fromfile();
    ui->lineEdit->clear();
    ui->textEdit->append("спектакли добавлены");
}


void admin::on_pushButton_17_clicked()
{
    ui->textEdit->clear();
    listforconcert* fil = listforconcert::get_instance();
    fil->fromfile();
    ui->lineEdit->clear();
    ui->textEdit->append("концерты добавлены");
}

void admin::on_pushButton_18_clicked()
{
    ui->textEdit->clear();
    listforactor* fil = listforactor::get_instance();
    fil->infile();
    ui->textEdit->append("актёры добавлены");
}

void admin::on_pushButton_19_clicked()
{
    ui->textEdit->clear();
    listforplay* fil = listforplay::get_instance();
    fil->infile();
    ui->textEdit->append("спектакли добавлены");

}

void admin::on_pushButton_20_clicked()
{
    ui->textEdit->clear();
    listforconcert* fil = listforconcert::get_instance();
    fil->infile();
    ui->textEdit->append("концерты добавлены");

}
