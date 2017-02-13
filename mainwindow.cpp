#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QResizeEvent>
#include <QTextStream>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QIcon>
#include <cstdlib>
#include <QResizeEvent>
#include <QApplication>
#include <cmath>
//#define NormalMode
#define DebugSerial



void MainWindow::loadData()
{


}

void LoadingWorker::doWork()
{
    QThread::msleep(15000);
    qDebug()<<"QByteArray size = "<<deviceData.size();
    if(deviceData.size() == 0)
        emit workFinished();

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),is_file_empty(true)
{
    ui->setupUi(this);
    this->setWindowTitle("Програма для роботи з пристроєм MGP");
    ui->progressBar->setTextVisible(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0,10);
   serial = new QSerialPort(this);
   settings = new SettingsDialog;
   graphik = new GraphikWindow();
   potentialGraphik = new PotentialGraphikWindow();
    ui->actionConnect->setEnabled(true);
    ui->graphikaction->setEnabled(false);
    ui->potentialGrphikAction->setEnabled(false);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);
    //------------------------------------------
    worker = new LoadingWorker(deviceData);
    worker->moveToThread(&thread);

#ifdef DebugSerial
    ui->forTest->setEnabled(true);
#else
    ui->forTest->setEnabled(false);
#endif

    initActionsConnections();
    ui->progressBar->setTextVisible(false);
    QObject::connect(&thread, &QThread::finished, worker, &QObject::deleteLater );
    QObject::connect(worker, SIGNAL(workFinished()),
                     this, SLOT(onWorkFinished()) );
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    QObject::connect(this, SIGNAL(sendWork()),
                     worker, SLOT(doWork()));

    ui->tableView->setMinimumSize(950,800);
    ui->tableView->setItemDelegate(new FmiDelegate);
    ui->tableView->setModel(&model);
    thread.start();
    }

MainWindow::~MainWindow()
{

    thread.quit();
    thread.wait();
    delete settings;
    delete serial;
    delete ui;
}

void MainWindow::on_CreatingData_triggered()
{
 ui->graphikaction->setEnabled(true);
 ui->potentialGrphikAction->setEnabled(true);
 model.creatingData();
 ui->progressBar->setValue(10);
}



void MainWindow::on_OpenFile_triggered()
{
    ui->graphikaction->setEnabled(true);
    ui->potentialGrphikAction->setEnabled(true);
    model.readData();
    ui->progressBar->setValue(10);

}


void MainWindow::on_SaveAsFile_triggered()
{
 QString filename = QFileDialog::getSaveFileName(this, tr("Open File"), QString(),
                /*  "Text Files (*.txt);;*/" MGP File (*.mgv)");
 if(!filename.isEmpty())
 {
 model.writeData(filename);
 }
}


void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
            emit sendWork();
            QMessageBox quitMsg;
            quitMsg.setWindowTitle("Пристрій підключено!");
            quitMsg.setText("Тепер на панелі приладу mgp натисніть кнопку ПК!");
            if (quitMsg.exec() == QMessageBox::Ok)
               return;

    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    serial->close();
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}
//! [5]

/*void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}*/

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}
//! [6]

