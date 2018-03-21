// HashTable Class
#ifndef HASH_TABLE
#define HASH_TABLE

#include "Bucket.h"

using std::string;

template<typename K, class Itemtype>
class HashTable {
private:
    Bucket<Itemtype> *buckets;
    double loadFactor;
    int collisionCount;
    int numOfItems;
    int tableSize;
    int bucketSize;
public:
    HashTable(int, int);
    ~HashTable();
    void setTableSize(int);
    int goodHash(K);
    int badHash(K);
    Itemtype * searchTable(K, Itemtype &);
    bool insertGoodHash(K, Itemtype &);
    bool insertBadHash(K, Itemtype &);
    bool remove(K,Itemtype &);
};

template<typename K, class Itemtype>
HashTable<K,Itemtype>::HashTable(int ts, int bs) {
    buckets = new Bucket<Itemtype>[ts];
    loadFactor = 0.0;
    collisionCount = 0;
    numOfItems = 0;
    tableSize = ts;
    bucketSize = bs + 1;
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
int HashTable<K,Itemtype>::goodHash(K key) {
  int length = 0;
  int index = 0;
  char ch[length];

  strcpy(ch, key.c_str());
  length = key.length();
  for(int i = 0; i < length; i++) {
    index += ch[i];
  }
  index = (index * index * index) % 53;
  return index;
}

template<typename K, class Itemtype>
int HashTable<K,Itemtype>::badHash(K key) {
    return key % tableSize;
}

template<typename K, class Itemtype>
Itemtype * HashTable<K,Itemtype>::searchTable(K key, Itemtype &item) {
    int hashedIndex = goodHash(key);
    Itemtype *temp = buckets[hashedIndex].searchBucketArray(item);
    if(temp) {
        return temp;
    }
    // search overflow
    return NULL;
}

template<typename K, class Itemtype>
bool HashTable<K,Itemtype>::insertGoodHash(K key, Itemtype &item) {
    int hashedIndex = goodHash(key);
    if(buckets[hashedIndex].getCount() == 0) {
        buckets[hashedIndex].setSize(bucketSize);
        buckets[hashedIndex].insertBucketArray(item);
        numOfItems++;
        return true;
    } else if(buckets[hashedIndex].getCount() > 0) {
        buckets[hashedIndex].insertBucketArray(item);
        collisionCount++;
        return true;
    } else {
        // insert into overflow structure
    }
    return false;
}

template<typename K, class Itemtype>
bool HashTable<K,Itemtype>::insertBadHash(K key, Itemtype &item) {
    int hashedIndex = badHash(key);
    if(buckets[hashedIndex].getCount() == 0) {
        buckets[hashedIndex].insertBucketArray(item);
        numOfItems++;
        return true;
    } else if(buckets[hashedIndex].getCount() > 0) {
        buckets[hashedIndex].insertBucketArray(item);
        collisionCount++;
        return true;
    } else {
        // insert into overflow structure
    }
    return false;
}

template<typename K, class Itemtype>
bool HashTable<K,Itemtype>::remove(K key, Itemtype &item) {
    int hashedIndex = goodHash(key);
    if(buckets[hashedIndex].searchBucketArray(item) != NULL) {
        if(buckets[hashedIndex].getCount() > 0) {
            buckets[hashedIndex].removeBucketArray(item);
            collisionCount--;
            return true;
        }
        buckets[hashedIndex].removeBucketArray(item);
        numOfItems--;
    } else {
        // insert into overflow structure
    }
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
