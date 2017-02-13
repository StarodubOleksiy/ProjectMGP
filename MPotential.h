#ifndef POTENTIAL_H
#define POTENTIAL_H
#include "GeographicValue.h"
class MPotential
{
private:
    double voltage;
    char positive;
public:
    MPotential();

    void init(char  polarnist, double volt);
    MPotential(const data_type& polarnist,const data_type& voltage,const data_type& range);
    friend std::ostream& operator<< (std::ostream& os, const  MPotential& t);
    std::string toString() const ;
    QString toQString() const ;
    friend std::istream& operator>> (std::istream& os,  MPotential& t);
    void setMPotential(char  polarnist, double volt );
    void setMPotential(std::string string);

};

#endif // POTENTIAL_H
