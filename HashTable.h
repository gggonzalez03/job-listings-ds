// HashTable Class
#ifndef HASH_TABLE
#define HASH_TABLE

#include "Bucket.h"
#include "LinkedList.h"

using std::string;

template<typename K, class Itemtype>
class HashTable {
private:
    Bucket<Itemtype> *buckets;
    LinkedList<Itemtype> *overflow;
    double loadFactor;
    int collisionCount;
    int numOfItems;
    int tableSize;
    int bucketSize;
public:
    HashTable();
    HashTable(int, int);
    ~HashTable();
    void setTableSize(int);
    void setBucketSize(int);
    int goodHash(K);
    int badHash(K);
    bool searchTable(K, Itemtype &);
    bool insertGoodHash(K, Itemtype &);
    bool insertBadHash(K, Itemtype &);
    bool remove(K,Itemtype &);
    void traverseTable(void callback(ofstream &, Itemtype &), ofstream &);
    void printTable(void callback(Itemtype &));
    double getLoadFactor() const;
    int getCollisionCount() const;
};


template<typename K, class Itemtype>
HashTable<K,Itemtype>::HashTable() {
    buckets = new Bucket<Itemtype>[0];
    overflow = new LinkedList<Itemtype>();
    loadFactor = 0.0;
    collisionCount = 0;
    numOfItems = 0;
    tableSize = 0;
    bucketSize = 0;
}

template<typename K, class Itemtype>
HashTable<K,Itemtype>::HashTable(int ts, int bs) {
    buckets = new Bucket<Itemtype>[ts];
    overflow = new LinkedList<Itemtype>();
    loadFactor = 0.0;
    collisionCount = 0;
    numOfItems = 0;
    tableSize = ts;
    bucketSize = bs;
    
    // Initialize the buckets in the array so that they can actually store data
    for (int i = 0; i < tableSize; i++)
    {
        buckets[i] = *new Bucket<Itemtype>(bs);
    }
}

template<typename K, class Itemtype>
HashTable<K,Itemtype>::~HashTable() {
    for(int i = 0; i < tableSize; i++) {
        if(buckets[i] != NULL) {
            delete buckets[i];
        }
    }
    delete[] buckets;
}

template<typename K, class Itemtype>
void HashTable<K,Itemtype>::setTableSize(int size) {
    tableSize = size;
}

template<typename K, class Itemtype>
void HashTable<K,Itemtype>::setBucketSize(int size) {
    bucketSize = size;
}

template<typename K, class Itemtype>
int HashTable<K,Itemtype>::goodHash(K key) {
    int index = stoi(key);
    int divisor = index % 10;
    
    if (!divisor)
        divisor += 1;
    
    index = (index * index * index);
    
    string temp = to_string(index);
    string middle = temp.substr(2,4);
    
    return (stoi(middle) / divisor) % tableSize;
}

template<typename K, class Itemtype>
int HashTable<K,Itemtype>::badHash(K key) {
    try
    {
        return stoi(key) % tableSize;
    }
    catch(invalid_argument &e)
    {
        return 0;
    }
}

template<typename K, class Itemtype>
bool HashTable<K,Itemtype>::searchTable(K key, Itemtype &item) {
    int hashedIndex = goodHash(key);
    Itemtype *found = buckets[hashedIndex].searchBucketArray(item);
    if(found)
    {
        item = *found;
        return true;
    }
    
    if (overflow->searchList(item))
        return true;
    
    return false;
}

template<typename K, class Itemtype>
bool HashTable<K,Itemtype>::insertGoodHash(K key, Itemtype &item) {
    
    int hashedIndex = goodHash(key);
    
    if (buckets == NULL)
        return false;
    
    if(buckets[hashedIndex].getCount() == 0) {
        numOfItems++;
        return buckets[hashedIndex].insertBucketArray(item);
    } else {
        if (!buckets[hashedIndex].insertBucketArray(item))
            overflow->insertFront(item);
        collisionCount++;
        return true;
    }
    return false;
}

template<typename K, class Itemtype>
bool HashTable<K,Itemtype>::insertBadHash(K key, Itemtype &item) {
    int hashedIndex = badHash(key);

    if (buckets == NULL)
        return false;

    if(buckets[hashedIndex].getCount() == 0) {
        numOfItems++;
        return buckets[hashedIndex].insertBucketArray(item);
    } else {
        if (!buckets[hashedIndex].insertBucketArray(item))
            overflow->insertFront(item);
        collisionCount++;
        return true;
    }
    
    return false;
}

