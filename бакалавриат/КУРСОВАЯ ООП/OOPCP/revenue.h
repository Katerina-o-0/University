#ifndef REVENUE_H
#define REVENUE_H

#include <QWidget>

namespace Ui {
class revenue;
}

class revenue : public QWidget
{
    Q_OBJECT

public:
    explicit revenue(QWidget *parent = nullptr);
    ~revenue();
signals:
    void mainwind();
    void update();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::revenue *ui;
};

#endif // REVENUE_H
