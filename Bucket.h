// Created by Ging Gonzalez and Fawzan Khan
// Bucket class is where items can be stored up to certain capacity
#ifndef BUCKET_H
#define BUCKET_H

template<class Itemtype>
class Bucket {
private:
    Itemtype *items;
    int count;
    int size;
public:
    // Constructors
    Bucket();
    Bucket(int);
    
    //Desctructor
    ~Bucket();
    
    // Returns the number of items in the bucket
    int getCount();
    // Searches the bucket and returns an item that was searched if it exists in the bucket
    Itemtype * searchBucketArray(Itemtype &);
    // Adds an item into the bucket and returns true of the add was successful
    bool insertBucketArray(Itemtype &);
    // Removes an item from the bucket and returns true if the remove was successful
    // Saves the removed item into the passed object parameter
    bool removeBucketArray(Itemtype &);
    // Sets the size of the bucket
    void setSize(int);
    // Traverse the bucket and call the callback for each traversal. It takes an ofstream for an
    // ability to save into a file.
    void traverseBucket(void callback(ofstream &, Itemtype &), ofstream &);
    // Traverse the bucket and call the callback that takes an item
    void printBucket(void callback(Itemtype &));
};

// Constructors
template<class Itemtype>
Bucket<Itemtype>::Bucket() {
    items = new Itemtype[0];
    count = 0;
    size = 0;
}

template<class Itemtype>
Bucket<Itemtype>::Bucket(int s) {
    items = new Itemtype[s];
    count = 0;
    size = s;
}

// Destructor
template<class Itemtype>
Bucket<Itemtype>::~Bucket() {
    delete[] items;
}


// Public member functions
template<class Itemtype>
int Bucket<Itemtype>::getCount() {
    return count;
}

template<class Itemtype>
Itemtype * Bucket<Itemtype>::searchBucketArray(Itemtype &it) {
    bool found = false;
    int i = 0;
    
    if (size <= 0)
        return NULL;
    
    while(!found && i < size)
    {
        if (items[i] == it)
        {
            found = true;
            return &items[i];
        }
        i++;
    }
    return NULL;
}

template<class Itemtype>
bool Bucket<Itemtype>::insertBucketArray(Itemtype &it) {
    Itemtype * temp = new Itemtype();
    
    if (size <= 0)
        return false;
    
    for(int i = 0; i < size; i++) {
        if(items[i] == *temp) {
            items[i] = it;
            count++;
            return true;
        }
    }
    return false;
}

template<class Itemtype>
bool Bucket<Itemtype>::removeBucketArray(Itemtype &it) {
    for(int i = 0; i < size; i++) {
        if(items[i] == it) {
            it = items[i];
            // This will delete the item (set it to an empty itemtype object)
            items[i] = *new Itemtype();
            count--;
            return true;
        }
    }
    return false;
}

template<class Itemtype>
void Bucket<Itemtype>::setSize(int s)
{
    size = s;
    items = new Itemtype[s];
}

template<class Itemtype>
void Bucket<Itemtype>::traverseBucket(void callback(ofstream &, Itemtype &), ofstream & ofs)
{
    Itemtype * temp = new Itemtype();
    if (size)
        for (int i = 0; i < size; i++)
            if (items[i] != *temp)
                callback(ofs, items[i]);
}

template<class Itemtype>
void Bucket<Itemtype>::printBucket(void callback(Itemtype &))
{
    Itemtype * temp = new Itemtype();
    if (size)
        for (int i = 0; i < size; i++)
            if (items[i] != *temp)
                callback(items[i]);
}

#endif
