#ifndef INITIALTYPES_H
#define INITIALTYPES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <cmath>

typedef std::vector<unsigned char> data_type;
typedef std::vector<unsigned char>::iterator data_type_itr;
typedef std::vector<unsigned char>::const_iterator data_type_citr;

unsigned get_number(data_type_citr itr, size_t n, size_t base );

#endif // INITIALTYPES_H
