#ifndef RAWDATA_H
#define RAWDATA_H

#include "RawDataLine.h"
#include <QTextStream>

class FileOpenError: public DataFileError
{
public:
//std::string origin;
 FileOpenError(const std::string& s): DataFileError(s)// {}
{
// origin = orig;
}

} ;

class RawData
{
private:
    std::vector<RawDataLine> raw_data;
public:
    RawData(const std::string& filename);

    void printRawData() const;

    int getRaw_DataSize() const;

    inline const std::vector<RawDataLine>& getRawData() const
    {
        return raw_data;
    }
RawData()
{
}
    //void copyRaw_Date(std::vector<RawDataLine> &final_data);
void fillingRawData(data_type &in_data);

};

#endif // RAWDATA_H
