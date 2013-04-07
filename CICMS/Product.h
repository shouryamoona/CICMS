#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product
{
protected:
	string _name;
	string _cat;
	int _barnum;
	double _price;
	string _manu;
	int _stock;
	int _numsoldpermth;
	char _per;

public:
	Product(char per, string name, string cat, int barnum, double price, string manu, int stock, int numsoldpermth);
	~Product();

	string getname();
	string getcat();
	int getbarnum();
	double getprice();
	string getmanu();
	int getstock();
	int getnumsoldpermth();
	char isPerishable(); 
	
	bool Sell(int qty);
	bool ResetSales();
	bool Restock(int qty);
	bool ResetStock();
	virtual int getexpirydate();
	virtual double getdiscount();
	virtual bool ifExpired(){return false;}
	virtual bool hasExpired(int currDate){return false;}
};

#endif
