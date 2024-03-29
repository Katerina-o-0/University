#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QFile>
#include <QFileDialog>

static const QString base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Получение символов файла и отправка в кодировщик
QString MainWindow ::encode_image(const QString& path) {

    QFile infile(path);     // Открытие файла в побитовой режиме чтения
    if (infile.open(QIODevice::ReadOnly)) {
       QByteArray blob = infile.readAll();
       QString result = encode(blob, blob.size());
       infile.close();
       return result;
    }
    else return "Файл не удалось открыть\n";
}

// Кодировка в BASE64
QString MainWindow :: encode(QByteArray input, unsigned const int len) {
    QString ret;
    size_t i = 0;
    QByteArray bytes;
    bytes.resize(3);
    QByteArray sextets;
    sextets.resize(4);

    while (i <= (len - 3)) {
        bytes[0] = input[i];
        bytes[1] = input[i+1];
        bytes[2] = input[i+2];

        sextets[0] = (bytes[0] & 0xfc) >> 2;    // Сдвигаем на 2 бита вправо, чтобы получить 6 бит
        sextets[1] = ((bytes[0] & 0x03) << 4) + ((bytes[1] & 0xf0) >> 4);   // Берем 2 последних бита bytes[0] и складываем их с четырьмя из bytes[1]
        sextets[2] = ((bytes[1] & 0x0f) << 2) + ((bytes[2] & 0xc0) >> 6);   // Берем 4 последних бита bytes[1] и складываем их с двумя из bytes[2]
        sextets[3] = bytes[2] & 0x3f;   // Берем 6 последних бит из bytes[2]

        for (size_t j = 0; j < 4; ++j) {
            ret += base64[sextets[j]]; // Получаем соответствующие символы по BASE64
        }

        i += 3; // Увеличиваем итератор на 3, т.к. считывали три байта
    }

    // Ситуация, если осталось не три байта (меньше), а с ними что-то нужно делать
    if (i != len) {
        size_t k = 0;
        size_t j = len - i; // Получаем индекс последнего счит. байта
        while (k < j) {     // Присваиваем оставшиеся байты
            bytes[k] = input[i + k];
            ++k;
        }

        while (j < 3) {     // Последним байтам ставим 0x00
            bytes[j] = '\0';
            ++j;
        }

        sextets[0] = (bytes[0] & 0xfc) >> 2;
        sextets[1] = ((bytes[0] & 0x03) << 4) + ((bytes[1] & 0xf0) >> 4);
        sextets[2] = ((bytes[1] & 0x0f) << 2) + ((bytes[2] & 0xc0) >> 6);
        // Последние 6-бит не заполняем, т.к. если была бы полная картина, то (i != len) было бы ложным

        for (j = 0; j < (len - i) + 1; ++j) {
            ret += base64[sextets[j]];
        }

        while ((j++) < 4)   // Недостающие символы ковертируем в '='
            ret += '=';

    }

    return ret;
}

QString MainWindow :: readfile(const QString& pathToFile) {
    QFile file(pathToFile);

    if (!file.open(QIODevice::ReadOnly)) {
        return "";
    }
     QTextStream stream(&file);
     QString out;
     stream >> out;
     file.close();
     return out;
}

// Является ли BASE64 кодом
bool MainWindow:: is_this(QString input) {
    QRegularExpression re("[a-zA-Z0-9\\/\\+\\=]{1,}");
    QRegularExpressionMatch match = re.match(input);
    return match.hasMatch();
}

// Возвращает позицию символа по BASE64 (а не по ASCII)
unsigned int MainWindow:: pos(const unsigned char chr) {
    //высчитываем в соответствии с таблицей
    if (chr >= 'A' && chr <= 'Z')
        return chr - 'A';
    else if (chr >= 'a' && chr <= 'z')
        return chr - 'a' + ('Z' - 'A') + 1;
    else if (chr >= '0' && chr <= '9')
        return chr - '0' + ('Z' - 'A') + ('z' - 'a') + 2;
    else if (chr == '+')
        return 62;
    else if (chr == '/')
        return 63;



}

// Декодирование BASE64
QByteArray MainWindow:: decode(const QByteArray& input) {
    QByteArray ret;
    size_t i = 0;
    QByteArray bytes;
    bytes.resize(3);
    QByteArray sextets;
    sextets.resize(4);

    while (i < input.size() && input[i] != '=') {
        size_t j = i % 4;
        sextets[j] = input[i++];

        if (i % 4 == 0) {
            for (j = 0; j < 4; ++j) {
                sextets[j] = pos(sextets[j]);
            }

            bytes[0] = (sextets[0] << 2) + ((sextets[1] & 0x30) >> 4);
            bytes[1] = ((sextets[1] & 0x0f) << 4) + ((sextets[2] & 0x3c) >> 2);
            bytes[2] = ((sextets[2] & 0x03) << 6) + sextets[3];
            for (j = 0; j < 3; ++j)
                ret += bytes[j];
        }
    }

    if (i % 4 != 0) {
        for (size_t j = 0; j < (i % 4); ++j)
            sextets[j] = pos(sextets[j]);

        bytes[0] = (sextets[0] << 2) + ((sextets[1] & 0x30) >> 4);
        bytes[1] = ((sextets[1] & 0x0f) << 4) + ((sextets[2] & 0x3c) >> 2);
        for (size_t j = 0; j < (i % 4) - 1; ++j)
            ret += bytes[j];
    }
    return ret;
}

// Создание (перезапись) файла по BASE64
void MainWindow:: decode_image(const QString& input, const QString& pathToSave) {
    QFile outfile(pathToSave);
    outfile.open(QIODevice::WriteOnly);

    if (!is_this(input)) {
        return;
    }

    QByteArray br = input.toUtf8();
    QByteArray temp = decode(br);
    outfile.write(temp);

    outfile.close();
}

//Для кодирования
void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Какое изображение закодировать?"), "D:\\Documents\\Practice_SAOD\\", tr("Image Files (*.png *.jpg)"));
    QString fN = QFileDialog::getSaveFileName(this,
        tr("Сохранить итог в файле: "), "D:\\Documents\\Practice_SAOD\\", tr("Text Files (*.txt)"));

    QFile file(fN);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream <<encode_image(fileName);
        ui->textEdit->setText("Изображение успешно закодировано и сохранено в файле:");
        ui->textEdit->append(fN);
    }
    file.close();
}

//Для декодирования
void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Text"), "D:\\Documents\\Practice_SAOD\\", tr("Text Files (*.txt)"));
    QString base64Str=readfile(fileName);
    QString fN = QFileDialog::getSaveFileName(this,
        tr("Сохранить итог в файле: "), "D:\\Documents\\Practice_SAOD\\", tr("Image Files (*.png *.jpg)"));
    decode_image(base64Str, fN);
    ui->textEdit->setText("Декодировние проведено успешно. Изображение сохранено:");
    ui->textEdit->append(fN);
}

