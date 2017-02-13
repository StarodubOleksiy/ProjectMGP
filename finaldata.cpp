#include "finaldata.h"
//#define _USE_MATH_DEFINES
#include <cmath>
#include <QFileDialog>
using namespace std;//цукенг
FinalData::FinalData(QObject *parent) :
    QAbstractTableModel(parent)
{
    header_data << QString::fromUtf8("Напруга, В.") << QString::fromUtf8("Глубина, м.")
    << QString::fromUtf8("Частота, Гц")<< QString::fromUtf8("Широта, град.")
    << QString::fromUtf8("Довгота град.")<< QString::fromUtf8("Висота м.")
    << QString::fromUtf8("Дата") << QString::fromUtf8("Час")
    << QString::fromUtf8("Відстань м.");

}
double FinalData::getItemDepth(int index) const
{
  return finData[index].depth;
}

string FinalData::getItemPotential(int index) const
{
 return finData[index].potential.toString();
}

int  FinalData::getSizeItemData()const
{
  return  finData.size();
}



void FinalData::setRawData( RawData &rawData)
{
    load(rawData);
}

void FinalData::load(RawData &rawData)
{
     vector<RawDataLine> temp = rawData.getRawData();
    for(vector<RawDataLine>::iterator itr=temp.begin(); itr != temp.end(); ++itr)
    {
        assert(itr->get_Range_Size() != 0);
        DataLine indata(*itr);
        finData.push_back(indata);
    }
    finData[0].distance = -500;
    for(size_t i = 1; i < finData.size(); ++i)
    {
    double tempLongitude1 = finData[i-1].longitude.toQString().toDouble();
    double tempLatitude1 = finData[i-1].latitude.toQString().toDouble();
    double tempLongitude2 = finData[i].longitude.toQString().toDouble();
    double tempLatitude2 = finData[i].latitude.toQString().toDouble();
    double deltaLongitude = tempLongitude2 - tempLongitude1;
    double deltaLatitude = tempLatitude2 - tempLatitude1;
    deltaLongitude = deltaLongitude*(2*acos(0.0))/180;
    deltaLatitude = deltaLatitude*(2*acos(0.0))/180;
    tempLongitude1 = tempLongitude1*(2*acos(0.0))/180;
    tempLongitude2 = tempLongitude2*(2*acos(0.0))/180;
    //qDebug()<<"sin 30 = " << sin(30*(2*acos(0.0))/180);
    /*double result =sqrt(pow((tempLongitude2-tempLongitude1),2)
    +pow((tempLatitude2-tempLatitude1),2));*/
    double result = radiusEarth*2*asin(sqrt(pow(sin(deltaLongitude/2),2)
    +cos(tempLongitude1)*cos(tempLongitude2)*pow(sin(deltaLatitude/2),2)));
    /*double result = radiusEarth*acos(sin(tempLongitude1)*sin(tempLongitude2)+
                           cos(tempLongitude1)*cos(tempLongitude2)*cos(tempLatitude2-tempLatitude1));*/
    qDebug()<<QString::number(result, 'f', 6 );
    qDebug()<<"arcsin()= " <<asin(tempLongitude1);
    finData[i].distance = QString::number(result, 'd', 6 ).toDouble();
    }
     endResetModel();
}


void FinalData::print(ostream& s, const FinalData& d) const
{

    s <<"$MGP" << endl;
    s << d.finData.size() << endl;
    for(vector<DataLine>::const_iterator itr=d.finData.begin(); itr != d.finData.end(); ++itr)
    {
        s << *itr << endl;
    }

}



ostream& operator << (ostream& s, const FinalData& d)
{
     d.print(s,d);
     return s;
}

std::istream& operator >> (std::istream& s, FinalData& d)
{
    string chekingFile;
    s >> chekingFile;
    cout << chekingFile;
    size_t datalines_in_file;
    s >>  datalines_in_file;
    vector<DataLine> tempData(datalines_in_file);
     if( !datalines_in_file )throw DataFileError("Invalid reading to massyv.");
    d.finData.resize(datalines_in_file);

    for(size_t i=0; i<datalines_in_file; ++i)
    {
        s >> tempData[i];
    }
    d.finData = tempData;
    return s;
}
QVariant FinalData::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= finData.size())
        return QVariant();
    // для каждого столбца возвращаем нужные данные
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (index.column() == voltage )
            return finData.at(index.row()).potential.toQString();
        if (index.column() == depth )
            return  finData.at(index.row()).depth;
        if (index.column() == freg )
            return finData.at(index.row()).freq;
        if (index.column() == longitude)
        {
            return finData.at(index.row()).longitude.toQString()=="91.000050"?
                        "------------" : finData.at(index.row()).longitude.toQString();
        }
        if (index.column() == latitude )
        {
            return finData.at(index.row()).latitude.toQString()=="91.000050"?
                        "------------" : finData.at(index.row()).latitude.toQString();
        }
        if (index.column() == height )
        {
            if(finData.at(index.row()).height == 1000000)
                return "------------";
            else return finData.at(index.row()).height;
        }
        if (index.column() == date )
        {
            return finData.at(index.row()).date.toQString()=="00.00.1800" ?
                        "------------" : finData.at(index.row()).date.toQString();
        }
        if (index.column() == time )
            return finData.at(index.row()).time.toQString();
        if (index.column() == length )
        {
            if(finData.at(index.row()).distance > 100 || finData.at(index.row()).distance == - 500)
                return "------------";
            else
                return finData.at(index.row()).distance;
        }

    }
    return QVariant();
}

