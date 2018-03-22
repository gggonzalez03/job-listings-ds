#ifndef NODE_H
#define NODE_H

using std::ostream;

template<typename K, typename V>
class Node {
private:
    K key;
    V value;
    Node* next;
public:
    Node() {};
    Node(K,V);
    void setK(K);
    K getK();
    void setV(V);
    V getV();
    void setNext(Node*);
    Node* getNext();
    friend ostream& operator<<(ostream&, const Node);
};

template<typename K, typename V>
Node<K,V>::Node(K ky, V va) : key(ky), value(va) {
    next = NULL;
}

template<typename K, typename V>
void Node<K,V>::setK(K ky) {
    key = ky;
}

template<typename K, typename V>
K Node<K,V>::getK() {
    return key;
}

template<typename K, typename V>
void Node<K,V>::setV(V va) {
    value = va;
}

template<typename K, typename V>
V Node<K,V>::getV() {
    return value;
}

template<typename K, typename V>
void Node<K,V>::setNext(Node* ptr) {
    next = ptr;
}

template<typename K, typename V>
Node<K,V>* Node<K,V>::getNext() {
    return next;
}

template<typename K, typename V>
ostream& operator<<(ostream& out, const Node<K,V> n) {
    out << n;
    return out;
}

#endif
