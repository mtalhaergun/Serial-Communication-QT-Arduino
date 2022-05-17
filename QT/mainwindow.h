#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_buttonLed_clicked();

    void on_buttonSay_clicked();

    void gonder(QString);

    void sayiSay();


private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 vendor_id = 9025;
    static const quint16 product_id = 66;
    QString port_name;
    bool arduino_is_available;
    bool buttonLed;
    bool buttonSay;
    QString sayi;
    int i_sayi;
    QTimer *timer;

};
#endif // MAINWINDOW_H
