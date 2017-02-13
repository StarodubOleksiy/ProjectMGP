#include "InitialTypes.h"

unsigned get_number(data_type_citr itr, size_t n, size_t base )
{
    unsigned res = 0;
    for(size_t i=0; i<n; ++i)
    {
        res *= base;
        res += ( *(itr+i) & 0xF );
    }
    return res;
}
