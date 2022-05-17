#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(sayiSay()));
    timer->start(1000);
    arduino_is_available = false;
    port_name = "";
    arduino = new QSerialPort;
    buttonLed = false;
    buttonSay = true;
    i_sayi = 0;

 /*   qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
            if(serialPortInfo.hasVendorIdentifier()){
                qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
            }
            qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
            if(serialPortInfo.hasProductIdentifier()){
                qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
            }
        }
        */

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
                if(serialPortInfo.vendorIdentifier() == vendor_id){
                    if(serialPortInfo.productIdentifier() == product_id){
                        port_name = serialPortInfo.portName();
                        arduino_is_available = true;
                    }
                }
            }
        }

    if(arduino_is_available){
        arduino->setPortName(port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }else{
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }



}

MainWindow::~MainWindow()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}




void MainWindow::on_buttonLed_clicked()
{
    if(buttonLed)
    {
        ui->buttonLed->setText("LEDİ AÇ");
        ui->label->setText("<font color=\"Red\">LED KAPALI");
        buttonLed = false;
        MainWindow::gonder(QString("%1k").arg(0));

    }
    else{
        ui->buttonLed->setText("LEDİ KAPAT");
        ui->label->setText("<font color=\"Green\">LED AÇIK");
        buttonLed = true;
        MainWindow::gonder(QString("%1a").arg(0));

    }
}


void MainWindow::on_buttonSay_clicked()
{
    buttonSay = false;
    ui->buttonSay->setEnabled(buttonSay);
    sayi = ui->textBox->text();
    i_sayi = sayi.toInt();
    if(buttonLed){
        MainWindow::gonder(QString("%1a").arg(i_sayi));
    }
    else{
        MainWindow::gonder(QString("%1k").arg(i_sayi));
    }
}

void MainWindow::gonder(QString komut)
{
    arduino->write(komut.toStdString().c_str());
}

void MainWindow::sayiSay()
{
    if(ui->textBox->text() == "0" && buttonSay)
    {
        ui->buttonSay->setEnabled(buttonSay);
        ui->textBox->clear();
    }
    if(!buttonSay)
    {
            QByteArray ba = arduino->readAll();
            sayi = QString::fromStdString(ba.toStdString());
            ui->textBox->clear();
            ui->textBox->setText(sayi);
            if(sayi.toInt() == 0)
            {
                buttonSay = true;
                ui->textBox->clear();
                ui->textBox->setText(sayi);
            }
    }
}



