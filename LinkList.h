#ifndef LINKLIST_H
#define LINKLIST_H

#include "Node.h"

template<typename K, typename V>
class LinkList {
private:
  Node* top;
  int count;
public:
  LinkList();
  ~LinkList();
  Node* find(K);
  void add(K,V);
  bool remove(K);
  Node* getTop();
};

template<typename K, typename V>
LinkList<K,V>::LinkList() {
  top(NULL,NULL);
  count = 0;
}

template<typename K, typename V>
LinkList<K,V>::~LinkList() {
  Node* temp = top;
  while (temp != nullptr)
  {
    top = top -> get_next();
    delete temp;
    temp = top;
  }
}

template<typename K, typename V>
Node* LinkList<K,V>::find(K key) {
  Node* temp = top;
  while (temp != 0)
  {
    if (temp->getK() == key) return temp;
    temp = temp -> get_next();
  }
  return 0;
}

template<typename K, typename V>
void LinkList<K,V>::add(K key, V value) {
  Node* newNode = new Node(key, value);
  if(count == 0) {
    top = newNode;
    count++;
  } else {
    Node* currNode = top;
    while(currNode->getNext() != NULL) {
      currNode = currNode->getNext();
    }
    currNode->setNext(newNode);
    count++;
  }
}

template<typename K, typename V>
bool LinkList<K,V>::remove(K key) {
  if(!find(key)) {
    return false;
  }
  Node* temp = top;
  Node* temp2 = NULL;
  Node* temp3 = NULL;
  while(temp->getK() != key) {
    temp2 = temp;
    temp = temp->get_next();
  }
  if(temp == top) {
    temp3 = temp;
    temp = temp->get_next();
    delete temp2;
    return true;
  } else if(temp->get_next() == NULL) {
    temp2->set_next(NULL);
    delete temp;
    return true;
  } else {
    Node* temp4 = temp;
    temp = temp->get_next();
    temp2->set_next(temp);
    delete temp4;
    return true;
  }
}

template<typename K, typename V>
Node* LinkList<K,V>::getTop() {
  return top;
}

#endif
