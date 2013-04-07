#ifndef DYNAMICARR_H
#define DYNAMICARR_H
#include <iostream>
#include <sstream>
#include "ListBase.h"

using namespace std;

template <typename E>
class DynamicArr : public ListBase<E>
{

private:
	E* *arr;
	int capacity;

public:
	//Constructor
	DynamicArr()
	{
		capacity = 1000;
		arr = new E*[capacity];
		arr[0]=NULL;
	}

	//Destructor
	~DynamicArr()
	{
		delete [] arr; 
	}


	//Adds new item
	bool AddItem(int index, E* item)
	{
	
		if (index<0) //invalid index
			return false;
		else
		{
			//int newSize=_size+1; //increase newSize ???
			
			if (index>=capacity)
			{
				capacity=capacity*2;
				E* *temp= new E*[capacity]; //creates another array
				for (int i=0; i<_size; i++)
					temp[i]=arr[i];
				delete []arr;
				arr=temp;
				arr[index]=item;
				_size++;
				return true;
			}

			else
			{
				//cout << "size : " << _size << ", index : " << index << endl;
				for (int i=_size; i<index; i--)
				{
					arr[i+1]=arr[i]; //shift back from the end to the front 
				}

				arr[index]=item;

				_size++;

				return true;
			}
		}
	}


	bool DeleteItem(int index)
	{
		if (index>=_size) //index out of range
			return false;

		else
		{
			for (int i=index; i<_size; i++)
				arr[i]=arr[i+1];

			return true;
		}
	}

	bool retrieve(int index, E *&item)
	{
		for (int i=0; i<_size; i++)
		{
			if (arr[i]==arr[index]) //found
			{
				item=arr[i];
				return true; 
			}
		}

		return false; // cant find
	}

	/*string toString()
	{
	ostringstream str1;

	for (i=0; i<size; i++)
	str1<<arr[i];

	string output=str1.str();

	return output;

	}*/
};


#endif

