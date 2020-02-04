#include "date.h"
#include "assert.h"
// #include "stdlib.h"

int main(int argc, char const *argv[])
{
    Date d1;
    d1.year = 0;
    d1.month = 0;
    d1.day = 0;
    
    Date d2;
    d2.year = 0;
    d2.month = 0;
    d2.day = 0;

    assert(datecmp(&d1,&d2) == 0);

    Date d3;
    d3.year = 0;
    d3.month = 0;
    d3.day = 1;
    assert(datecmp(&d1,&d3) == -1);

    d3.month = 1;
    assert(datecmp(&d1,&d3) == -2);

    d3.year = 1;
    assert(datecmp(&d1,&d3) == -3);    
    
    return 0;
}
