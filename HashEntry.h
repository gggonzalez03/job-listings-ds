// HashEntry Class
#ifndef HASH_ENTRY
#define HASH_ENTRY

#include "Bucket.h"

template<typename K, typename V>
class HashEntry {
private:
  K key;
  V value;
  Bucket<K,V> *bucketArr;
public:
  // Constructor
    HashEntry();
  HashEntry(K,V);
  // Getters
  K getKey();
  V getValue();
  Bucket<K,V> getBucketArr();
};

template<typename K, typename V>
HashEntry<K,V>::HashEntry() {
    
}

template<typename K, typename V>
HashEntry<K,V>::HashEntry(K key, V value) {
  this->key = key;
  this->value = value;
  bucketArr = new Bucket<K,V>*();
}

template<typename K, typename V>
K HashEntry<K, V>::getKey() {
  return key;
}

template<typename K, typename V>
V HashEntry<K, V>::getValue() {
  return value;
}

template<typename K, typename V>
Bucket<K,V> HashEntry<K,V>::getBucketArr() {
  return bucketArr;
}
#endif
