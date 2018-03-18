// HashEntry Class
#ifndef HASH_ENTRY
#define HASH_ENTRY

template<typename K, typename V>
class HashEntry {
private:
  K key;
  V value;
public:
  // Constructor
  HashEntry(K, V);
  // Getters
  K getKey();
  V getValue();
};

template<typename K, typename V>
HashEntry<K,V>::HashEntry(K key, V value) {
  this->key = key;
  this->value = value;
}

template<typename K, typename V>
K HashEntry<K, V>::getKey() {
  return key;
}

template<typename K, typename V>
V HashEntry<K, V>::getValue() {
  return value;
}

#endif
