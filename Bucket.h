#ifndef BUCKET_H
#define BUCKET_H

const int SIZE = 4;

template<class Itemtype>
class Bucket {
private:
  Itemtype *items;
  int count;
public:
  Bucket();
  ~Bucket();
  int getCount();
  Itemtype * searchBucketArray(Itemtype &);
  bool insertBucketArray(Itemtype &);
  bool removeBucketArray(Itemtype &);
};

template<class Itemtype>
Bucket<Itemtype>::Bucket() {
    items = new Itemtype[SIZE];
    count = 0;
}

template<class Itemtype>
Bucket<Itemtype>::~Bucket() {
  delete[] items;
}

template<class Itemtype>
int Bucket<Itemtype>::getCount() {
  return count;
}

template<class Itemtype>
Itemtype * Bucket<Itemtype>::searchBucketArray(Itemtype &it) {
  for(int i = 0; i < SIZE; i++) {
    if(items[i] == it) {
      return it;
    }
  }
  return NULL;
}

template<class Itemtype>
bool Bucket<Itemtype>::insertBucketArray(Itemtype &it) {
  for(int i = 0; i < SIZE; i++) {
    if(items[i] == NULL) {
      items[i] = it;
      count++;
      return true;
    }
  }
  return false;
}

template<class Itemtype>
bool Bucket<Itemtype>::removeBucketArray(Itemtype &it) {
  for(int i = 0; i < SIZE; i++) {
    if(items[i] == it) {
      delete items[i];
      count--;
      return true;
    }
  }
  return false;
}

#endif
/*
const int BUCKET_SIZE = 3;



template<typename K, typename V>
class Bucket{
private:
    int count;
    struct BucketItem
    {
        K key;
        V value;
    };
    BucketItem *bucketArray;
public:
    Bucket();
    ~Bucket();
    int getCount();
    bool insertBucketArray(K, V);
    bool searchBucketArray(K);
    bool removeBucketArray(K);
};

template<typename K, typename V>
Bucket<K,V>::Bucket() {
    bucketArray = new V[BUCKET_SIZE];
    count = 0;
}

template<typename K, typename V>
Bucket<K,V>::~Bucket() {
    for(int i = 0; i < BUCKET_SIZE; i++) {
        if(bucketArray[i] != NULL) {
            delete bucketArray[i];
        }
    }
    delete[] bucketArray;
}

template<typename K, typename V>
int Bucket<K,V>::getCount() {
    return count;
}

template<typename K, typename V>
bool Bucket<K,V>::searchBucketArray(K key) {
    int index = 0;

    while (index < BUCKET_SIZE)
    {
        if (bucketArray[index].key == key)
            return true;
        index++;
    }
    //  int index = 0;
    //  if(bucketArray[index]->getKey() == key) {
    //    return bucketArray[index]->getValue();
    //  } else if(bucketArray[index + 1]->getKey() == key) {
    //    return bucketArray[index + 1]->getValue();
    //  } else if(bucketArray[index + 2]->getKey() == key) {
    //    return bucketArray[index + 2]->getValue();
    //  }
    return false;
}

template<typename K, typename V>
bool Bucket<K,V>::insertBucketArray(K key, V value) {
  int index = 0;
  while(index < BUCKET_SIZE) {
    if(bucketArray[index] == NULL) {
      bucketArray[index] = BucketItem(key, value);
      count++;
      return true;
    }
    index++;
  }
    return false;
    //  int index = 0;
    //  HashEntry<K,V> *temp = new HashEntry<K,V>(key value);
    //  // if empty index is at 0
    //  if(bucketArray[index] == NULL) {
    //    bucketArray[index] = temp;
    //    count++;
    //  } else if(bucketArray[index + 1] == NULL) { //if empty index is at 1
    //    bucketArray[index] = temp;
    //    count++;
    //  } else if(bucketArray[index + 2] == NULL) { // if empty index is at 2
    //    bucketArray[index] = temp;
    //    count++;
    //  }
}

template<typename K, typename V>
bool Bucket<K,V>::removeBucketArray(K key) {
    int index = 0;

    while (index < BUCKET_SIZE)
    {
        if (bucketArray[index].key == key)
        {
            delete bucketArray[index];
            count--;
            return true;
        }
        index++;
    }

    return false;
    //  int index = 0;
    //  // if item is at index[0] of bucketArray
    //  if(bucketArray[index]->getKey() == key) {
    //    HashEntry<K,V> *temp = bucketArray[index];
    //    //bucketArray[index] = NULL;
    //    count--;
    //    return temp->getValue();
    //  } else if(bucketArray[index + 1]->getKey() == key) { // if item is at index[1]
    //    HashEntry<K,V> *temp = bucketArray[index];
    //    //bucketArray[index] = NULL;
    //    count--;
    //    return temp->getValue();
    //  } else if(bucketArray[index + 2]->getKey() == key) { // if item is at index[2]
    //    HashEntry<K,V> *temp = bucketArray[index];
    //    //bucketArray[index] = NULL;
    //    count--;
    //    return temp->getValue();
    //  }
}

#endif
*/
