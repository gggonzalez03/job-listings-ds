// HashTable Class
// Created by Ging Gonzalez and Fawzan Khan
// HashTable class saves an array of buckets that contain the main data
// and as well as the colliions. Overflows are saved in a different data
// structure, LinkedList.

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
    // Constructors
    HashTable();
    HashTable(int, int);
    // Destructor
    ~HashTable();
    // Sets the size of the hash table
    void setTableSize(int);
    // Sets the size of each bucket in the hash table
    void setBucketSize(int);
    // Returns a hashed index using a good hash algorithm
    int goodHash(K);
    // Returns a hashed index using a bad hash algorithm
    int badHash(K);
    // Searches the table by a certain key, and saves the result in the object passed in
    // returns boolean
    bool searchTable(K, Itemtype &);
    // Insert using the good hash algorithm
    // returns boolean
    bool insertGoodHash(K, Itemtype &);
    // Insert using the bad hash algorithm
    // returns boolean
    bool insertBadHash(K, Itemtype &);
    // Removes an item from the table, and saves the removed item into the object passed in
    bool remove(K,Itemtype &);
    // Traverse the table with a file stream callback
    void traverseTable(void callback(ofstream &, Itemtype &), ofstream &);
    // Traverse the table with a callback that accepts an item object
    void printTable(void callback(Itemtype &));
    // Returns the load factor in decimal form
    double getLoadFactor() const;
    // Returns the accumulated collision count
    int getCollisionCount() const;
};

// Constructors
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

// Desctructor
template<typename K, class Itemtype>
HashTable<K,Itemtype>::~HashTable() {
    for(int i = 0; i < tableSize; i++) {
        if(buckets[i] != NULL) {
            delete buckets[i];
        }
    }
    delete[] buckets;
}

// Setters
template<typename K, class Itemtype>
void HashTable<K,Itemtype>::setTableSize(int size) {
    tableSize = size;
}

template<typename K, class Itemtype>
void HashTable<K,Itemtype>::setBucketSize(int size) {
    bucketSize = size;
}

// Hashes
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

// Hash table operations
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

// Traversal methods
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
