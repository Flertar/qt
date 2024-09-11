#include "mainwindow.h"

#include <QCommandLineParser>


#include "QSerialPort"
#include "QSerialPortInfo"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QCommandLineParser parser;
    parser.setApplicationDescription("Prog");
    parser.addHelpOption();

    QCommandLineOption portOption("p", "Set COM port", "port");
    parser.addOption(portOption);

    QCommandLineOption baudRateOption("b", "Set BaudRate", "baudrate");
    parser.addOption(baudRateOption);

    parser.process(a);

    QString portName = parser.value(portOption);
    QString baudRate = parser.value(baudRateOption);

    if (parser.isSet(portOption)) {
        qDebug() << "Your COM port:" << portName;
    } else {
        qDebug() << "COM is not set.";
    }

    if (parser.isSet(baudRateOption)) {
        qDebug() << "Your BaudRate:" << baudRate;
    } else {
        qDebug() << "BaudRate is not set.";
    }

    return a.exec();
}
