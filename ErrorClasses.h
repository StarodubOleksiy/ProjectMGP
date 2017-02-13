#ifndef ERRORCLASSES_H
#define ERRORCLASSES_H

#include "InitialTypes.h"
const int def_double_width=10;
const int def_int_width=6;

class MPotentialFormatError: public std::runtime_error
{
public:
    MPotentialFormatError(const std::string& s): runtime_error(s) {}

};

class DataFileError: public std::runtime_error
{
public:
    DataFileError(const std::string& s): runtime_error(s) {}

};

class TimeFormatError : public DataFileError
{
 public:
    TimeFormatError(const std::string& s): DataFileError(s) {}
};

class LongitudeFormatError : public DataFileError
{
 public:
    LongitudeFormatError(const std::string& s): DataFileError(s) {}
};
class LatitudeFormatError : public DataFileError
{
 public:
    LatitudeFormatError(const std::string& s): DataFileError(s) {}
};
class DateFormatError : public DataFileError
{
 public:
    DateFormatError(const std::string& s): DataFileError(s) {}
};

#endif // ERRORCLASSES_H
