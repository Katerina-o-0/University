//comment.h
#ifndef COMMENT_H
#define COMMENT_H
#include <QWidget>

namespace Ui {
class comment;
}

class comment : public QWidget
{
    Q_OBJECT

public:
    explicit comment(QWidget *parent = nullptr);
    ~comment();
signals:
    void mainwind();
    void update();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::comment *ui;
};

#endif // COMMENT_H
