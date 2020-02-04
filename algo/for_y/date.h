
#ifndef DATE_H
#define DATE_H

typedef struct Date {
	int year;
	int month;
	int day;
} Date;

int datecmp(const Date *d1, const Date *d2);

#endif