#include "MDate.h"
#include <QDebug>


    MDate::MDate():
        year(0), month(0), day(0),dataReceived(true)
    {}

    MDate::MDate(int iday, int im, int iy)
    {
        init(iday, im, iy);
    }

    void MDate::init(int iday, int im, int iy)
    {
        year = iy;
        month = im;
        day = iday;
        /*if( month >= 13  )
        {
            throw DateFormatError("Wrong month");
        }
        if( day  >= 32  )

        {
            throw DateFormatError("Wrong day");
        }
 */
        if( month >= 13  )
        {
            month = 0;
        }
        if( day  >= 32  )
        {
            day  = 0;
        }

    }



    MDate::MDate(const data_type& rt)
    {
        if( rt.size() != 6 )
        {
            throw DateFormatError("Wrong data bytes count.");
        }
        int iy=0, im=0, iday=0;
        const int base = 10;
        iday = get_number(rt.begin(), 2, base);
        im = get_number(rt.begin()+2, 2, base);
        iy = get_number(rt.begin()+4, 2, base)+2000;

        init(iday,im,iy);
    }

    void MDate::setData(QString string)
    {
        QStringList list1 = string.split(".");
        int iday = list1[0].toInt();
        int im = list1[1].toInt();
        int iy = list1[2].toInt();
        init(iday,im,iy);
    }
void MDate::setDataNotReceived()
    {
    qDebug()<<"Function works!!!";
      dataReceived=false;
    }
bool MDate::getDataNotReceived() const
  {
      return dataReceived;
  }

#if 0
std::ostream& operator<< (std::ostream& os, const  MDate& t)
{
    os << setfill('0') << right;
    os << setw(2) << t.day << '.';
    os << setw(2) << t.month << '.';
    os << setw(2) << t.year;

     os << setfill(' ');
    return os;
}
std::istream& operator>> (std::istream& is, MDate& t)
{
    char dummy;
    is >> t.day>>dummy>> t.month>>dummy>> t.year;
    return is;
 }
#endif
std::ostream& operator<< (std::ostream& os, const  MDate& t)
{
    std::stringstream st;
    st << std::setfill('0') << std::right;
    st << std::setw(2) << t.day << '.';
    st << std::setw(2) << t.month << '.';
    st << std::setw(2) << t.year;
    os << st.str();
    return os;
}
std::string MDate::toString() const
{
     std::stringstream st;
    st << std::setfill('0') << std::right;
    st << std::setw(2) << day << '.';
    st << std::setw(2) << month << '.';
    st << std::setw(2) << year ;
    return st.str();
}

QString MDate::toQString() const
{
    QString str;
   std::stringstream st;
   st << std::setfill('0') << std::right;
   st << std::setw(2) << day << '.';
   st << std::setw(2) << month << '.';
   st << std::setw(2) << year ;
    return str.fromStdString(st.str());

}


std::istream& operator>> (std::istream& is, MDate& t)
{
 char dummy;
 is >> t.day>>dummy>> t.month>>dummy>> t.year;
 return is;
 }
