//buyticket.h
#ifndef BUYTICKET_H
#define BUYTICKET_H

#include <QWidget>

namespace Ui {
class buyticket;
}

class buyticket : public QWidget
{
    Q_OBJECT

public:
    explicit buyticket(QWidget *parent = nullptr);
    ~buyticket();
signals:
    void mainwind();
    void update();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::buyticket *ui;
};

#endif // BUYTICKET_H
