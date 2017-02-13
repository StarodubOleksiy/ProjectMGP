#include "MTime.h"
#include "InitialTypes.h"


using namespace std;
    MTime::MTime():
        seconds(0), minutes(0), hours(0)
    {}

    MTime::MTime(int ih, int im, int is)
    {
        init(ih,im,is);
    }

    void MTime::init(int ih, int im, int is)
    {
        seconds = is;
        minutes = im;
        hours = ih;
      /*  if( seconds >= 60 || seconds < 0 )
        {
            throw TimeFormatError("Wrong seconds");
        }
        if( minutes  >= 60 || minutes < 0 )
        {
            throw TimeFormatError("Wrong minutes");
        }
        if( hours >= 24 || hours < 0 )
        {
            throw TimeFormatError("Wrong hours");
        }*/
        if( seconds >= 60 || seconds < 0 )
                {
                    seconds = 0;
                }
                if( minutes  >= 60 || minutes < 0 )
                {
                    minutes = 0;
                }
                if( hours >= 24 || hours < 0 )
                {
                   hours = 0;
                }
    }

    MTime::MTime(const data_type& rt)
    {
        if( rt.size() != 6 )
        {
            throw TimeFormatError("Wrong data bytes count.");
        }
        int ih=0, im=0, is=0;
        const int base = 10;
        ih = get_number(rt.begin()+0, 2, base);
        im = get_number(rt.begin()+2, 2, base);
        is = get_number(rt.begin()+4, 2, base);

        init(ih,im,is);
    }

void MTime::setTime( int ih, int im, int is)
{
    init(ih,im,is);
}

#if 0
void MTime::setTime( QString string)
{
    QStringList list1 = string.split(":");
    int ih = list1[0].toInt();
    int im = list1[1].toInt();
    int is = list1[2].toInt();
    init(ih,im,is);
}

ostream& operator<< (ostream& os, const MTime& t)
{
    os << setfill('0') << right;
    os << setw(2) << t.hours << ':';
    os << setw(2) << t.minutes << ':';
    os << setw(2) << t.seconds;

    // Dirty trick, Homework: save and restore state, using copyfmt (19 lecture)
    os << setfill(' ');
    return os;
}
istream& operator >> (istream& is,  MTime& t)
{
    char dummy;
    is >> t.hours>>dummy>>t.minutes>>dummy>> t.seconds;
    return is;
}
#endif
ostream& operator<< (ostream& os, const MTime& t)
{
    stringstream st;
    st << setfill('0') << right;
    st << setw(2) << t.hours << ':';
    st << setw(2) << t.minutes << ':';
    st << setw(2) << t.seconds;
    os << st.str();
    return os;
}
istream& operator >> (istream& is,  MTime& t)
{
    char dummy;
    is >> t.hours>>dummy>>t.minutes>>dummy>> t.seconds;
    return is;
}
std::string MTime::toString() const
{
    std::stringstream st;
    st << std::setfill('0') << std::right;
    st << std::setw(2) << hours << ':';
    st << std::setw(2) << minutes << ':';
    st << std::setw(2) << seconds ;
    return st.str();
}

QString MTime::toQString() const
{
   QString str;
   std::stringstream st;
   st << std::setfill('0') << std::right;
   st << std::setw(2) << hours << ':';
   st << std::setw(2) << minutes << ':';
   st << std::setw(2) << seconds ;
    return str.fromStdString(st.str());

}

void MTime::setTime( QString time)
{
    QStringList list1 = time.split(":");
    int ih = list1[0].toInt();
    int im = list1[1].toInt();
    int is = list1[2].toInt();
    init(ih,im,is);
}