template<typename K, class Itemtype>
bool HashTable<K,Itemtype>::remove(K key, Itemtype &item) {
    int hashedIndex = goodHash(key);
    if(buckets[hashedIndex].removeBucketArray(item)) {
        if(buckets[hashedIndex].getCount() > 0) {
            collisionCount--;
            return true;
        }
        numOfItems--;
        return true;
    }
    else {
        bool deleted = false;
        
        if (overflow->deleteNode(item))
        {
            collisionCount--;
            deleted = true;
        }
        
        return deleted;
    }
    return false;
}

template<typename K, class Itemtype>
void HashTable<K,Itemtype>::traverseTable(void callback(ofstream &, Itemtype &), ofstream & ofs)
{
    for (int i = 0; i < tableSize; i++)
    {
        if (buckets[i].getCount())
            buckets[i].traverseBucket(callback, ofs);
    }
    
    overflow->traverseList(callback, ofs);
}

template<typename K, class Itemtype>
void HashTable<K,Itemtype>::printTable(void callback(Itemtype &))
{
    for (int i = 0; i < tableSize; i++)
    {
        if (buckets[i].getCount())
            buckets[i].printBucket(callback);
    }
    
    overflow->printList(callback);
}

template<typename K, class Itemtype>
double HashTable<K,Itemtype>::getLoadFactor() const
{
    return (double)numOfItems / (double)tableSize;
}

template<typename K, class Itemtype>
int HashTable<K,Itemtype>::getCollisionCount() const
{
    return collisionCount;
}

#endif
/*
 #include "HashEntry.h"

 const int TABLE_SIZE = 150;

 template<typename K, typename V>
 class HashTable {
 private:
 // HashEntry array
 Bucket<Itemtype> *bucket;
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
 bucket = new Bucket<Itemtype>[TABLE_SIZE];
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
 return 0;
 }

 // Basic Hash function that may have many collisions
 template<typename K, typename V>
 int HashTable<K,V>::badHash(K key) {
 return 0;
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
 void HashTable<K,V>::insertGoodHash(K key, V value) {
 HashEntry<K,V> *item = new HashEntry<K,V>(key, value);
 int hashedIndex = goodHash(key);
 // if hashedIndex is empty
 if(arr[hashedIndex] == NULL)
 {
 arr[hashedIndex] = item;
 // increment number of elements
 numOfElements++;
 // calculate load factor each time you insert
 loadFactor = numOfElements % TABLE_SIZE;
 } else {
 // checks if the HashEntry items bucket array is full
 if(item->getBucketArr()->getCount() != 3) {
 // inserts item into bucket array, starting at index[0]
 item->getBucketArr()->insertBucketArray(hashedIndex, value);
 // update number of collisions
 collisionCount++;
 }
 // insert into overflow linked list
 //collisionCount++;
 }
 }


 // Inserts into HashTable using badHash()
 template<typename K, typename V>
 void HashTable<K,V>::insertBadHash(K key, V value) {
 HashEntry<K,V> *item = new HashEntry<K,V>(key, value);
 int hashedIndex = badHash(key);
 // if hashedIndex is empty
 if(arr[hashedIndex] == NULL) {
 arr[hashedIndex] = item;
 // increment number of elements
 numOfElements++;
 // calculate load factor each time you insert
 loadFactor = numOfElements % TABLE_SIZE;
 } else {
 // checks if the HashEntry items bucket array is full
 if(item->getBucketArr()->getCount() != 3) {
 // inserts item into bucket array, starting at index[0]
 item->getBucketArr()->insertBucketArray(key, value);
 // update number of collisions
 collisionCount++;
 }
 // insert into overflow linked list
 //collisionCount++;
 }
 }

 // Removes the key-value pair at the hashed index
 template<typename K, typename V>
 V HashTable<K,V>::remove(K key) {
 int hashedIndex = goodHash(key);
 // check HashTable array
 if(arr[hashedIndex]->getKey() == key) {
 HashEntry<K,V> *temp = arr[hashedIndex];
 //arr[hashedIndex] = NULL;
 numOfElements--;
 return temp->getValue();
 // update load factor
 loadFactor = numOfElements % TABLE_SIZE;
 } else if(arr[hashedIndex]->getBucketArr()->getCount() != 0) { // if the item is in the bucketArray
 arr[hashedIndex]->getBucketArr()->removeBucketArray(key);
 } else {
 // check overflow link list and remove item
 }
 return NULL;
 }

 #endif
 */
