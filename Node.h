#ifndef NODE_H
#define NODE_H

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
};

Node::Node(K ky, V va) : key(ky), value(va) {
  next = NULL;
}

void Node::setk(K ky) {
  key = ky;
}

K Node::getK() {
  return key;
}

void Node::setV(V va) {
  value = va;
}

V Node::getV() {
  return value;
}

void Node::setNext(Node* ptr) {
  next = ptr;
}

Node* Node::getNext() {
  return next;
}

#endif
