#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>


int main(int argc, char* argv[]) {


	Date mydate;

	set_today(&mydate);

	printf("yil = %d\n", year(&mydate));
	printf("ay = %d\n", month(&mydate));
	printf("gun = %d\n", month_day(&mydate));
	printf("haftanin %d. gunu\n", weekday(&mydate) + 1); // pazar haftanın ilk günü kabul edilecek.
	printf("yilin %d. gunu\n", year_day(&mydate));

}

/*
53.video
********
OOP mantığıyla çalışan date.h adında bir kütüphane tasarlayalım. Kullanıcı bu dosyanın içerisindeki yapı elemanlarının ne olduklarını bilmesin
bizim ona sunduğumuz fonksiyonlar sayesinde ihtiyaç doğrultusunda bu kütüphaneyi kullansın.


1. test Basarili
-------

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>

int main(int argc, char *argv[]) {

	Date dx;

	set_date(&dx, 5, 8, 1987);
	print_date(&dx);

	set_today(&dx);
	print_date(&dx);

	set_date_from_str(&dx, "03-07-2023");
	print_date(&dx);


}

----------------------------------------------

2. test Basarili
-------

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>

int main(int argc, char *argv[]) {

	printf("bir tarih girin : ");
	Date dx;

	scan_date(&dx);
	print_date(&dx);


}

-----------------------------------------------

3. test Basarili
-------

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>


int main(int argc, char* argv[]) {



	int i = 0;
	for (i = 0; i < 1000; ++i) {
		Date dx;
		set_random_date(&dx);
		print_date(&dx);
		(void)getchar();
	}


}

-------------------------------------------------------
4. test Basarili
-------

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>


int main(int argc, char* argv[]) {


	Date mydate;

	set_date(&mydate, 12, 6, 1987);
	print_date(&mydate);

	set_year(&mydate, 2000);
	print_date(&mydate);

	set_month_day(&mydate, 18);
	print_date(&mydate);

	set_month(&mydate, 9);
	print_date(&mydate);


}

------------------------------------------------

5.test
------

#include <stdio.h>
#include <stdlib.h>
#include "date.h"

int main(int argc, char *argv[]) {

	Date mydate;

	set_today(&mydate);

	int i;
	for (i = 0; i < 10; ++i) {
		increment_date(&mydate, 50);
		print_date(&mydate);
		(void)getchar();
	}

	int i;
	for (i = 0; i < 10; ++i) {
		decrement_date(&mydate, 50);
		print_date(&mydate);
		(void)getchar();
	}

	return 0;
}

-----------------------------------------------------------

6. test  Basarili
--------

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>


int main(int argc, char* argv[]) {


	Date mydate;

	set_today(&mydate);

	printf("yil = %d\n", year(&mydate));
	printf("ay = %d\n", month(&mydate));
	printf("gun = %d\n", month_day(&mydate));
	printf("haftanin %d. gunu\n", weekday(&mydate) + 1); // pazar haftanın ilk günü kabul edilecek.
	//printf("yilin %d. gunu\n", year_day(&mydate));

}


------------------------------------------------------------

7. test kodu
------------

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>

void set_date_array_random(Date* p, size_t size)
{
	while (size--)
		set_random_date(p++);
}

//	Üstteki kod ile alttaki kod yaptıkları iş açısından aynı işi yaparlar.

//void set_date_array_random(Date* p, size_t size)
//{
//	size_t i;
//	for (i = 0; i < size; ++i)
//		set_random_date(p + i);
//}




void print_date_array(const Date* p, size_t size)
{
	while (size--)
		print_date(p++);
}

static int dcmp(const void* vp1, const void* vp2)
{
	return cmp_date((const Date*)vp1, (const Date*)vp2);
}

void sort_date_array(Date* p, size_t size)
{
	qsort(p, size, sizeof(*p), &dcmp);
}


int main(int argc, char *argv[]) {

	size_t n;

	printf("Kac tarih : ");
	scanf("%zu", &n);

	Date* p = (Date *)malloc(n * sizeof(Date));
	if (!p) {
		fprintf(stderr, "bellek yetersiz\n");
		return 1;
	}

	set_date_array_random(p, n);

	clock_t start = clock();
	sort_date_array(p, n);
	clock_t end = clock();
	printf("Siralama tamamlandi sure %f saniye\n", (double)(end-start) / CLOCK_PER_SEC);
	(void)getchar();


	print_date_array(p, n);

	free(p);

	return 0;
}

---------------------------------------------------------------------------------------------

8. test kodu
------------

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>

int main(int argc, char *argv[]) {

	Date birth_day;

	printf("dogum tarihinizi girin : ");
	scan_date(&birth_day);
	printf("dogum tarihiniz : ");
	print_date(&birth_day);


	Date todays_date;
	set_today(&todays_date);

	printf("Bugun : ");
	print_date(&todays_date);

	printf("Bugun hayatinizin %d. gunu\n", date_diff(&todays_date, &birth_day))

	return 0;
}

-----------------------------------------------------------------------------------

9. test kodu
------------


#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include <time.h>

int main(int argc, char *argv[]) {

	Date today;

	set_today(&today);
	printf("Bugun : ");
	print_date(&today);

	Date future_date;

	int i;
	for (i = 1; i < 2000000000; i *= 10) {
		printf("bugunden %d gun sonrasi : ", i);
		ndays_after(&future_date, &today, i);
		print_date(&future_date);
	}

	return 0;
}









*/