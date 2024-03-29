#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    first = new admin;
    second=new billboard;
    third=new buyticket;
    fourth=new revenue;
    fifth=new comment;
    //для возврата в главное меню
    connect(first, &admin::mainwind, this, &MainWindow::show);
    connect(second, &billboard::mainwind, this, &MainWindow::show);
    connect(third, &buyticket::mainwind, this, &MainWindow::show);
    connect(fourth, &revenue::mainwind, this, &MainWindow::show);
    connect( fifth, &comment::mainwind, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//для кнопки администратора
void MainWindow::on_pushButton_clicked()
{
    first->show();
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    second->show();
    this->close();
}

void MainWindow::on_pushButton_3_clicked()
{
    third->show();
    this->close();
}

void MainWindow::on_pushButton_5_clicked()
{
   fourth->show();
    this->close();
}



void MainWindow::on_pushButton_4_clicked()
{
     fifth->show();
     this->close();
}
