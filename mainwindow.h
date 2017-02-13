#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QSharedPointer>
#include <QToolBar>
#include <qtextedit.h>
#include <QMainWindow>
#include <QDialog>
#include <QScopedPointer>
#include <QtSerialPort/QSerialPort>
#include "settingsdialog.h"

#include "FinalData.h"
#include "fmidelegate.h"
#include <QDebug>
#include <QThread>
#include <QMutex>

#include <QDialog>
#include <QStyledItemDelegate>
#include <QItemSelectionModel>
#include "graphikwindow.h"
#include "potentialgraphikwindow.h"
#include "helpmenu.h"


class deviceException : public std::runtime_error
{
  //  QString exception ;
 public:
     deviceException(QString someException): runtime_error(someException.toStdString())
     {
      // exception = someException;
     }

};

class LoadingWorker : public QObject
{
    Q_OBJECT


public:
        LoadingWorker(QByteArray &dData):deviceData(dData){}
public slots:
void doWork();
signals:
void workFinished();
private:
QByteArray &deviceData;


};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
void sendWork();
public slots:
void readData();
void onWorkFinished();
private slots:
    void on_CreatingData_triggered();
 //   void on_tableWidget_cellChanged(int row, int column);
    void on_OpenFile_triggered();
    void on_SaveAsFile_triggered();
    void openSerialPort();
    void closeSerialPort();
    //void about();
    void writeData(const QByteArray &data);


    void handleError(QSerialPort::SerialPortError error);

    void on_graphikaction_triggered();

    void on_potentialGrphikAction_triggered();

    void on_help_action_triggered();

protected:
   // void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
    size_t ncol;
    size_t nrow;
    bool new_file;
    bool is_file_empty;
    FinalData model;
    QString curFileName;
    void loadData();
    SettingsDialog *settings;
    QSerialPort *serial;
    GraphikWindow *graphik;
    QByteArray deviceData;
     LoadingWorker *worker;
     HelpMenu h_menu;
     QThread thread;
    PotentialGraphikWindow *potentialGraphik;
   FmiDelegate delegate;
    void initActionsConnections();
};

#endif // MAINWINDOW_H
