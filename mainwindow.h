#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtSerialBus>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_ConB_clicked();

    void ReceiveMessage();

    void on_CloseB_clicked();


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void allPorts();
    QSerialPort serialPort;
    QString buffer;
    QString code;
    int codeSize;
};

#endif // MAINWINDOW_H
