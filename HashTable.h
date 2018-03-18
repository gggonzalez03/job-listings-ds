// HashTable Class
#ifndef HASH_TABLE
#define HASH_TABLE

#include "HashEntry.h"

const int TABLE_SIZE = 150;

template<typename K, typename V>
class HashTable {
private:
    // HashEntry array
    HashEntry<K,V> *arr;
    double loadFactor;
    int collisionCount;
    int numOfElements;
public:
    // Constructor
    HashTable();
    // Destructor
    ~HashTable();
    // HashTable operations
    int goodHash(K);
    int badHash(K);
    V searchTable(K);
    void insertGoodHash(K,V);
    void insertBadHash(K,V);
    V remove(K);
};

template<typename K, typename V>
HashTable<K,V>::HashTable() {
    arr = new HashEntry<K,V>[TABLE_SIZE];
    loadFactor = 0.0;
    collisionCount = 0;
    numOfElements = 0;
}

template<typename K, typename V>
HashTable<K,V>::~HashTable() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        if(arr[i] != NULL) {
            delete arr[i];
        }
    }
    delete[] arr;
}

// Hash function that has minimum collisions
template<typename K, typename V>
int HashTable<K,V>::goodHash(K key) {
    
}

// Basic Hash function that may have many collisions
template<typename K, typename V>
int HashTable<K,V>::badHash(K key) {
    
}

// Searches HashTable based on the key, hashes key value to get the index
template<typename K,typename V>
V HashTable<K,V>::searchTable(K key) {
    int hashedIndex = goodHash(key);
    // if hashedIndex contains the search key
    if(arr[hashedIndex]->getKey() == key) {
        return arr[hashedIndex]->getValue();
    } else {
        // searches the bucketArray for the search key
        arr[hashedIndex]->getBucketArr()->searchBucketArray(key);
    }
    return NULL;
}

// Inserts into HashTable using goodHash()
template<typename K, typename V>
void insertGoodHash(K key, V value) {
//    HashEntry<K,V> *item = new HashEntry<K,V>(key, value);
//    int hashedIndex = goodHash(key);
//    // if hashedIndex is empty
//    if(arr[hashedIndex] == NULL)
//    {
//        arr[hashedIndex] = item;
//        // increment number of elements
//        numOfElements++;
//        // calculate load factor each time you insert
//        loadFactor = numOfElements % TABLE_SIZE;
//    } else {
//        // checks if the HashEntry items bucket array is full
//        if(item->getBucketArr()->getCount() != 3) {
//            // inserts item into bucket array, starting at index[0]
//            item->getBucketArr()->insertBucketArray(hashedIndex, value);
//            // update number of collisions
//            collisionCount++;
//        }
//        // insert into overflow linked list
//        //collisionCount++;
//    }
}


// Inserts into HashTable using badHash()
template<typename K, typename V>
void insertBadHash(K key, V value) {
//    HashEntry<K,V> *item = new HashEntry<K,V>(key, value);
//    int hashedIndex = badHash(key);
//    // if hashedIndex is empty
//    if(arr[hashedIndex] == NULL) {
//        arr[hashedIndex] = item;
//        // increment number of elements
//        numOfElements++;
//        // calculate load factor each time you insert
//        loadFactor = numOfElements % TABLE_SIZE;
//    } else {
//        // checks if the HashEntry items bucket array is full
//        if(item->getBucketArr()->getCount() != 3) {
//            // inserts item into bucket array, starting at index[0]
//            item->getBucketArr()->insertBucketArray(key, value);
//            // update number of collisions
//            collisionCount++;
//        }
//        // insert into overflow linked list
//        //collisionCount++;
//    }
}

// Removes the key-value pair at the hashed index
template<typename K, typename V>
V HashTable<K,V>::remove(K key) {
//    int hashedIndex = goodHash(key);
//    // check HashTable array
//    if(arr[hashedIndex]->getKey() == key) {
//        HashEntry<K,V> *temp = arr[hashedIndex];
//        //arr[hashedIndex] = NULL;
//        numOfElements--;
//        return temp->getValue();
//        // update load factor
//        loadFactor = numOfElements % TABLE_SIZE;
//    } else if(arr[hashedIndex]->getBucketArr()->getCount() != 0) { // if the item is in the bucketArray
//        arr[hashedIndex]->getBucketArr()->removeBucketArray(key);
//    } else {
//        // check overflow link list and remove item
//    }
    return NULL;
}

#endif
