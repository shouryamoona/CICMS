#ifndef PERISHABLEFOOD_H
#define PERISHABLEFOOD_H

#include <string>
#include <iostream>
#include "Product.h"

using namespace std;

class PerishableFood: public Product
{
protected:
	int _expdate;
	double _discount;

public:
	PerishableFood(char per,string name,string cat,int barnum,double price,string manu,int stock,int numsoldpermth,int expdate,double discount);
	~PerishableFood();

	bool ifExpired();
	bool hasExpired(int currDate);
	int getexpirydate();
	double getdiscount();

};

#endif