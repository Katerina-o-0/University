#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QString encode_image(const QString& path);
    QString encode(QByteArray input, unsigned const int len);
    QString readfile(const QString& pathToFile);
    void decode_image(const QString& input, const QString& pathToSave);
    bool is_this(QString input);
    unsigned int pos(const unsigned char chr);
    QByteArray decode(const QByteArray& input);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
