#ifndef _LINKED_LIST_TEMPLATE_
#define _LINKED_LIST_TEMPLATE_

#include <iostream>
#include <iomanip>
#include "Node.h"
using namespace std;

//Tạo Linked List
template <class T>
class LinkedList
{
public:
  Node<T>* head, *tail;

  void DelHead();
  void DelTail();
  void Destroy();
  void AddHead(T);
  void AddTail(T);
  void DelData(T);
  void DelAny(int);
  void reverseList();
  void AddAny(T, int);

  bool isExist(T) const;
  bool isContainUniqueItem() const;
  bool operator == (const LinkedList<T>&);
  bool operator != (const LinkedList<T>&);

  int Size() const;
  int isEmpty() const;
  int getPos(T) const;

  LinkedList<T>& beContainUniqueItem();
  LinkedList<T>& operator=(const LinkedList<T>&);
  LinkedList<T>& operator+=(const LinkedList<T>&);

  T getHead() const;

  string toString() const;

  Node<T>* getNodeAt(int) const;

  template <class U> friend ostream &operator<<(ostream &, const LinkedList<U> &);

  LinkedList(Node<T>* head = NULL, Node<T>* tail = NULL) : head(head), tail(tail){}
  LinkedList(const LinkedList<T>&);
  ~LinkedList();
};

template <class T>
void LinkedList<T>::DelHead(){
  if (this->head == NULL)
    {
        return;
    }
    else
    {
        Node<T> *p = this->head;
        this->head = this->head->next;
        delete p;
    }
}

template <class T>
void LinkedList<T>::DelTail(){
  if (this->head == NULL)
    {
        return;
    }
    else
    {
        Node<T> *p = this->getNodeAt(this->Size() - 2);
        this->tail = p;
        Node<T> *q = this->tail->next;
        this->tail->next = NULL;
        delete q;
    }
}

template <class T>
void LinkedList<T>::Destroy(){
  while(this->head != NULL){
        Node<T>* p = this->head;
        this->head = this->head->next;
        delete p;
  }
}

template <class T>
void LinkedList<T>::AddHead(T data){
  Node<T>* p = p->CreateNode(data);
  if (this->head == NULL)
    {
        this->head = this->tail = p;
    }
    else
    {
        p->next = this->head;
        this->head = p;
    }
}

template <class T>
void LinkedList<T>::AddTail(T data){
  Node<T>* p = p->CreateNode(data);
  if (this->head == NULL)
    {
        this->head = this->tail = p;
    }
    else
    {
        this->tail->next = p;
        this->tail = p;
    }
}

template <class T>
void LinkedList<T>::DelData(T data){
  this->DelAny(this->getPos(data));
}

template <class T>
void LinkedList<T>::DelAny(int pos){
   if (this->head == NULL || pos > this->Size() - 1 || pos < 0)
   {
       return;
   }
   else
   {  
       if (pos == 0)
       {
           this->DelHead();
       }
       else if (pos == this->Size() - 1)
       {
           this->DelTail();
       }
       else
       {
           Node<T> *k = this->getNodeAt(pos);
           Node<T> *p = this->getNodeAt(pos - 1);
           p->next = k->next;
           delete k;
       }
   }
}

template <class T>
void LinkedList<T>::reverseList(){
  Node<T>* prev = NULL;
  Node<T>* current = this->head;
  Node<T>* next = NULL;
  this->tail = this->head;  // After reversing, the current head will become the tail
  while (current != NULL) {
    next = current->next;   // Store the next node
    current->next = prev;   // Reverse the current node's pointer
    prev = current;         // Move prev to this node
    current = next;         // Move to the next node
  }
  this->head = prev;        // Set the new head of the reversed list
}

template <class T>
void LinkedList<T>::AddAny(T data, int pos){
  Node<T>* p = p->CreateNode(data);
  if (this->head == NULL)
    {
        this->head = this->tail = p;
    }
    else
    {
        if (pos == this->Size())
        {
            this->AddTail(p->data);
        }
        else
        {
            Node<T> *k = this->getNodeAt(pos - 1);
            Node<T> *g = k->next;
            p->next = g;
            k->next = p;
        }
    }
}

