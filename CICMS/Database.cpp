#include "Database.h"
#include "Product.h"
#include "PerishableFood.h"
#include "Interface.h"
#include <string>
#include <fstream>
#include <cctype>

Database::Database()
{
	_index=0;
	inventory = new VectorList<Product>;
}

ListBase<Product>* Database::getinven()
{
	return inventory;
}

bool Database::addProd(char per, string name, string cat, int barnum, double price, string manu, int stock, int Numsoldpermth,int exp,double disc)
{
	vector<int> vect;
	if( SearchProdByBarNum(barnum, vect) )
		return false;

	if(per=='y'||per=='Y')
	{
		Product *item=new PerishableFood(per,name, cat,barnum,price, manu,stock,Numsoldpermth,exp,disc);
		if(inventory->AddItem(_index,item))
		{
			_index++;
			return true;
		}
		else 
			return false;
	}
	else if(per=='n'||per=='N')
	{
		Product *item=new Product(per,name,cat,barnum,price, manu,stock,Numsoldpermth);
		if(inventory->AddItem(_index,item))
		{
			_index++;
			return true;
		}
		else 
			return false;
	}
	else
		return false;
}

bool Database::delProd(int barnum)
{
	vector<int> vect;
	if( !SearchProdByBarNum(barnum, vect) )
		return false;

	for (int i=0;i<_index;i++)
	{
		Product *p;
		inventory->retrieve(i,p);

		if(barnum==p->getbarnum())
		{
			inventory->DeleteItem(i);
			_index--;
			return true;
		}
	}
	return false;
}

int Database::getindex()
{
	return _index;
}

bool Database::LoadFile()
{
	char per;
	string name,cat,manu;
	double price,disc;
	int barnum,stock,Numsoldpermth,expdate,n=0;

	ifstream f1;
	f1.open("batchdata.txt");	

	f1>>n;
	for (int i=0;i<n;i++)
	{
		f1>>per;
		f1.ignore(80,'\n');
		getline(f1,name);
		getline(f1,cat);
		f1>>barnum>>price;
		f1.ignore(80,'\n');
		getline(f1,manu);
		f1>>stock>>Numsoldpermth;
		if(per=='y'||per=='Y')
		{
			f1>>expdate>>disc;
		}
		else
		{
			expdate=NULL;
			disc=NULL;
		}
		addProd(per,name, cat,barnum,price, manu,stock,Numsoldpermth,expdate,disc);
	}
	f1.close();
	return true;
}

string Database::toString(int index)
{
	ostringstream os;

	Product *cur;
	inventory->retrieve(index,cur);

	os << cur->getname()<<" "<< cur->getcat() << " " << cur->getbarnum() << " " << cur->getprice()<< " "
		<<cur->getmanu() << " " << cur->getstock() << " " << cur->getnumsoldpermth() << " ";

	if ( cur->isPerishable()=='y'||cur->isPerishable()=='Y')
	{
		int i=cur->getexpirydate();
		int year = i%10000;
		i=i/10000;

		int month=i%100;
		int date=i/100;
		if(date<10 && month>=10)
			os <<0<<date<<"-"<<month<<"-"<<year<< " " << cur->getdiscount()<<"%";

		else if(date<10 && month<10)
			os <<0<<date<<"-"<<0<<month<<"-"<<year<< " " << cur->getdiscount()<<"%";
		else if(month<10 && date>=10)
			os <<date<<"-"<<0<<month<<"-"<<year<< " " << cur->getdiscount()<<"%";
		else
			os <<date<<"-"<<month<<"-"<<year<< " " << cur->getdiscount()<<"%";
	}
	os << endl;
	return os.str();
}

string Database::toStringPara(int index)
{
	ostringstream os;

	Product *p;
	inventory->retrieve(index,p);
	os << "Product Name: " << p->getname() << endl << "Barcode number: " << p->getbarnum() << endl
		<< "Category: " << p->getcat() << endl
		<< "Price: " << p->getprice() << endl
		<< "Manufacturer: " << p->getmanu() << endl
		<< "Stock: " << p->getstock() << endl
		<< "Number sold per month: " << p->getnumsoldpermth() << endl;
	if ( p->isPerishable()=='y'||p->isPerishable()=='Y')
	{
		int i=p->getexpirydate();
		int year = i%10000;
		i=i/10000;

		int month=i%100;
		int date=i/100;
		if(date<10 && month>=10)
		{
			os <<"Expiry Date: "<<0<<date<<"-"<<month<<"-"<<year<<endl;
		}
		else if(date<10 && month<10)
		{
			os <<"Expiry Date: "<<0<<date<<"-"<<0<<month<<"-"<<year<<endl;
		}
		else if(month<10 && date>=10)
		{
			os <<"Expiry Date: "<<date<<"-"<<0<<month<<"-"<<year<<endl;
		}
		else
		{
			os <<"Expiry Date: "<<date<<"-"<<month<<"-"<<year<<endl;
		}
		os<<"Discount: "<<p->getdiscount()<<"%"<<endl;
	}
	os << "Gross Revenue: " <<p->getnumsoldpermth()*p->getprice() << endl;
	os << endl;
	return os.str();
}

