#include "PerishableFood.h"
#include "Product.h"
#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;

PerishableFood::PerishableFood(char per,string name,string cat,int barnum,double price,string manu,int stock,int numsoldpermth,int expdate,double discount)
	:Product(per, name, cat, barnum, price, manu, stock, numsoldpermth)
{
	_expdate=expdate;
	_discount=discount;
}

PerishableFood::~PerishableFood()
{
}

bool PerishableFood::ifExpired()
{
	struct tm *newtime;
	__time64_t long_time;

	_time64( &long_time );                // Get time as long integer. 
	newtime = _localtime64( &long_time ); // Convert to local time. 

	int curyear = (newtime ->tm_year) + 1900;
	int curdate = (newtime ->tm_mday);
	int curmonth = (newtime ->tm_mon) + 1;

	int i=getexpirydate();

	int date,month,year;

	year = i%10000;
	i=i/10000;

	month=i%100;
	date=i/100;

	if (year<curyear)
	{
		return true;
	}
	else if(month<curmonth)
	{
		return true;
	}
	else if(date<=curdate)
	{
		return true;
	}
	return false;
}

bool PerishableFood::hasExpired(int currDate)
{
	int i=getexpirydate();

	int date, month, year;
	year = i%10000;
	i = i/10000;
	month = i%100;
	date = i/100;

	int cdate, cmonth, cyear;
	cyear = currDate%10000;
	currDate = currDate/10000;
	cmonth = currDate%100;
	cdate = currDate/100;

	if (year<cyear)
	{
		return true;
	}
	else if(month<cmonth)
	{
		return true;
	}
	else if(date<=cdate)
	{
		return true;
	}
	return false;
}

int PerishableFood::getexpirydate()
{
	return _expdate;
}

double PerishableFood::getdiscount()
{
	return _discount;
}
