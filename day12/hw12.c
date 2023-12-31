#define TRUE              -1
#define FALSE             0
#define MINYEAR           2021
#define MAXYEAR           2031
#define HOLIDAYNAMELENGTH 50
#define FIX               0
#define HAPPY             1

#include <stdio.h>

typedef struct {
    int year;
    int month;
    int day;
} date_t;

typedef struct {
    int type;
    int end_year;
    int start_year;
    int month;
    int day_or_week;
    char *name;
} holiday_t;

char *monthname[] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char *dayweekname[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int   isvaliddate(date_t d);
char *getholidayname(date_t d);
char *getdaysuffix(int day);
int   getdayweek(date_t d);
int   getweeks(int day);

int main( int argc, char *argv[] )
{
    date_t today;

    printf("Type year, month and day and Enter.:");
    fflush(stdout);
    if(scanf("%d %d %d", &(today.year), &(today.month), &(today.day))!=3 || !isvaliddate(today) ) {
        printf("Error. Illegal date.\n");
        return -1;
    }

    printf("Today is the %d%s of %s, %s, %d. It is %s.\n", today.day, getdaysuffix(today.day), monthname[today.month], dayweekname[getdayweek(today)], today.year, getholidayname(today) );
    return 0;
}

int isvaliddate(date_t d)
{
    static int daynum[]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    date_t day229={d.year,2,29}, day301={d.year,3,1};
    if(d.month == 2 && (getdayweek(day229) != getdayweek(day301))) {
        daynum[2]++;
    }

    if(d.year < MINYEAR || d.year > MAXYEAR) return FALSE;
    if(d.month < 1 || d.month > 12) return FALSE;
    if(d.day < 1 || d.day > daynum[d.month]) return FALSE;

    return TRUE;
}

char *getholidayname(date_t d)
{
    static holiday_t holidays[] = {
        {FIX, MAXYEAR, 1948, 1, 1, "New Year's Day" },
        {HAPPY, MAXYEAR, 2000, 1, 2, "Coming of Age Day" },
        {FIX, MAXYEAR, 1967, 2,11, "National Foundation Day" },
        {FIX, MAXYEAR, 2007, 4,29, "Showa Day" },
        {FIX, MAXYEAR, 1948, 5, 3, "Constitution Memorial Day" },
        {FIX, MAXYEAR, 2007, 5, 4, "Greenery Day" },
        {FIX, MAXYEAR, 1949, 5, 5, "Children's Day" },
        {HAPPY, MAXYEAR, 2003, 7, 3, "Marine Day" },
        {HAPPY, MAXYEAR, 2003, 9, 3, "Respect for the Aged Day" },
        {HAPPY, MAXYEAR, 2000, 10, 2, "Health and Sports Day" },
        {FIX, MAXYEAR, 1946, 11, 3, "Culture Day" },
        {FIX, MAXYEAR, 1948, 11, 23, "Labor Appreciation Day" },
        {FIX,       0,    0, 0, 0, "no holiday" },
    };

    holiday_t *ph;

    for(ph=holidays; ph->end_year != 0; ph++) {
        if(d.year < ph->start_year || d.year > ph->end_year) continue;
        if(d.month != ph->month) continue;
        
        if(ph->type == FIX) {
            if(d.day == ph->day_or_week) break;
        } else {
            if(getweeks(d.day) == ph->day_or_week && getdayweek(d) == 1) break;
        }
    }
    return ph->name;
}

char *getdaysuffix(int day)
{
    static char *suffix[]={"th", "st", "nd", "rd" };
    int last_1_digit = day % 10;

    switch(last_1_digit) {
        case 1:
        case 2:
        case 3:
            return suffix[last_1_digit];
            break;
    }
    return suffix[0];
}

int getweeks(int d)
{
	return ((d-1)/7+1);
}


int getdayweek(date_t d)
{
	if((d.month==1) || (d.month==2)) {
		d.year-=1; d.month+=12;
	}
	return (d.year+d.year/4-d.year/100+d.year/400+(13*d.month+8)/5+d.day)%7;
	/* return a day of the week in figures (sun:0, mon:1, ...) */ 
}