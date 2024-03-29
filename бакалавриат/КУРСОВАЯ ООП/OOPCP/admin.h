//admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
signals:
    void mainwind();
private slots:
    void on_pushButton_2_clicked();//кнопка назад
    void on_pushButton_3_clicked();//добавить
    void on_pushButton_4_clicked();//посмотреть
    void on_pushButton_5_clicked();//удалить
    void on_pushButton_6_clicked();//поиск
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();

private:
    Ui::admin *ui;
};

#endif // ADMIN_H
