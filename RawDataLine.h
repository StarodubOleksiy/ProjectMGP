#ifndef RAWDATALINE_H
#define RAWDATALINE_H

#include "ErrorClasses.h"


class RawDataLine
{
private:
   data_type delim,polar,potential,range, depth, freq,g_a, longitude, latitude, height, date, time;
     public:
   static const int invalid_height = 1000000;
    RawDataLine(data_type& tempData);

void process_next_field(data_type& tempData, data_type &output, data_type_itr &itr);


    int makeFreq() const;
    int makeHeight() const;
    double  makeDepth() const;


    static void print_table_header(std::ostream &os)
    {
        os << "rd.voltage";
        os << "\t|";
        os << "rd.depth";
        os << "\t|";
        os << "rd.voltage_factor";
        os << "\t|";
        os << "rd.freq";
        os << "\t|";
        os << "rd.longitude";
        os << "\t|";
        os << "rd.latitude";
        os << "\t|";
        os << "rd.height";
        os << "\t|";
        os << "rd.date";
        os << "\t|";
        os << "rd.time";
    }
static void printDataAsHex(std::ostream &os, const data_type& v)
 {
 os << std::hex << std::setfill('0');

 for(data_type_citr itr = v.begin(); itr!=v.end(); ++ itr)
  {
 os << std::setw(2) << static_cast<int>(*itr)<< ' ';
 }
        // Dirty trick, Homework: save and restore state, using copyfmt (19 lecture)
       os << std::dec << std::setfill(' ');

    }


friend std::ostream& operator<< (std::ostream& os, const RawDataLine& rd);
 data_type& getPolar() ;
 data_type& getPotential();
 data_type& getRange();
const data_type& getLongitude() const;
const   data_type& getLatitude() const;
const  data_type& getDate() const;
const   data_type& getTime() const;
int get_Range_Size() ;
};

#endif // RAWDATALINE_H
