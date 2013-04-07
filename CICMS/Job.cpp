#include "Job.h"
#include "Operations.h"


Job::Job()
{}

Job::Job(string name, string cat, int barnum, double price, string manu, int stock)
{
	_name=name;
	_cat=cat;
	_barnum=barnum;
	_price=price;
	_manu=manu;
	_stock=stock;
	_stockorexporsale=NULL;
	_typeofJobs = "A";
}

Job::Job(int barnum)
{
	_name="error";
	_cat="error";
	_barnum=barnum;
	_price=NULL;
	_manu="error";
	_stock=NULL;
	_stockorexporsale=NULL;
	_typeofJobs = "D";
}

Job::Job(int barnum,int stockorexporsale, string typeofJobs)
{
	_name="error";
	_cat="error";
	_barnum=barnum;
	_price=NULL;
	_manu="error";
	_stock=NULL;
	_stockorexporsale=stockorexporsale;
	_typeofJobs = typeofJobs;
}

Job::~Job()
{}

string Job::getName()
{
	return _name;
}

string Job::getCat()
{
	return _cat;
}

string Job::getManu()
{
	return _manu;
}

double Job::getPrice()
{
	return _price;
}

int Job::getBarNum()
{
	return _barnum;
}

int Job::getStock()
{
	return _stock;
}

int Job::getNumsoldpermth()
{
	return _Numsoldpermth;
}

int Job::getStockorexporsale()
{
	return _stockorexporsale;
}

string Job::getTypeOfJobs()
{
	return _typeofJobs;
}

int Job::getJobType()
{
	if(getTypeOfJobs() == "A")
		return 0;	// ADD
	else if(getTypeOfJobs() == "D")
		return 1; // DELETE
	else if(getTypeOfJobs() == "r")
		return 2; // RESTOCK
	else if(getTypeOfJobs() == "d")	
		return 3; // DISPOSE
	else if(getTypeOfJobs() == "s")
		return 4; // SALE
	else
		return -1;	// error
}

bool Job::dojob1(Database &Data,string name, string cat, int barnum, double price, string manu, int stock) //add product
{
	if( Data.addProd('n', _name, _cat, _barnum, _price, _manu, _stock, 0, 0, 0) )
		return true;
	else
		return false;
}

bool Job::dojob2(Database &Data,int barnum) //delete product
{
	if( Data.delProd(_barnum) )
		return true;
	else
		return false;
}

bool Job::dojob3(Database &Data,int barnum,int stockorexporsale) //restock product
{
	Operations instance;
	if( instance.RestockProd(Data, _barnum, _stockorexporsale) )
		return true;
	else
		return false;
}

bool Job::dojob4(Database &Data,int barnum,int stockorexporsale) //dispose perishable product
{	
	vector<int> vect;
	if( !Data.SearchProdByBarNum(barnum, vect) )
		return false;

	for(int i=0;i<Data.getindex();i++)
	{
		Product *p=NULL;
		Data.getinven()->retrieve(i,p);
		bool check=p->hasExpired(stockorexporsale);
		if(barnum == p->getbarnum())
		{
			if( (p->isPerishable() == 'n') || p->hasExpired(stockorexporsale)==false )
				return false;
			else
			{
				p->ResetStock();
				return true;
			}
		}
	}
}

bool Job::dojob5(Database &Data,int barnum,int stockorexporsale) //sale of product
{
	Operations instance;
	if( instance.SellProd(Data, _barnum, _stockorexporsale) )
		return true;
	else 
		return false;
}


