// HashTable Class
#ifndef HASH_TABLE
#define HASH_TABLE

#include "HashEntry.h"

const int TABLE_SIZE = 150;
const int BUCKET_SIZE = 4;

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
    // TODO: This gives me error
  // arr = new HashEntry<K,V>[TABLE_SIZE];
  loadFactor = 0.0;
  collisionCount = 0;
  numOfElements = 0;
  /*for(int i = 0; i < TABLE_SIZE; i++) {
    for(int j = 0; j < BUCKET_SIZE; j++) {
      arr[i][j] = NULL;
    }
  }*/
}

template<typename K, typename V>
HashTable<K,V>::~HashTable() {
  for(int i = 0; i < TABLE_SIZE; i++) {
    for(int j = 0; j < BUCKET_SIZE; j++) {
      if(arr[i][j] != NULL) {
        delete arr[i][j];
      }
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

}

// Inserts into HashTable using goodHash()
template<typename K, typename V>
void insertGoodHash(K key, V value) {

}

// Inserts into HashTable using badHash()
template<typename K, typename V>
void insertBadHash(K key, V value) {

}

// Removes the key-value pair at the hashed index
template<typename K, typename V>
V HashTable<K,V>::remove(K key) {

}

#endif
