#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>
#include <vector>
#include "Database.h"
#include "Product.h"

class Statistics
{
public:
	Statistics();
	
	bool TopXprod(Database Data,int x,vector<int> &topx);
	string BestSaleProdByCat (Database &Data, string cat);
	string BestSaleManu (Database &Data);

};

#endif