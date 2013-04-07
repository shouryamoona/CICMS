#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

using namespace std;


template<typename T>
class stack
{
private:
	vector<T*> s;
	int index;

public:
	stack()
	{
		s;
		index=-1;
	}

	~stack(){}

	bool push_back(T* item)
	{
		if(item!=NULL)
		{
			index++;
			s.push_back(item);
			return true;
		}
		else 
			return false;
	}

	bool pop()
	{
		if ( s.empty() )
 			return false;
		else
		{
			s.erase(s.begin()+index);
			//s.pop_back();
			index--;
		}
		return true;
	}

	bool retrieve(T* &item)
	{
		if ( s.empty() )
 			return false;
		else
		{
			item=s.at(index);
			//item = s.back();
		}
		return true;
	}
	
	bool empty()
	{
		if(s.size()==0)
			return true;
		else 
			return false;
	}

	int size()
	{
		return s.size();
	}

};


#endif