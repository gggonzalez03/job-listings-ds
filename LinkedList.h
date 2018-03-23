//
//  LinkedList.h
//  JobListingsTeamProject
//
//  Created by Ging Gonzalez on 3/21/18.
//  Copyright © 2018 Ging Gonzalez. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>

using std::string;

template <class ItemType>
class LinkedList
{
private:
    struct ListNode
    {
        ItemType data;
        ListNode *next;
    };
    
    ListNode *head;
    int count;
    
public:
    // Constructor
    LinkedList();
    
    // Destructor
    ~LinkedList();
    
    // Linked list operations
    int getCount() const { return count; };
    bool insertFront(ItemType &);
    bool deleteNode(ItemType &);
    bool searchList(ItemType &) const;
    void printList(void callback(ItemType &)) const;
    void traverseList(void callback(ofstream &, ItemType &), ofstream & ofs);
    bool saveList();
};

template<class ItemType>
LinkedList<ItemType>::LinkedList()
{
    head = new ListNode;
    head->next = NULL;
    head->data = *new ItemType();
    count = 0;
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    
}

template<class ItemType>
bool LinkedList<ItemType>::insertFront(ItemType &item)
{
    // Create the node
    ListNode *newNode = new ListNode;
    
    if (count == 0)
    {
        head->data = item;
        count++;
        return true;
    }
    
    newNode->data = item;
    newNode->next = head;

    head = newNode;
    
    count++;
    
    return true;
}

template<class ItemType>
bool LinkedList<ItemType>::deleteNode(ItemType &item)
{
    ListNode *nodePtr = head;
    ListNode *prevNode = head;
    
    while (nodePtr)
    {
        if (nodePtr->data == item)
        {
            item = nodePtr->data;
            
            // If the head is the only item in the list
            if (count == 1)
            {
                nodePtr->data = *new ItemType();
                return true;
            }
            
            prevNode->next = nodePtr->next;
            
            delete nodePtr;
            count--;
            
            return true;
        }
        
        prevNode = nodePtr;
        nodePtr = nodePtr->next;
    }
    
    return false;
}

template<class ItemType>
void LinkedList<ItemType>::printList(void callback(ItemType &)) const
{
    ListNode *nodePtr = head;
    while (nodePtr && count > 0)
    {
        callback(nodePtr->data);
        nodePtr = nodePtr->next;
    }
}

template<class ItemType>
void LinkedList<ItemType>::traverseList(void callback(ofstream &, ItemType &), ofstream & ofs)
{
    ListNode *nodePtr = head;
    while (nodePtr && count > 0)
    {
        callback(ofs, nodePtr->data);
        nodePtr = nodePtr->next;
    }
}

#endif /* LinkedList_h */
