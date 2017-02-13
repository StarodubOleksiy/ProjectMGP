#ifndef MDATE_H
#define MDATE_H


#include "MPotential.h"
class MDate
{
private:
    int year, month, day;

public:
    MDate();
    bool dataReceived;

    MDate(int iday, int im, int iy);

    void init(int iday, int im, int iy);
    MDate(const data_type& rt);
    friend std::ostream& operator<< (std::ostream& os, const  MDate& t);
    std::string toString() const;
    QString toQString() const ;
    friend std::istream& operator>> (std::istream& os,  MDate& t);
    void setData(QString string);
    void setDataNotReceived();
    bool getDataNotReceived()const;


};

#endif
