#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    try
        {
    w.show();
    } catch(deviceException error)
    {
        QMessageBox quitMsg;
        quitMsg.setWindowTitle("Error open file!");
        quitMsg.setText("Invalid file "+QString(error.what())+"\nDo you want to try again?\n");
        quitMsg.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
        if (quitMsg.exec() == QMessageBox::Yes)
       w.readData();
        else qDebug()<<"end";
    }
//I may be do it!!!
    return a.exec();
}
