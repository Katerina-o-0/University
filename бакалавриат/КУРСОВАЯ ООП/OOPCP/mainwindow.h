#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "admin.h"
#include "billboard.h"
#include "buyticket.h"
#include "revenue.h"
#include "comment.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
   void update();
private slots:
    void on_pushButton_clicked(); //для администратора
    void on_pushButton_2_clicked();//афиша

    void on_pushButton_3_clicked();//купить билет

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();//оставить отзыв

private:
    Ui::MainWindow *ui;
    admin* first;
    billboard* second;
    buyticket* third;
    revenue*fourth;
    comment* fifth;
};
#endif // MAINWINDOW_H
