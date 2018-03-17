// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Ging Gonzalez
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree 
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
    
    // Find the smallest node item value
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* treePtr) const;
    
    // Find the largest node item value
    BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* treePtr) const;
   
public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    // Find the smallest node
    bool findSmallest(ItemType & returnedItem) const;
    // Find the largest node
    bool findLargest(ItemType & returnedItem) const;
 
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType> *nodePtr = findNode(this->rootPtr, anEntry);
    if (nodePtr != NULL)
    {
        // Only try to set returnedItem IF nodePtr is not NULL
        // Avoids bad access error
        returnedItem = nodePtr->getItem();
        return true;
    }
    return false;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(ItemType & returnedItem) const
{
    returnedItem = _findSmallest(this->rootPtr)->getItem();
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::findLargest(ItemType & returnedItem) const
{
    returnedItem = _findLargest(this->rootPtr)->getItem();
    return true;
}

//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr == NULL)
    {
        nodePtr = newNodePtr;
    }
    else
    {
        if (newNodePtr->getItem() < nodePtr->getItem())
        {
            nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
        }
        else
        {
            nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
        }
    }
    
    return nodePtr;
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)

{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const 
{
    if (nodePtr == NULL)
        return NULL;
    if (target < nodePtr->getItem())
        return findNode(nodePtr->getLeftPtr(), target);
    else
        if (target > nodePtr->getItem())
            return findNode(nodePtr->getRightPtr(), target);
        else
            return nodePtr;
}

// Find and return the smallest node (leftmost node)
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType> *treePtr) const
{
    if (treePtr != NULL && treePtr->getLeftPtr() != NULL)
        return _findSmallest(treePtr->getLeftPtr());
    return treePtr; // Tree pointer is the smallest one in this case since it's the only one in the tree
}

// Find and return the largest node (rightmost node)
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findLargest(BinaryNode<ItemType> *treePtr) const
{
    if (treePtr != NULL && treePtr->getRightPtr() != NULL)
        return _findLargest(treePtr->getRightPtr());
    return treePtr; // Tree pointer is the largest one in this case since it's the only one in the tree
}

#endif
