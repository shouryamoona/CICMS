#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <string>
#include <vector>
#include "Database.h"
#include "Product.h"
#include "BatchProcessing.h"

using namespace std;

class Operations
{
public:
	Operations();

	bool ResetProdSales(Database &Data, int barnum);
	bool SellProd(Database &Data, int barnum, int qty);
	bool RestockProd(Database &Data,int barnum, int qty);
	bool LoadBatch(Database &Data,BatchProcess &bjobs);

};

#endif