bool FinalData::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if (index.isValid() && role == Qt::EditRole) {
       switch(index.column())
       {
       case voltage:
       {
           finData.at(index.row()).potential.setMPotential(value.toString().toStdString());
           break;
       }
       case depth:
       {
           finData.at(index.row()).depth = value.toString().toDouble();
           break;
       }
       case freg:
       {
           finData.at(index.row()).freq = value.toString().toInt();
           break;
       }
       case longitude:
       {
           finData.at(index.row()).longitude.setGMLongitude(value.toString());
           break;
       }
       case latitude:
       {
          finData.at(index.row()).latitude.setMLatitude(value.toString());
           break;
       }
       case height:
       {
           finData.at(index.row()).height = value.toInt();
           break;
       }
       case date:
       {
            finData.at(index.row()).date.setData(value.toString());
           break;
       }
       case time:
       {
           finData.at(index.row()).time.setTime(value.toString()) ;
           break;
       }
       case length:
       {
           finData.at(index.row()).distance =  value.toString().toDouble();  ;
           break;
       }
       }
        return true;
    }
    return false;
}

int FinalData::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return finData.size();
}

int FinalData::columnCount(const QModelIndex &parent) const
{
   Q_UNUSED(parent);
   return DataLine::get_cols();
}

QVariant FinalData::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(role != Qt::DisplayRole)
           return QVariant();
   if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
       return header_data.at(section); // заголовки столбцов
   }else{
       return QString("%1").arg( section + 1 ); // возвращаем номера строк
   }
}

Qt::ItemFlags FinalData::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
FinalData::~FinalData()
{

}


bool FinalData::creatingData()
{
    QString filename = QFileDialog::getOpenFileName(0, tr("Open File"), QString(),
                                                    "Text Files (*.txt);; Data Files (*.ssv)");
    if( !filename.isEmpty() )
    {
        beginResetModel();
       //filename;
        if (filename!= "") {
            QFile file(filename);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(0, tr("Error"), tr("Could not open file"));
                return false;
            }
            try
            {
                RawData rawData(filename.toStdString() );
                clear();
                load( rawData );
            } catch(DataFileError error)
            {
                QMessageBox quitMsg;
                quitMsg.setWindowTitle("Error open file!");
                quitMsg.setText("Invalid file "+QString(error.what())+"\nDo you want to try again?\n");
                quitMsg.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
                if (quitMsg.exec() == QMessageBox::Yes)
                    creatingData();
                else
                    return false;
            }
                   }
         return true;
    }
    return false;
}

bool FinalData::writeData(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(0, tr("Error"), QString(tr("Could not open file %1").arg(filename)));
        return false;
    }
    qDebug()<<filename;
    std::ofstream  fileToWrite;
       fileToWrite.open(filename.toStdString().c_str());
       fileToWrite << *this;
       file.close();
       fileToWrite.close();
       return true;
}
bool FinalData::readData()
{
    QString filename = QFileDialog::getOpenFileName(0, tr("Open File"), QString(),
     "MGP File (*.mgv)");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(0, tr("Error"), QString(tr("Could not open file %1").arg(filename)));
        return false;
    }
    if( !filename.isEmpty() )
    {
        beginResetModel();
        std::ifstream  fileOpen;
        fileOpen.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        fileOpen.open(filename.toStdString().c_str());
        try
            {
        fileOpen >> *this;
        } catch(runtime_error error)
        {
        QMessageBox quitMsg;
         quitMsg.setWindowTitle("Error open file!");
         quitMsg.setText("Файл невірний або пошкоджений\n" +QString(error.what()) +"\nБажаєте вибрати коректний файл?\n");
         quitMsg.setStandardButtons(QMessageBox::Yes| QMessageBox::Cancel);
         if (quitMsg.exec() == QMessageBox::Yes)
          readData();
          else return false;
         }

        fileOpen.close(); /*DataFileError error*/
        file.close();
        endResetModel();
     return true;
    }
    return false;
}
