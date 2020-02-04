#include "date.h"

int datecmp(const Date *d1, const Date *d2){
    return d1->year > d2->year ? 3 : 
        d1->year < d2->year ? -3 : 
            d1->month > d2->month ? 2 : 
                d1->month < d2->month ? -2 : 
                    d1->day > d2->day ? 1 :
                        d1->day < d2->day ? -1 : 0;
}