//! [7]
//!
void MainWindow::readData()
{
    qDebug()<<"Signal send";
    ui->graphikaction->setEnabled(true);
    ui->potentialGrphikAction->setEnabled(true);
#ifdef NormalMode

    for(int i = 0; i < 5; ++i)
    {
        serial->waitForReadyRead(100);
        ui->progressBar->setValue(i);
    }
    deviceData = serial->readAll(); // Перший, один і актуальний рядок цього слоту
    for(int i = 5; i < 10; ++i)
    {
        serial->waitForReadyRead(100);
        ui->progressBar->setValue(i);
    }
    if(deviceData.size() < 5)
    {
        QString isMGP;

        QTextStream(&isMGP)<<deviceData;
        qDebug()<<isMGP;
        if (isMGP != "$MGP")
            throw new deviceException("Error");

        return;
    }
    qDebug()<<"Done";
#endif
    //----------------------------------------------------------------------------------!!!!!!!!!!
#ifdef DebugSerial
       QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    for(int i = 0; i < 10; ++i)
    {
        serial->waitForReadyRead(100);
        ui->progressBar->setValue(i);
    }
    ui->progressBar->setTextVisible(true);
    QTextStream stream(&file);
    QString line;
    do {
        line = stream.readLine();
        line.remove(" ");

        deviceData.push_back(line.toStdString().c_str());
    } while (!line.isNull());
    stream.flush();
    file.close();


    ui->progressBar->setValue(10);
    //------------------------------------------------------------------------------------!!!!!!!!!
    QString debugFile("Debug.txt");

    QFile fileToDebug(debugFile);
    if (!fileToDebug.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }
    QTextStream DebugStream(&fileToDebug);
    DebugStream<<deviceData.size();
    for(int i = 0; i < deviceData.size(); ++i )
        DebugStream<<deviceData[i];
    DebugStream.flush();
    fileToDebug.close();

    #endif
    //-----------------------------------------------------------------------------------------------
    QByteArray::Iterator deviceDataBegin =deviceData.begin();
    QByteArray::Iterator deviceDataEnd =deviceData.end();
    data_type in_data;
    std::copy(deviceDataBegin, deviceDataEnd, std::back_inserter(in_data));


    for(int i = 0; i < deviceData.size(); ++i)
        qDebug ()<<in_data[i];

    RawData rawData;
    rawData.fillingRawData(in_data);
   model.clear();
   model.load(rawData);


}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->forTest, SIGNAL(triggered()),  this, SLOT(readData()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
       // connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
   // connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}







void MainWindow::on_graphikaction_triggered()
{
    QVector<double> depthPoints;
    for(int i = 0; i <model.getSizeItemData(); ++i )
        depthPoints.push_back(model.getItemDepth(i));
    for(int i = 0; i <model.getSizeItemData(); ++i )
        qDebug()<<depthPoints[i];
    QVector<double>::iterator pos;
    pos = std::max_element(depthPoints.begin(), depthPoints.end());
    int zoom = round(*pos);
    if(*pos > zoom) zoom++;

    graphik->setDepthPonts(depthPoints);
    graphik->showGraphik(zoom);
}



void MainWindow::on_potentialGrphikAction_triggered()
{
    bool noData = true;
    QVector<double> pothentialPoints;
    for(int i = 0; i <model.getSizeItemData(); ++i )
    {
        QString tempPotential = QString::fromStdString(model.getItemPotential(i)) ;
        tempPotential.remove("+");
        pothentialPoints.push_back(tempPotential.toDouble());
    }
    for(int i = 0; i <model.getSizeItemData(); ++i )
        qDebug()<<pothentialPoints[i];
    for(int i = 0; i <model.getSizeItemData(); ++i )
     if(pothentialPoints[i]!=0)
     {
       noData = false;
       break;
     }
     QVector<double>::iterator pos;
    pos = std::max_element(pothentialPoints.begin(), pothentialPoints.end());
    int zoom = round(*pos);
    if(*pos > zoom) zoom++;
    if(*pos==0) zoom++;
    if(noData)
    {
        QMessageBox quitMsg;
        quitMsg.setWindowTitle("Даних немає!");
        quitMsg.setText("Даних немає!");
        if (quitMsg.exec() == QMessageBox::Ok)
           return;
    } else
    {
        potentialGraphik->setPotentialPoints(pothentialPoints);
        potentialGraphik->showGraphik(zoom);
     }
    }

void MainWindow::onWorkFinished()
{
    QMessageBox quitMsg;
    quitMsg.setWindowTitle("Даних немає!");
    quitMsg.setText("Даних немає або прилад не підєднаний!");
    if (quitMsg.exec() == QMessageBox::Ok)
       return;
}

void MainWindow::on_help_action_triggered()
{
    h_menu.show();
}
