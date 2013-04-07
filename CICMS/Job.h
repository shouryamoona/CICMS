#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <string>

#include "Database.h"
//#include "Operations.h"

using namespace std;

class Job
{
private:
	string _name, _cat, _manu;
	double _price;
	int _barnum, _stock, _Numsoldpermth;
	int _stockorexporsale;
	string _typeofJobs;

public:
	Job();
	Job(string name, string cat, int barnum, double price, string manu, int stock);	//constructor to add product
	Job(int barnum);	//constructor to delete product
	Job(int barnum,int stockorexporsale, string typeofJobs);	//contructor to restock product/dispose perishable goods/sale of goods
	~Job();

	string getName();
	string getCat();
	string getManu();
	double getPrice();
	int getBarNum();
	int getStock();
	int getNumsoldpermth();
	int getStockorexporsale();
	string getTypeOfJobs();
	int getJobType();

	bool dojob1(Database &Data,string name, string cat, int barnum, double price, string manu, int stock); //add product
	bool dojob2(Database &Data,int barnum); //delete
	bool dojob3(Database &Data,int barnum,int stockorexporsale); //restock
	bool dojob4(Database &Data,int barnum,int stockorexporsale); //dispose perishable prod
	bool dojob5(Database &Data,int barnum,int stockorexporsale); //sale of product
	
};

#endif