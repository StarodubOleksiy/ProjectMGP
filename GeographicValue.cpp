#include "MPotential.h"
#include <QStringList>

 GeographicValue::GeographicValue():
     degree(0), minute(0)   {}

GeographicValue::GeographicValue(int ideg, int im)
 {
     init(ideg,im);
 }



GeographicValue::GeographicValue(const data_type& rt)
 {
     if( rt.size() != 8 )
     {
         throw LongitudeFormatError("Wrong data bytes count.");
     }
     int ideg=0, im=0;
     const int base = 10;
     ideg = get_number(rt.begin(), 2, base);
     im = get_number(rt.begin()+2, 6, base);

     init(ideg,im);
 }




std::string GeographicValue::toString() const
{
    std::stringstream st;
    st << std::setfill('0') << std::right;
    st << std::setw(2) << degree << '.';
    st << std::setw(6) << minute ;
    return st.str();
}

QString GeographicValue::toQString() const
{
    QString str;
    std::stringstream st;
    st << std::setfill('0') << std::right;
    st << std::setw(2) << degree << '.';
    st << std::setw(6) << minute ;
    return str.fromStdString(st.str());

}

#if 0
ostream& operator<< (std::ostream& os, const GeographicValue& t)
{
    os << setfill('0') << right;
    os << setw(2) << t.degree << '.';
    os << setw(6) << t.minute << '.';

    // Dirty trick, Homework: save and restore state, using copyfmt (19 lecture)
    os << setfill(' ');
    return os;
}

istream& operator>> (std::istream& is, GeographicValue& t)
{
    char dummy;
    is >> t.degree>> dummy >> t.minute ;
    return is;
}
#endif


std::ostream& operator<< (std::ostream& os, const GeographicValue& t)
{
    os << t.toString();
    return os;
}
std::istream& operator>> (std::istream& is, GeographicValue& t)
{
    char dummy;
    is >> t.degree>> dummy >> t.minute ;
    return is;
}

