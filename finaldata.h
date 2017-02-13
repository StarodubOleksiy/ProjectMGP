#ifndef FINALDATA_H
#define FINALDATA_H

#include <QAbstractTableModel>
#include "DataLine.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <QVector>
#include <QApplication>
#include <QTextStream>
#include <QInputDialog>
#include <QtDebug>
#include <QAction>
#include <QResizeEvent>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QVector>

enum values{voltage,depth,freg,longitude,latitude,height,date,time,length};

class FinalData : public QAbstractTableModel {
    Q_OBJECT
    std::vector<DataLine> finData;
    size_t ncol;
    size_t nrow;
    QStringList header_data;
    const int radiusEarth = 6372795;
protected:
virtual void print(std::ostream& s, const FinalData& d) const;
public:
    FinalData(QObject *parent = 0);
    void setRawData( RawData &rawData);

    void load( RawData &rawData);

    inline size_t get_rows() const { return finData.size(); }
    inline static size_t get_cols() { return DataLine::get_cols(); }

    inline void clear() { finData.clear(); }

    inline DataLine& operator[](size_t idx){ return  finData[idx]; }
    inline const DataLine& operator[](size_t idx) const { return finData[idx]; }
        bool creatingData();
        bool readData();
        void loadData();
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        void getDateAndTime(const QModelIndex& index, QString &date,QString &time);
        ~FinalData();
        double getItemDepth(int index)const;
        std::string getItemPotential(int index)const;
        int getSizeItemData()const;
        bool writeData(QString filename);
        void checkingFinalData();


    friend std::ostream& operator << (std::ostream& s, const FinalData& d);
    friend std::istream& operator >> (std::istream& s, FinalData& d);

};

std::ostream& operator << (std::ostream& s, const FinalData& d);
std::istream& operator >> (std::istream& s, FinalData& d);

#endif // FINALDATA_H
