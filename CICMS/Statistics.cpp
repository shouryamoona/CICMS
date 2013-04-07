#include "Statistics.h"
#include "Product.h"
#include <string>

Statistics::Statistics()
{}

bool Statistics::TopXprod(Database Data,int x,vector<int> &topx)
{
	vector<double> revenue;
	double maxrevenue=0,temprevenue=0;
	int iterator=0,j,k;
	int size=Data.getindex();
	Product *p;
	int flag=0;
	
	for(int i=0;i<size;i++)
	{
		Data.getinven()->retrieve(i,p);
		revenue.push_back( (p->getprice() ) * (p->getnumsoldpermth() ) );
	}

	// Check how many products have been sold
	for(int i=0;i<size;i++)
	{
		if(revenue[i]!=0)
			flag++;
	}

	if (flag>x)
		iterator=x;
	else 
		iterator=flag;

	for(int i=0;i<iterator;i++)
	{
		maxrevenue=0;
		for(j=0;j<size;j++)
		{
			if(revenue[j]>maxrevenue )
			{
				k=j;
				maxrevenue=revenue[j];
			}
		}
		topx.push_back(k);
		revenue[k]=0;
	}
	return true;
}

string Statistics::BestSaleProdByCat (Database &Data, string cat)
{
	ostringstream os;
	Product *prod = NULL, *best = NULL;
	int j = 0;
	double bestSale = 0, revenueCheck = 0;;
	vector<double> grossRev;
	
	for(int i = 0; i < Data.getinven()->getLength(); i++)
	{
		Data.getinven()->retrieve(i,prod);
		if (prod->getcat() == cat)
		{
			// Use a vector to store the gross revenue of a product (double data type)
			grossRev.push_back( (prod->getprice()) * (prod->getnumsoldpermth()) );
			
			// Compare the gross revenue for each product in a given cat
			if (grossRev[j] > bestSale)	// what if equal? is it possible?
			{
				bestSale = grossRev[j];
				best = prod;
			}
			j++;		
		}
	}
	
	for(int k = 0; k < grossRev.size(); k++) // check if no prod sold => no gross rev => cout no sold!
	{
		 revenueCheck += grossRev[k];
	}
	if(revenueCheck == 0)
	{
		os << endl << "No product had been sold yet!";
		return os.str();
	}
	else
	{
		os << endl << "The top selling product in the " << cat << " category is " << best->getname() << ".";
		return os.str();
	}
}
	
string Statistics::BestSaleManu (Database &Data)	// To be done: Provide a check for CAPS difference in manufacturer's name
{
	ostringstream os;
	bool newManuCheck;
	int bestManu = 0;
	double grossRev = 0, maxRev = 0;
	vector< vector<Product*> > manuList;	// 2D vector to store the products into vectors of different manufacturers
	Product* item = NULL;

	for(int i = 0; i < Data.getindex(); i++)	// to loop through all products in the list
	{
		Data.getinven()->retrieve(i,item);
		newManuCheck = true;

		// Search through all the products for all the manu's names -> store in vector
		for(int j = 0; j < manuList.size(); j++)
		{
			if( manuList[j][0]->getmanu() == item->getmanu() ) // Check if item pointing to a product with same manufacturer in the vector
			{
				manuList[j].push_back(item);
				newManuCheck = false;
				break; // forced to exit the loop
			}
		}

		// new manufacturer
		if (newManuCheck == true)	// item is pointing to a product with a new manufacturer
		{
			manuList.push_back( vector<Product*>() );	// create a new row
			manuList[manuList.size()-1].push_back(item);	// assign to 1st column of new row
		}

	}
	
	// Use a loop to generate gross revenue by each manufacturer
	for(int row = 0; row < manuList.size(); row++)
	{
		for(int column = 0; column < manuList[row].size(); column++)
			grossRev += ( manuList[row][column]->getprice() * manuList[row][column]->getnumsoldpermth() );
		if(grossRev > maxRev)
		{
			maxRev = grossRev;
			bestManu = row;
		}
	}

	if(manuList.empty())
	{
		os << endl << "No product had been sold yet!";
		return os.str();
	}
	else
	{
		os << endl << "The top selling manufacturer is " << manuList[bestManu][0]->getmanu() << ".";
		return os.str();
	}
}