// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Ging Gonzalez
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
    void breadthFirstTraversal(void visit(ItemType &)) const{_breadthfirsttraversal(visit, rootPtr);}
    

    void printTree(void printIndentedItem(int, ItemType &), int indentCount) const {_printTree(printIndentedItem, rootPtr, indentCount);}

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _breadthfirsttraversal(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void printIndentedItem(int, ItemType &), BinaryNode<ItemType> *node, int indentCount) const;
   
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;
    
   
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->getRightPtr() != NULL)
    {
        destroyTree(nodePtr->getRightPtr());
        delete nodePtr->getRightPtr();
    }
    
    if (nodePtr->getLeftPtr() != NULL)
    {
        destroyTree(nodePtr->getLeftPtr());
        delete nodePtr->getLeftPtr();
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_breadthfirsttraversal(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    // Store BinaryNode addresses in the queue
    Queue<BinaryNode<ItemType>*> queue;
    if (nodePtr == NULL)
    {
        return;
    }
    
    queue.enqueue(nodePtr);
    while (!queue.isEmpty())
    {
        BinaryNode<ItemType> *curr;
        queue.dequeue(curr);
        
        ItemType item = curr->getItem();
        visit(item);
        
        if (curr->getLeftPtr() != NULL)
            queue.enqueue(curr->getLeftPtr());
        if (curr->getRightPtr() != NULL)
            queue.enqueue(curr->getRightPtr());
    }
    
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        ItemType item = nodePtr->getItem();
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        visit(item);
    }
}

// Prints the tree as an indented list
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void printIndentedItem(int, ItemType &), BinaryNode<ItemType> *node, int indentCount) const
{
    if (node == NULL)
        return;
    
    ItemType item = node->getItem();
    printIndentedItem(indentCount, item);
    
    if (node->getRightPtr() != NULL)
    {
        indentCount++;
        _printTree(printIndentedItem, node->getRightPtr(), indentCount);
    }
    if (node->getLeftPtr() != NULL)
    {
        if (node->getRightPtr() == NULL)
            indentCount++;
        _printTree(printIndentedItem, node->getLeftPtr(), indentCount);
    }
}



#endif

