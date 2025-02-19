#define _CRT_SECURE_NO_WARNINGS

#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define PRIVATE			static
#define PUBLIC
#define YEARBASE		1900
#define RANDOM_YEAR_MIN	1950
#define RANDOM_YEAR_MAX	2023

#define ISLEAP(Y)		((Y) % 4 == 0 && ((Y) % 100 != 0 || (Y) % 400 == 0))
#define MDAYS(Y, M)		(daytabs[ISLEAP(Y)][M])

//--------------------------------------------------------------------------------------------------------------------------------------

PRIVATE int daytabs[][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

PRIVATE Date* set(Date* p, int d, int m, int y);
PRIVATE int is_valid_date(int d, int m, int y);
PRIVATE int totaldays(const Date* p);
PRIVATE Date* to_date(Date* p, int tdays);


//--------------------------------------------------------------------------------------------------------------------------------------

PUBLIC Date* set_month_day(Date* p, int mday)
{
	return set(p, mday, month(p), year(p));
}

PUBLIC Date* set_month(Date* p, int month)
{
	return set(p, month_day(p), month, year(p));
}

PUBLIC Date* set_year(Date* p, int year)
{
	return set(p, month_day(p), month(p), year);
}

//--------------------------------------------------------------------------------------------------------------------------------------

PUBLIC int month_day(const Date* p)
{
	return p->d_;
}

PUBLIC int month(const Date* p)
{
	return p->m_;
}

PUBLIC int year(const Date* p)
{
	return p->y_;
}
PUBLIC int weekday(const Date* p)
{
	static const int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int y = year(p);
	int m = month(p);
	int d = month_day(p);

	if (m < 3)
		y -= 1;

	return ((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7);
}

PUBLIC int year_day(const Date* p)
{
	int y = year(p);
	int m = month(p);
	
	int sum = month_day(p);

	for (int i = 1; i < m; ++i) {
		sum += MDAYS(y, i);
	}

	return sum;
}

//--------------------------------------------------------------------------------------------------------------------------------------

PUBLIC void print_date(const Date* p)
{
	static const char* const pmons[] = { "", "Ocak", "Subat", "Mart", "Nisan", "Mayis", "Haziran",
										"Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik" };

	static const char* const pdays[] = { "Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi" };

	printf("%02d %s %d %s\n", month_day(p), pmons[month(p)], year(p), pdays[weekday(p)]);

}

PUBLIC Date* scan_date(Date* p)
{
	int d, m, y;
	scanf("%d%d%d", &d, &m, &y);

	return set(p, d, m, y);
}
//--------------------------------------------------------------------------------------------------------------------------------------

PUBLIC int cmp_date(const Date* p1, const Date* p2)
{
	int y1 = year(p1);
	int y2 = year(p2);

	if (y1 != y2) {
		return y1 > y2 ? 1 : -1;
	}

	int m1 = month(p1);
	int m2 = month(p2);

	if (m1 != m2) {
		return m1 > m2 ? 1 : -1;
	}

	int d1 = month_day(p1);
	int d2 = month_day(p2);

	if (d1 != d2) {
		return d1 > d2 ? 1 : -1;
	}
}

PUBLIC Date* increment_date(Date* p, int day)
{
	return to_date(p, totaldays(p) + day);
	
}

PUBLIC Date* decrement_date(Date* p, int day)
{
	return to_date(p, totaldays(p) - day);
}


PUBLIC Date* ndays_after(Date* presult, const Date* psource, int n)
{
	return to_date(presult, totaldays(psource) + n);

}

PUBLIC Date* ndays_before(Date* presult, const Date* psource, int n)
{
	return to_date(presult, totaldays(psource) - n);
}


//--------------------------------------------------------------------------------------------------------------------------------------

PUBLIC Date* set_random_date(Date* p)
{
	int y = rand() % (RANDOM_YEAR_MAX - RANDOM_YEAR_MIN + 1) + RANDOM_YEAR_MIN;
	int m = rand() % 12 + 1;
	int d = rand() % MDAYS(y, m) + 1;

	set(p, d, m, y);
}


PUBLIC Date* set_date_from_str(Date* p, const char* str)
{
	int d = atoi(str);
	int m = atoi(str + 3);
	int y = atoi(str + 6);

	return set(p, d, m, y);
}






Date* set_today(Date* p)
{
	time_t sec;
	time(&sec);

	struct tm* tptr = localtime(&sec);

	set(p, tptr->tm_mday, tptr->tm_mon + 1, tptr->tm_year + 1900);
}


PUBLIC Date* set_date(Date* p, int d, int m, int y)
{
	return set(p, d, m, y);
}


PRIVATE int totaldays(const Date* p)
{
	int sum = year_day(p);

	for (int i = YEARBASE; i < year(p); ++i) {
		sum += ISLEAP(i) ? 366 : 365;
	}
	return sum;
}


PRIVATE Date* set(Date* p, int d, int m, int y)
{
	if (!is_valid_date(d, m, y)) {
		fprintf(stderr, "Gecersiz tarih olustu\n");
		exit(EXIT_FAILURE);
	}
	p->d_ = d;
	p->m_ = m;
	p->y_ = y;
}


PUBLIC int date_diff(const Date* p1, const Date* p2)
{
	int y1 = totaldays(p1);
	int y2 = totaldays(p2);

	return y1 - y2;

	//return totaldays(p1) - totaldays(p2);		idiomatik yapısıda kullanılabilir.
}


PRIVATE Date* to_date(Date* p, int tdays)
{
	int y = YEARBASE;

	while (tdays > (ISLEAP(y) ? 366 : 365)) {

		tdays -= (ISLEAP(y) ? 366 : 365);
		++y;
	}

	int m = 1;

	while (tdays > MDAYS(y, m)) {
		tdays -= MDAYS(y, m);
		++m;
	}

	int d = tdays;

	return set(p, d, m, y);
}


PRIVATE int is_valid_date(int d, int m, int y)
{
	return ((y >= YEARBASE) && (m > 0 && m <= 12) && (d > 0 && d <= MDAYS(y, m)));
}



