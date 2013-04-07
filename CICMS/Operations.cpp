#include "Operations.h"


Operations::Operations()
{}

bool Operations::ResetProdSales(Database &Data, int barnum)
{
	vector<int> vect;
	if( !Data.SearchProdByBarNum(barnum, vect) )
		return false;

	for(int i=0;i<Data.getindex();i++)
	{
		Product *p=NULL;
		Data.getinven()->retrieve(i,p);

		if(barnum==p->getbarnum())
		{
			if( p->ResetSales() );
				return true;
		}
	}
	return false;
}

bool Operations::RestockProd(Database &Data, int barnum,int qty)
{
	vector<int> vect;
	if( !Data.SearchProdByBarNum(barnum, vect) )
		return false;

	for(int i=0;i<Data.getindex();i++)
	{
		Product *p=NULL;
		Data.getinven()->retrieve(i,p);

		if(barnum==p->getbarnum())
		{
			p->Restock(qty);
			return true;
		}
	}
	return false;
}

bool Operations::SellProd(Database &Data, int barnum,int qty)
{
	vector<int> vect;
	if( !Data.SearchProdByBarNum(barnum, vect) )
		return false;

	Product *p;
	for (int i=0;i<Data.getindex();i++)
	{
		
		Data.getinven()->retrieve(i,p);
		if(barnum==p->getbarnum())
		{
			if( qty > p->getstock() )
				return false;
			else
			{
				p->Sell(qty);
				return true;
			}
		}
	}
	return false;
}

bool Operations::LoadBatch(Database &Data,BatchProcess &bjobs)
{
	if( bjobs.loadJobs() == false )
		return false;
	if( bjobs.processJobs(Data) == false )
		return false;
	if( bjobs.saveLog() == false )
		return false;

	return true;
}


