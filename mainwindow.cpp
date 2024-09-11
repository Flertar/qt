#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QWidget"
#include "QMessageBox"

#include "QSerialPort"
#include "QSerialPortInfo"

#include "QCanBusDevice"
#include "QCanBusDeviceInfo"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ports
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->PortB->addItems(stringPorts);

    // Baud Rate Ratios
    QList<qint32> baudRates = QSerialPortInfo::standardBaudRates();
    QList<QString> stringBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        stringBaudRates.append(QString::number(baudRates.at(i))+" bps");
    }
    ui->BaudRatesB->addItems(stringBaudRates);


    // Data Bits
    ui->DataBitBox->addItem("5 Bits");
    ui->DataBitBox->addItem("6 Bits");
    ui->DataBitBox->addItem("7 Bits");
    ui->DataBitBox->addItem("8 Bits");

    // Stop Bits
    ui->StopBitBox->addItem("1 Bit");
    ui->StopBitBox->addItem("1,5 Bits");
    ui->StopBitBox->addItem("2 Bits");

    //Flow Controls
    ui->FlowBox->addItem("No Flow Control");
    ui->FlowBox->addItem("Hardware Flow Control");
    ui->FlowBox->addItem("Software Flow Control");

}

MainWindow::~MainWindow()
{
    delete ui;


}


void MainWindow::on_ConB_clicked()
{
    QString portName = ui->PortB->currentText();
    serialPort.setPortName(portName);

    serialPort.open(QIODevice::ReadWrite);

    if(!serialPort.isOpen()){
        ui->textBrowser->setText("Incorrect connection, please change the settings and try to connect again");
    }
    else {

        QString stringbaudRate = ui->BaudRatesB->currentText();
        int intbaudRate = stringbaudRate.toInt();
        serialPort.setBaudRate(intbaudRate);

        QString dataBits = ui->DataBitBox->currentText();
        if(dataBits == "5 Bits") {
            serialPort.setDataBits(QSerialPort::Data5);
        }
        else if((dataBits == "6 Bits")) {
            serialPort.setDataBits(QSerialPort::Data6);
        }
        else if(dataBits == "7 Bits") {
            serialPort.setDataBits(QSerialPort::Data7);
        }
        else if(dataBits == "8 Bits"){
            serialPort.setDataBits(QSerialPort::Data8);
        }

        QString stopBits = ui->StopBitBox->currentText();
        if(stopBits == "1 Bit") {
            serialPort.setStopBits(QSerialPort::OneStop);
        }
        else if(stopBits == "1,5 Bits") {
            serialPort.setStopBits(QSerialPort::OneAndHalfStop);
        }
        else if(stopBits == "2 Bits") {
            serialPort.setStopBits(QSerialPort::TwoStop);
        }


        QString flowControl = ui->FlowBox->currentText();
        if(flowControl == "No Flow Control") {
            serialPort.setFlowControl(QSerialPort::NoFlowControl);
        }
        else if(flowControl == "Hardware Flow Control") {
            serialPort.setFlowControl(QSerialPort::HardwareControl);
        }
        else if(flowControl == "Software Flow Control") {
            serialPort.setFlowControl(QSerialPort::SoftwareControl);
        }

        code = ui->lineE->text();
        codeSize = code.size();

    }    connect(&serialPort,SIGNAL(readyRead()),this,SLOT(ReceiveMessage()));

}

void MainWindow::on_CloseB_clicked()
{
    serialPort.close();
}

void MainWindow::ReceiveMessage() {
    QByteArray dataBA = serialPort.readAll();
    QString data(dataBA);
    ui->textBrowser->append("Получено: " + data);
    buffer.append(data);
    int index = buffer.indexOf(code);
    if (index != -1) {
        QString message = buffer.mid(0, index);
        ui->textBrowser->append(message);
        buffer.remove(0, index + codeSize);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString message = ui->lineE->text();
    ui->textBrowser->append(message);
    serialPort.write(message.toUtf8());
}

