//billboard.h
#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <QWidget>

namespace Ui {
class billboard;
}

class billboard : public QWidget
{
    Q_OBJECT

public:
    explicit billboard(QWidget *parent = nullptr);
    ~billboard();
signals:
    void mainwind();
    void update();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
private:
    Ui::billboard *ui;
};

#endif // BILLBOARD_H
