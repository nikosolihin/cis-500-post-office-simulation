#ifndef INTQUEUE_H
#define INTQUEUE_H

#include <iostream>
#include <string>
#include <sstream>

class IntQueue
{
	public:
		IntQueue ();
        bool isEmpty () const;
		bool isFull () const;
        bool dequeue (int& x);
        bool enqueue (const int& x);
        int length () const;
        std::string display (); 

	private:
        int size;
	    
		struct Node {
			int elem;
			Node * next;

			Node (const int& x) 
			{
				elem = x;
				next = NULL;
			}
		};

		Node * front, * back;
};

#endif