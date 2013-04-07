#ifndef SORTEDLL_H
#define SORTEDLL_H

#include <iostream>
#include "ListBase.h"

using namespace std;

// SortedLL class: a modified version of Linked List
// Purpose: to add the items in sorted order (by category)
template <typename R>
class SortedLL : public ListBase<R>
{
private:
	struct ListNode		// Structure for each node
	{
		R *item;
		ListNode *next;
		ListNode *prev;
	};

	ListNode *head;
	ListNode *curr;

public:
	SortedLL()	// Constructor
	{
		head = NULL; 
		curr = NULL;
	}
	
	~SortedLL() // Destructor
	{
		while ( !isEmpty() )
			DeleteItem(0);
	}		

	bool AddItem(int index, R *item)	
	{
		_size = getLength() + 1;	// Update size

		if ( (index < 0) || (index >= _size) )
			return false;
		else
		{
			// For empty list case: Add new node to head of list
			if ( getLength() == 1 )		// ==1 because size is increased at the start
			{
				head = new ListNode;
				head->item = item;
				head->next = NULL;
				head->prev = NULL;
			}
			else
			{
				// If list is not empty, check for the category before adding
				// Find a node that has the same category as the new node; add to the first node (latest) in the particular category

				ListNode* newNode = new ListNode;
				newNode->item = item;
				curr = head;
				while(curr != NULL)
				{
					if ( (newNode->item)->getname() < (curr->item)->getname() )	// sort by name
					{
						newNode->next = curr;
						newNode->prev = curr->prev;
						if(curr == head)	// add to the head of list
						{
							head->prev = newNode;
							head = newNode;
						}
						else	// middle case
						{
							curr->prev->next = newNode;
							curr->prev = newNode;
						}
						break; // to exit the loop
					}
					else	// different category
					{
						if( getLength() == 2 )	// add to the head of list
						{				
							newNode->next = head->next;
							newNode->prev = head;
							head->next = newNode;
							curr = newNode;
							break;
						}
						else
						{
							curr = curr->next;				// keep traversing until the last position is reached
							if ( curr->next == NULL )		// curr is now at last item on the list
							{								// add to the back of the list since it is a new category
								curr->next = newNode;
								newNode->next = NULL;
								newNode->prev = curr;
								break;
							}
						}
					}
				}
			}
		}
		return true;
	}

	bool DeleteItem(int index)
	{
		ListNode* delNode = new ListNode;
		delNode = head;

		if ( (index < 0) || (index >= _size) )
			return false;
		else
		{
			if( getLength() == 1 )	// only 1 product (head)
			{
				delete delNode;
				delNode = NULL;	
				_size = 0;
			}
			else if ( index == 0 )	// removal of first item
			{   
				head = delNode->next;
				delNode->next->prev = NULL;
				delete delNode;
				delNode = NULL;
				_size = _size - 1;
			}
			else
			{		
				for(int i = 0; i < index; i++)	// for other cases - traverse
				{
					delNode = delNode->next;	// delNode at the right position now
				}

				if(delNode->next == NULL)	// Last item to be deleted
				{
					delNode->prev->next = NULL;
				}
				else	// Middle of list
				{
					delNode->prev->next = delNode->next;
					delNode->next->prev = delNode->prev;
				}
				delete delNode;
				delNode = NULL;
				_size = _size - 1;
			}
		}
		return true;
	}

	bool retrieve(int index, R *&item)	
	{
		ListNode* nodeOfInterest = new ListNode;
		nodeOfInterest = head;

		if ( (index < 0) || (index >= getLength()) )
			return false;

		for(int i = 0; i < index; i++)
		{
			nodeOfInterest = nodeOfInterest->next;	// nodeOfInterest is at the right position
		}
		item = nodeOfInterest->item;

		return true;
	}

};

#endif