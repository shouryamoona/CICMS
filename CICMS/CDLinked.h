#ifndef CDLINKED_H
#define CDLINKED_H

#include <iostream>
#include <string>
#include <sstream>
#include "ListBase.h"

using namespace std;


// DOUBLY CIRCULAR LINKED LIST IMPLEMENTATION
template <typename D>			
class CDLinked : public ListBase<D>
{
	struct ListNode
	{
		D *item;
		ListNode *next;
		ListNode *prev;
	};
	ListNode *tail;
	ListNode* traverseTo(int index)
	{
		if ( (index < 0) || (index >= getLength()) )
			return NULL;
		else
		{  
			ListNode *cur = tail->next;
			for ( int skip = 0; skip < index; skip++ )
				cur = cur->next;

			return cur;
		}
	}

public:

	CDLinked()
	{
		tail = NULL;
	}

	bool AddItem(int index, D *item)
	{
		int newLength = getLength() + 1;

		if ( (index < 0) || (index >= newLength) )
		{
			return false;
		}

		else 
		{  
			ListNode *newPtr = new ListNode;
			newPtr->item = item;
			newPtr->next = NULL;
			newPtr->prev = NULL;
			_size = newLength;

			if (index==0)
			{
				if(tail==NULL)
				{
					tail=newPtr;
					newPtr->prev=tail;
					newPtr->next=tail;
				}
				else
				{
					newPtr->prev=tail;
					newPtr->next=tail->next;
					tail->next->prev=newPtr;
					tail->next=newPtr;
					tail=newPtr;
				}
			}

			else if (index==getLength()-1)
			{
				newPtr->prev=tail;
				newPtr->next=tail->next;
				tail->next->prev=newPtr;
				tail->next=newPtr;
				tail=newPtr;
			}

			else
			{
				ListNode *cur = traverseTo(index);
				newPtr->next = cur;
				newPtr->prev = cur->prev;

				cur->prev = newPtr;
				cur->prev->next=newPtr;
			}
			
		}

		return true;
	}

	bool DeleteItem(int index)
	{
		ListNode *cur = new ListNode;
		if ( (index < 0) || (index >= getLength()) )
		{
			return false;
		}

		else 
		{  
			if ( getLength() == 1)
			{
				cur = tail;
				tail = NULL;
			} 
			else if ( index == 0 ) 
			{  
				cur = tail->next;  
				tail->next = cur->next;
				cur->next->prev=tail;
			} 
			else 
			{
				ListNode *cur = traverseTo(index);
				cur->prev->next=cur->next;
				cur->next->prev = cur->prev;
			}
			delete cur;
			cur = NULL;
			_size--;
			
		}
		return true;
		
	}

	bool retrieve(int index, D *&item)
	{
		if ( (index < 0) || (index >= getLength()) )
			return false;
		else
		{  
			ListNode *cur = traverseTo( index );
			item = cur->item;
		}
		return true;
	}

	~CDLinked()
	{
		while (!isEmpty())
			DeleteItem(0);
	}
};

#endif
