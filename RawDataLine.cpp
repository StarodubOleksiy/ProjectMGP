#include "RawDataLine.h"

using namespace std;
RawDataLine::RawDataLine(data_type& tempData)
{


 data_type_itr itr = tempData.begin();
 if(*itr!= '$' )
           {
               throw DataFileError("No $ sign at line start.");
           }
 data_type_itr nextf = itr;
 itr = find(nextf, tempData.end(), ',');
 copy(nextf, itr, back_inserter(delim));
 process_next_field(tempData, polar,itr);
 process_next_field(tempData, potential,itr);
 process_next_field(tempData, range,itr);
 process_next_field(tempData, depth,itr);
 process_next_field(tempData, freq,itr);
 process_next_field(tempData, g_a,itr);
 process_next_field(tempData, longitude,itr);
 process_next_field(tempData, latitude,itr);
 process_next_field(tempData, height,itr);
 process_next_field(tempData, date,itr);
  nextf = itr;
 itr +=7;
  copy(++nextf, itr, back_inserter(time));

}

void RawDataLine::process_next_field(data_type &tempData, data_type &output, data_type_itr &itr)
{
data_type_itr nextf = itr;
itr = find(++nextf, tempData.end(), ',');
copy(nextf, itr, back_inserter(output));
}
 data_type& RawDataLine::getPolar()
  {
      return polar;
  }
 data_type& RawDataLine::getRange()
  {
      return range;
  }
 data_type& RawDataLine::getPotential()
  {
      return potential;
  }



double  RawDataLine::makeDepth() const
{
    const int base = 10;
    int tempValue = get_number(depth.begin(), 3, base);
    double result= static_cast<double>(tempValue)/100;
    return result;
}

    int  RawDataLine::makeFreq() const
    {
        data_type_citr itr = freq.begin();

        int result=-1;
         if (*itr == 'S')
            result = 100;
        else
           result = 244;
           return result;

    }

    int  RawDataLine::makeHeight() const
    {
       int base = 100;
        int result = 0;
        data_type_citr checkItr = height.begin();
        if(*checkItr == 'x')
        {
         return invalid_height;
        }

        for(data_type_citr itr = height.begin(); itr!=height.end(); ++ itr)
        {
            result  = result+( *itr & 0xF )*base;
            base/=10;
        }
        return result;

    }


  const data_type& RawDataLine::getLongitude() const
    {
        return longitude;
    }

  const   data_type& RawDataLine::getLatitude() const
    {
        return latitude;
    }
   const  data_type& RawDataLine::getDate() const
    {
        return date;
    }
  const   data_type& RawDataLine::getTime() const
    {
        return time;
    }


int RawDataLine::get_Range_Size()
{
    return range.size();
}



std::ostream& operator<< (std::ostream& os, const RawDataLine& rd)
{
    os<<" |";
    RawDataLine::printDataAsHex(os, rd.delim);
    os<<" |";
    RawDataLine::printDataAsHex(os, rd.polar);
    os<<" |";
    RawDataLine::printDataAsHex(os, rd.potential);
     os<<" |";
    RawDataLine::printDataAsHex(os, rd.range);
     os<<" |d=";
    RawDataLine::printDataAsHex(os, rd.depth);
     os<<" |";
    RawDataLine::printDataAsHex(os, rd.freq);
     os<<" |";
    RawDataLine::printDataAsHex(os, rd.g_a);
    RawDataLine::printDataAsHex(os, rd.longitude);
    RawDataLine::printDataAsHex(os, rd.latitude);
    RawDataLine::printDataAsHex(os, rd.height);
    os<<" |";
    RawDataLine::printDataAsHex(os, rd.date);
    os<<" |";
    RawDataLine::printDataAsHex(os, rd.time);
    return os;
}

