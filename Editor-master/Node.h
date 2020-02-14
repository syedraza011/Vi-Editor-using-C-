//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file Node.h 
    Listing 4-1 */
#ifndef NODE_   //prevent from declaring a variable twice 
#define NODE_

template<class ItemType>
class Node
{
public:
   Node();
   Node(const ItemType& anItem);
   Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
   void setItem(const ItemType& anItem);
   void setNext(Node<ItemType>* nextNodePtr);
   ItemType getItem() const ;
   Node<ItemType>* getNext() const ;

private:
	ItemType        item; // A data item
	Node<ItemType>* next; // Pointer to next node

}; // end Node

#include "Node.inl"
#endif