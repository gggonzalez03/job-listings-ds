#ifndef LINKLIST_H
#define LINKLIST_H

#include "Node.h"
using std::cout;

template<typename K, typename V>
class LinkList {
private:
    Node<K,V>* top;
    int count;
public:
    LinkList();
    ~LinkList();
    Node<K,V>* find(K);
    void add(K,V);
    bool remove(K);
    Node<K,V>* getTop();
    void print();
};

template<typename K, typename V>
LinkList<K,V>::LinkList() {
    top = NULL;
    count = 0;
}

template<typename K, typename V>
LinkList<K,V>::~LinkList() {
    Node<K,V>* temp = top;
    while (temp != nullptr)
    {
        top = top -> get_next();
        delete temp;
        temp = top;
    }
}

template<typename K, typename V>
Node<K,V>* LinkList<K,V>::find(K key) {
    Node<K,V>* temp = top;
    while (temp != 0)
    {
        if (temp->getK() == key) return temp;
        temp = temp -> getNext();
    }
    return 0;
}

template<typename K, typename V>
void LinkList<K,V>::add(K key, V value) {
    Node<K,V>* newNode = new Node<K,V>(key, value);
    if(count == 0) {
        top = newNode;
        count++;
    } else {
        Node<K,V>* currNode = top;
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
    Node<K,V>* temp = top;
    Node<K,V>* temp2 = NULL;
    Node<K,V>* temp3 = NULL;

    while(temp->getK() != key) {
        temp2 = temp;
        temp = temp->getNext();
    }
    if(temp == top) {
        temp3 = temp;
        temp = temp->getNext();
        delete temp3;
        return true;
    } else if(temp->getNext() == NULL) {
        temp2->setNext(NULL);
        delete temp;
        return true;
    } else {
        Node<K,V>* temp4 = temp;
        temp = temp->getNext();
        temp2->setNext(temp);
        delete temp4;
        return true;
    }
    return false;
}

template<typename K, typename V>
Node<K,V>* LinkList<K,V>::getTop() {
    return top;
}

template<typename K, typename V>
void LinkList<K,V>::print() {
    Node<K,V>* temp = getTop();
    while(temp != NULL) {
        cout << temp->getV();
        temp = temp->getNext();
    }
}

#endif
