#ifndef DATE_H
#define DATE_H

typedef struct {

	int d_;
	int m_;
	int y_;

}Date;

// set functions

Date* set_date(Date* p, int d, int m, int y);
Date* set_today(Date* p);
Date* set_date_from_str(Date* p, const char* str); //12-05-1987
Date* set_random_date(Date* p);
Date* set_month_day(Date* p, int mday);
Date* set_month(Date* p, int month);
Date* set_year(Date* p, int year);
Date* increment_date(Date* p, int day);
Date* decrement_date(Date* p, int day);


// accessors - get functions
int month_day(const Date* p);
int month(const Date* p);
int year(const Date* p);
int weekday(const Date* p);
int year_day(const Date* p);


// utility functions
int cmp_date(const Date* p1, const Date* p2);
int date_diff(const Date* p1, const Date* p2); // p1 - p2
Date* ndays_after(Date* presult, const Date* psource, int n);  // return edilen adres set edilen tarihin adresi presult
Date* ndays_before(Date* presult, const Date* psource, int n);

//input - output functions

void print_date(const Date* p);
Date* scan_date(Date* p);


#endif