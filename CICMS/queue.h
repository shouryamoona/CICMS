#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <vector>

using namespace std;


template<typename T>
class queue
{
private:
	vector<T*> q;

public:
	queue()
	{
		q;
	}

	~queue(){}

	bool push_back(T* item)
	{
		if(item!=NULL)
		{
			q.push_back(item);
			return true;
		}
		else 
			return false;
	}

	bool pop()
	{
		q.erase(q.begin());
		return true;
	}

	bool retrieve(T* &item)
	{
		item=q.at(0);
		return true;
	}

	bool empty()
	{
		if(q.size()==0)
			return true;
		else 
			return false;
	}

	int size()
	{
		return q.size();
	}

};


#endif