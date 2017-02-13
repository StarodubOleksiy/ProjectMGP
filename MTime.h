#ifndef MTIME_H
#define MTIME_H

#include "MDate.h"
class MTime
{
private:
    int seconds, minutes, hours;
public:
    MTime();
    MTime(int ih, int im, int is);


    void init(int ih, int im, int is);


    MTime(const data_type& rt);
    std::string toString() const;
    void setTime(int h, int m, int s);
    void setTime(QString time);
    QString toQString() const ;
    friend std::ostream& operator<< (std::ostream& os, const MTime& t);
    friend std::istream& operator>> (std::istream& is, MTime& t);
};

#endif
