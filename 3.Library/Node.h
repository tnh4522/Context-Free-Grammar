#ifndef _NODE_
#define _NODE_

template <class T>
class Node {
public:
  T data;
  Node* next;

  Node<T>* CreateNode(T data);
};

template <class T>
Node<T>* Node<T>::CreateNode(T data) {
  Node<T>* p = new Node<T>;
  p->data = data;
  p->next = NULL;
  return p;
}

#endif