#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include "Product.h"
#include "PerishableFood.h"
#include "ListBase.h"
#include "CDLinked.h"
#include "VectorList.h"
#include "DynamicArr.h"
#include "SortedLL.h"

using namespace std;

class Database
{
private:
	int _index;
	ListBase<Product> *inventory;
	
public:
	Database();

	ListBase<Product>* getinven();
	int getindex();
	bool addProd(char per, string name, string cat, int barnum, double price, string manu, int stock, int numsoldpermth,int exp,double disc);
	bool delProd(int barnum);
	bool LoadFile();
	string toString(int index);
	bool SaveToFile();
	string toStringPara(int index);
	bool SearchProdByName (string name,vector<int> &V);
	bool SearchProdByBarNum (int barnum, vector<int> &V);
	bool SearchProdByCat (string cat, vector<int> &V);
	bool SearchProdByManu (string manu, vector<int> &V);

};

#endif