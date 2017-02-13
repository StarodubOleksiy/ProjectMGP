#include "RawData.h"
#include <QDebug>
//#define Debug
//#define inData
using namespace std;

RawData::RawData(const string& filename)
{

    ifstream testStream;
    testStream.open(filename.c_str() );
    if (!testStream)
     throw  FileOpenError("Impossible read file");
   string line;
   string rightFile;
   getline(testStream,line);
   copy(line.begin(), line.begin()+11, back_inserter(rightFile));
          if (rightFile!= "24 4D 47 50")
            throw DataFileError("Invalid data.");
    testStream.close();
   ifstream  hex_data;
   hex_data.open( filename.c_str() );
    data_type in_data;
    qDebug()<<"read success";
    int ti;
    hex_data >> hex;
    while( hex_data >> ti )
    {
        #ifdef inData
        qDebug()<<"Hex_data";
        qDebug()<<ti;
        #endif
        in_data.push_back(ti);
    }
    hex_data.close();
    if(in_data[0] != '$'||in_data[1] != 'M'||in_data[2] != 'G'||in_data[3] != 'P')
        throw DataFileError("No \'$\' sign at file start.");

    data_type_itr itr = find(in_data.begin()+1, in_data.end(), '$');
    if(itr  == in_data.end() )
    {
        throw DataFileError("No \'$\' sign at row start.");
    }
   data_type_itr eraseItr = in_data.begin();
in_data.erase(eraseItr);
    fillingRawData(in_data);
  }
void RawData::printRawData() const
 {

for(vector<RawDataLine>::const_iterator itr=raw_data.begin(); itr != raw_data.end(); ++itr)
    {
        cout << *itr;

        cout << endl;
    }
}




int RawData::getRaw_DataSize() const
{
return raw_data.size();
}

void RawData::fillingRawData(data_type &in_data )
{
  data_type_itr itr = find(in_data.begin(), in_data.end(), '$');//  Рядок різниця між прийняттям даних з файлу і пристрою!!!
  if(itr  == in_data.end() )
  {
      throw DataFileError("No \'$\' sign at row start.");
  }

#ifdef inData
for(size_t i = 0; i < in_data.size();++i)
    qDebug()<<in_data[i];
#endif

 cout <<"Print Raw Data";
while(itr != in_data.end() && itr+1 != in_data.end()  )
{

data_type temp_data;
 data_type_itr nextf = ++itr;
 itr = find(nextf, in_data.end(), '$');
 copy(--nextf, itr, back_inserter(temp_data));
#ifdef Debug
 cout   <<"temp";
 for(size_t i = 0 ; i < temp_data.size(); ++i)
 {
 cout   <<temp_data[i];
 }
 cout   <<endl;
#endif
 RawDataLine tempObj(temp_data);
 raw_data.push_back(tempObj);
}

}


