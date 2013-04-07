#ifndef VECTORLIST_H
#define VECTORLIST_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "ListBase.h"

using namespace std;

template <typename V>
class VectorList :public ListBase<V>
{
private:
	vector<V*> Vlist;
	V* tempitem;
public:

	VectorList()
	{
		Vlist;
	}

	~VectorList(){}

	bool AddItem(int index, V* item)
	{
		/*adding item to index pos*/

		int size= Vlist.size();
		if(index<0)
			return false;
		else if(index==size||index>size)
		{
			Vlist.push_back(item);
			_size=Vlist.size();
			return true;
		}
		else
		{
			vector<V*> templist;
			for(int i=index;i<size;i++)
			{
				tempitem=Vlist.at(i);
				Vlist.pop_back();
				templist.push_back(tempitem);
			}
			Vlist.push_back(item);
			for(int i=templist.size();i>0;i--)
			{
				Vlist.push_back(templist.at(i));
			}
			_size=Vlist.size();
			return true;
		}
	}

	bool DeleteItem(int index)
	{
		/*deleting item to index pos*/
		if (index < 0)
			return false;
		else
		{
			Vlist.erase(Vlist.begin()+index);
			_size=Vlist.size();
			return true;
		}
	}
	bool retrieve(int index, V *&item)
	{
		if (index < 0)
			return false;
		else
		{
			item = Vlist.at(index);
			_size=Vlist.size();
			return true;
		}
	}
};

#endif