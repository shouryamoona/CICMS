#include "Product.h"

Product::Product(char per, string name, string cat, int barnum, double price, string manu, int stock, int numsoldpermth)
{
	_per = per;
	_name = name;
	_cat = cat;
	_barnum = barnum;
	_price = price;
	_manu = manu;
	_stock = stock;
	_numsoldpermth = numsoldpermth;
}

Product::~Product()
{
}

string Product::getname()
{
	return _name;
}

string Product::getcat()
{
	return _cat;
}

int Product::getbarnum()
{
	return _barnum;
}

double Product::getprice()
{
	return _price;
}

string Product::getmanu()
{
	return _manu;
}

int Product::getstock()
{
	return _stock;
}

int Product::getnumsoldpermth()
{
	return _numsoldpermth;
}

char Product::isPerishable()
{
	return _per;
}

int Product::getexpirydate()
{
	return NULL;
}

double Product::getdiscount()
{
	return NULL;
}

bool Product::Sell(int qty)
{
	if(qty<=_stock)
	{
		_stock -= qty;
		_numsoldpermth += qty;
		return true;
	}
	else
		return false;
}

bool Product::ResetSales()
{
	_numsoldpermth = 0;
	return true;
}

bool Product::Restock(int qty)
{
	_stock += qty;
	return true;
}

bool Product::ResetStock()
{
	_stock=0;
	return true;
}