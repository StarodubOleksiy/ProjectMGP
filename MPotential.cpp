#include "MPotential.h"
using namespace std;

MPotential::MPotential():
    voltage(0),positive('-')
{}



void MPotential::init(char polarnist, double volt)
{
    cout << polarnist<<" ";
if(polarnist != '-' && polarnist != '+') throw MPotentialFormatError("Wrong pothential");
    positive = polarnist;
    voltage = volt;


}

MPotential::MPotential(const data_type& rt1,const data_type& rt2,const data_type& rt3)
{
  char pos;
  data_type_citr itr_factor = rt1.begin();
  switch( *itr_factor )
         {
  case '+':
  pos='+';
  break;

  default:
  pos='-';
  break;
    }
    const int base = 10;
    int volt = get_number(rt2.begin(), 3, base);

    double result;
    itr_factor = rt3.begin();
    switch( *itr_factor )
           {
    case 'a':
    result=volt/10;
    break;
    case 'b':
    result=volt/100;
    break;

    default:
    result=volt/1000;
    break;
      }
     init(pos,result);
}


void MPotential::setMPotential(string str )
{
   string::iterator it=str.begin();
   char st= *it;
   string stri;
   stri.append(str.begin()+1,str.end());
   double temp = ::atof( stri.c_str());
   init(st,temp);
}


#if 0
std::ostream& operator<< (std::ostream& os, const  MPotential& t)
{
    std::stringstream st;
    st <<t.positive;
    st << t.voltage;
    os << st.str();
    return os;
return os;
}
std::istream& operator>> (std::istream& is, MPotential& t)
{
    is >> t.positive>> t.voltage;
    return is;
}
#endif
std::ostream& operator<< (std::ostream& os, const  MPotential& t)
{
std::stringstream st;
st << t.positive;
st << t.voltage;
os << st.str();
return os;
}
std::string MPotential::toString()const
{
std::stringstream st;
st << positive ;
st  <<voltage ;
return st.str();
}

QString MPotential::toQString() const
{
    QString str;
    std::stringstream st;
    st << positive ;
    st  <<voltage ;
    return str.fromStdString(st.str());

}

std::istream& operator>> (std::istream& is, MPotential& t)
{

is >> t.positive>> t.voltage;
return is;
}
