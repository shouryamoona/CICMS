#ifndef LISTBASE_H
#define LISTBASE_H

#include <iostream>
#include <string>
#include "Product.h"

using namespace std;

// LIST BASE CLASS
template <typename B>				
class ListBase					
{
protected:
	int _size;

public:
	ListBase(){
		_size = 0;
	}

	virtual ~ListBase() {};

	bool isEmpty(){
		return (_size==0);
	}

	int getLength(){
		return _size;
	}

	virtual bool AddItem(int index, B* item) =0;
	virtual bool DeleteItem(int index) =0;
	virtual bool retrieve(int index, B *&item) = 0;
	//virtual string toString() = 0;  
};

#endif