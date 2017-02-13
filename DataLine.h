#ifndef DATALINE_H
#define DATALINE_H

#include "MTime.h"

class DataLine
{
    friend class FinalData;
MPotential  potential;
MLongitude longitude;
MLatitude latitude;
double  depth;
double distance;
protected:
virtual void print(std::ostream& s, const DataLine& d) const;
public:
    int     freq;
    int     height;
    MDate date;
    MTime time;
    inline static size_t get_cols() { return 9; }
    void setDepth(double dpt);
    void setFreq(int fr);
    void setHeight(int hgt);
    void setPotential(char  polarnist, double volt);
    void setPotential(std::string string);
    void setLongitude(QString string);
    void setLatitude(QString string);
    void setData(QString string);
    void setTime(int h, int m, int s);
    double getDepth()const;
    MPotential  &getMPotential();
    MLongitude &getMLongitude();
    MLatitude &getMLatitude();


    DataLine(RawDataLine& rd);

    DataLine();

    void init(RawDataLine& rd);

    friend std::ostream& operator<<(std::ostream &os, const DataLine& dt);
    friend std::istream& operator>>(std::istream &is, DataLine& dt);
    static void print_table_header(std::ostream &os);

};

std::ostream& operator<<(std::ostream &os, const DataLine& dt);
std::istream& operator>>(std::istream &is, DataLine& dt);


#endif // DATALINE_H
