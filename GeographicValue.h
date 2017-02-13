#ifndef GEOGRAPHICVALUE_H
#define GEOGRAPHICVALUE_H

#include <QStringList>
#include "RawData.h"
class GeographicValue
{
int degree,minute;
protected:
virtual void init(int ideg, int im)
 {
     degree = ideg;
     minute = im;
 }
public:
    GeographicValue();
    GeographicValue(int ideg, int im);

    std::string toString() const;
     QString toQString() const ;

   GeographicValue(const data_type& rt);
//void setGeographicValue(QString string);

friend std::ostream& operator<< (std::ostream& os, const GeographicValue& t);
friend std::istream& operator>> (std::istream& is,  GeographicValue& t);
};



class MLongitude: public GeographicValue
{
public:
    MLongitude()
    {
      GeographicValue();
    }
    MLongitude(const data_type& rt): GeographicValue(rt) {}
    virtual void init(int ideg, int im)
         {
          /*  if( ideg > 90)
             {
                 throw LongitudeFormatError("Wrong Longitude");
             } else*/
        if( ideg > 91)
           ideg = 0;
           GeographicValue::init(ideg,im);

         }
    void setGMLongitude(QString string)
    {
      QStringList list1 = string.split(".");
      int ideg = list1[0].toInt();
      int im = list1[1].toInt();
      init(ideg,im);
    }

};

//-------------------------------------------------------------------------------------------------------------



class MLatitude: public GeographicValue
{
public:
    MLatitude()
    {
      GeographicValue();
    }

    MLatitude(const data_type& rt): GeographicValue(rt){}
    virtual void init(int ideg, int im)
      {
         /*if( ideg > 90)
          {
              throw LongitudeFormatError("Wrong Latitude");
          } else*/
        if( ideg > 91)
           ideg = 0;
         GeographicValue::init(ideg,im);

      }
    void setMLatitude(QString string)
    {
      QStringList list1 = string.split(".");
      int ideg = list1[0].toInt();
      int im = list1[1].toInt();
      init(ideg,im);
    }

};

#endif // GEOGRAPHICVALUE_H
