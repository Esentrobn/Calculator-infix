//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT stack: Link-based implementation.
    Listing 7-x.  
    @file LinkedStack.h */

#ifndef _LINKED_STACK
#define _LINKED_STACK

#include "StackInterface.h"
#include "Node.cpp"
#include "PrecondViolatedExcep.cpp"

/** ADT stack - Linked implementation. */

template<class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
	
private:
	Node<ItemType>* topPtr; // Pointer to first node in the chain;
                           // this node contains the stack's top

public:
// Constructors and destructor:
	LinkedStack();                                     // Default constructor
	LinkedStack(const LinkedStack<ItemType>& aStack);  // Copy constructor
	virtual ~LinkedStack();                            // Destructor
	
// Stack operations:
	bool isEmpty() const;
	bool push(const ItemType& newItem);
	bool pop();
	bool search(const ItemType& Item);

   /** @throw PrecondViolatedExcep if the stack is empty */
	ItemType peek() const throw(PrecondViolatedExcep);
}; // end LinkedStack



#endif