bool Database::SaveToFile()
{
	Product *p;

	ofstream f1;
	f1.open("batchdata.txt");	

	f1<<getindex()<<endl;
	for (int i=0;i<getindex();i++)
	{
		inventory->retrieve(i,p);
		f1<<p->isPerishable()<<endl<<p->getname()<<endl<<p->getcat()<<endl<<p->getbarnum()<<endl<<
			p->getprice()<<endl<<p->getmanu()<<endl<<p->getstock()<<endl<<p->getnumsoldpermth()<<endl;

		if ( p->isPerishable()=='y'||p->isPerishable()=='Y')
		{
			int i=p->getexpirydate();
			int year = i%10000;
			i=i/10000;

			int month=i%100;
			int date=i/100;
			if(date<10 && month>=10)
				f1 <<0<<date<<month<<year<<endl<<p->getdiscount()<<endl;

			else if(date<10 && month<10)
				f1 <<0<<date<<0<<month<<year<<endl<<  p->getdiscount()<<endl;
			else if(month<10 && date>=10)
				f1 <<date<<0<<month<<year<< endl<< p->getdiscount()<<endl;
			else
				f1 <<date<<month<<year<<endl<< p->getdiscount()<<endl;
		}
	}
	f1.close();

	return true;
}

bool Database:: SearchProdByName (string name, vector<int> &V)
{
	Product *p;int flag=0;
	string str;
	for (int i=0;i<getindex();i++)
	{
		inventory->retrieve(i,p);
		str=p->getname();
		if (str.size()==name.size())
		{
			for (int i=0;i<name.size();i++)
			{
				if(isupper(name[i]) || isupper(str[i]))
				{
					name[i]=tolower(name[i]);
					str[i]=tolower(str[i]);
				}
			}
			if(name==str)
			{
				flag++;
				V.push_back(i);
			}
		}
	}
	if(flag!=0)
		return true;
	else
		return false;
}

bool Database:: SearchProdByBarNum (int barnum, vector<int> &V)
{
	Product *p;
	int flag=0;
	int str;

	for (int i=0;i<getindex();i++)
	{
		inventory->retrieve(i,p);
		str=p->getbarnum();
		if(barnum==str)
		{
			flag++;
			V.push_back(i);
		}
	}

	if(flag!=0)
		return true;
	else
		return false;
}

bool Database:: SearchProdByCat (string cat, vector<int> &V)
{
	Product *p;
	int flag=0;
	string str;
	for (int i=0;i<getindex();i++)
	{
		inventory->retrieve(i,p);
		str=p->getcat();
		if (str.size()==cat.size()) //only check when size are the same (Increases effectiveness- decrease runtime)
		{
			for (int i=0;i<cat.size();i++)
			{
				if(isupper(cat[i]) || isupper(str[i]))
				{
					cat[i]=tolower(cat[i]);
					str[i]=tolower(str[i]);
				}
			}

			if(cat==str)
			{
				flag++;
				V.push_back(i);
			}
		}
	}
	if(flag!=0)
		return true;
	else
		return false;
}

bool Database:: SearchProdByManu (string manu, vector<int> &V)
{
	Product *p;
	int flag=0;

	string str;
	for (int i=0;i<getindex();i++)
	{
		inventory->retrieve(i,p);
		str=p->getmanu();
		if (str.size()==manu.size()) //only check when size are the same (Increases effectiveness- decrease runtime)
		{
			for (int i=0;i<manu.size();i++)
			{
				if(isupper(manu[i]) || isupper(str[i]))
				{
					manu[i]=tolower(manu[i]);
					str[i]=tolower(str[i]);
				}
			}

			if(manu==str)
			{
				flag++;
				V.push_back(i);
			}
		}
	}
	if(flag!=0)
		return true;
	else
		return false;
}