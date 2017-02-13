#include "DataLine.h"
#include <QDebug>
using namespace std;
DataLine::DataLine(RawDataLine& rd)
    {
        init(rd);
    }
    DataLine::DataLine():
       depth(-1), freq(-1), height(-1)
    {}

    void DataLine::init(RawDataLine& rd)
    {
    potential = MPotential(rd.getPolar(),rd.getPotential(),rd.getRange());
    depth = rd.makeDepth();
    freq = rd.makeFreq();
    height = rd.makeHeight();
    data_type_citr tempLongitude = rd.getDate().begin();
    if (*tempLongitude=='x')
    {
    longitude.init(91,50);
    } else
    longitude = MLongitude(rd.getLongitude());
    data_type_citr tempLatitude = rd.getDate().begin();
    if (*tempLatitude=='x')
    {
    latitude.init(91,50);
    } else
    latitude = MLatitude(rd.getLatitude());
    data_type_citr tempDate = rd.getDate().begin();
    if (*tempDate=='x')
      {
       date = MDate(00,00,1800);
      } else
    date = MDate(rd.getDate());
    time = MTime(rd.getTime());
     }



void DataLine::setDepth(double dpt)
{
    depth = dpt;
}

void DataLine::setFreq(int fr)
{
    freq = fr;
}

void DataLine::setHeight(int hgt)
{
    height = hgt;
}


void DataLine::setPotential(string string)
{
 potential.setMPotential(string);
}

void DataLine::setLatitude(QString string)
{
 latitude.setMLatitude(string);
}
void DataLine::setLongitude(QString string)
{
longitude.setGMLongitude(string);
}
void DataLine::setData(QString string)
{
date.setData(string);
}

void DataLine::setTime(int ih, int im, int is)
{
  time.setTime(ih, im, is);
}

MPotential &DataLine::getMPotential()
{
 return potential;
}

double DataLine::getDepth()const
{
 return depth;
}

MLongitude &DataLine::getMLongitude()
{
    return longitude;
}


MLatitude &DataLine::getMLatitude()
{
    return latitude;
}
void DataLine::print(ostream& os, const DataLine& dt) const
{
  os << setw(def_double_width) << dt.potential << " \t";
  os << setw(def_double_width) << dt.depth << " \t";
  os << setw(def_int_width) << dt.height << " \t";
  os << setw(def_int_width) << dt.freq << " \t";
  os << setw(def_int_width) << dt.longitude << " \t";
  os << setw(def_int_width) << dt.latitude << " \t";
  os << setw(def_int_width) << dt.date << " \t";
  os << setw(def_double_width) << dt.time << " \t";
  os << setw(def_double_width) << dt.distance << " \t";
}
ostream& operator<<(ostream &os, const DataLine& dt)
{
    dt.print(os, dt);
    return os;
}


istream& operator>>(istream &is, DataLine& dt)
{
    is >> dt.potential;
    is >> dt.depth ;
    is >> dt.height ;
    is >> dt.freq ;
    is >> dt.longitude ;
    is >> dt.latitude ;
    is >> dt.date ;
    is >> dt.time ;
    is >> dt.distance ;
    return is;
    // НАПИСАТИ!

}

void DataLine::print_table_header(std::ostream &os)
    {
        os << std::setw(def_double_width) << "Potential" << " \t";
        os << std::setw(def_double_width) << "Depth" << " \t";
        os << std::setw(def_int_width) << "Height"<< " \t";
        os << std::setw(def_int_width) << "Freq" << " \t";
        os << std::setw(def_int_width) << "Longitude" << " \t";
        os << std::setw(def_int_width) << "Latitude" << " \t";
        os << std::setw(def_int_width) << "Date" << " \t";
        os << std::setw(def_int_width) << "Time" << " \t";
        os << std::setw(def_int_width) << "Distance" << " \t";
    }