template <class T>
int LinkedList<T>::Size() const{
  int count = 0;
  for (Node<T> *p = this->head; p != NULL; p = p->next)
  {
    count++;
  }
  return count;
}

template <class T>
int LinkedList<T>::isEmpty() const{
  if (this->head == NULL) return 1;
  return 0;
}

template <class T>
int LinkedList<T>::getPos(T data) const{
  int i = 0;
  for (Node<T>* p = this->head; p != NULL; p = p->next){
    if (p->data == data) return i;
    i++;
  }
  return -1;
}

template <class T>
bool LinkedList<T>::isExist(T data) const{
  if (this->isEmpty()) return false;
  for (Node<T>* p = this->head; p != NULL; p = p->next){
      if (p->data == data) return true;
  }
  return false;
}

template <class T>
bool LinkedList<T>::isContainUniqueItem() const{
  for (Node<T>* p = this->head; p != NULL; p = p->next){
    for (Node<T>* k = p->next; k != NULL; k = k->next){
      if (p->data == k->data) return false; 
    }
  }
  return true;
}

template <class T>
bool LinkedList<T>::operator==(const LinkedList<T>& other){
  if (this->Size() != other.Size()) return false;
  else{
    Node<T>* p = this->head;
    Node<T>* k = other.head;
    while (p != NULL && k != NULL) {
      if (p->data != k->data) return false;
      p = p->next;
      k = k->next;
    }
    return true;
  }
}

template <class T>
bool LinkedList<T>::operator!=(const LinkedList<T>& other){
  return (!(*this == other));
}

template <class T>
LinkedList<T>& LinkedList<T>::beContainUniqueItem(){
  if (!this->head) return *this; // Kiểm tra nếu danh sách rỗng thì trả về ngay lập tức

    Node<T>* p = this->head;
    while (p != NULL) {
        Node<T>* k = p;
        while (k->next != NULL) {
            if (k->next->data == p->data) {
                Node<T>* temp = k->next;
                k->next = k->next->next;
                delete temp;
                if (k->next == NULL) {
                    this->tail = k;
                }
            } else {
                k = k->next;
            }
        }
        p = p->next;
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other){
  if(this->head != NULL){
    this->Destroy();
    this->head = this->tail = NULL;
  }
  Node<T>* current = other.head;
  while (current)
  {
    this->AddTail(current->data);
    current = current->next;
  }
  return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& other){
  for (Node<T>* p = other.head; p != NULL; p = p->next){
    this->AddTail(p->data);
  }
  return *this;
}

template <class T>
T LinkedList<T>::getHead() const{
  T output;
  if (this->head != NULL) output = this->head->data;
  return output;
}

template <class T>
string LinkedList<T>::toString() const{
    string output = "";
    for (Node<T>* p = this->head; p != NULL; p = p->next){
        output += p->data;
    }
    return output;
}

template <class T>
Node<T>* LinkedList<T>::getNodeAt(int pos) const{
  if (this->head == NULL || pos > this->Size())
    {
        return NULL;
    }
    else
    {
        Node<T> *k = this->head;
        for (int i = 0; i < pos; i++)
        {
           k = k->next;
        }
        return k;
    }
}

template <class T>
ostream &operator << (ostream &out, const LinkedList<T> &x){
    for (Node<T>* p = x.head; p != NULL; p = p->next){
        cout << p->data;
        if (p != x.tail) cout << ",";
    }
    return out;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other){
  this->head = this->tail = nullptr;
  Node<T>* current = other.head;
  while (current)
  {
    this->AddTail(current->data);
    current = current->next;
  }
}

template <class T>
LinkedList<T>::~LinkedList()
{
  while(this->head != NULL){
        Node<T>* p = this->head;
        this->head = this->head->next;
        delete p;
  }
}

#endif