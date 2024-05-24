#ifndef _STEMPLATE_
#define _STEMPLATE_

#include <iostream>
#include <iomanip>
#include "Node.h"
#include "anyFunction.h"
#include "LinkedListTemplate.h"
using namespace std;;

//Định nghĩa Stack gồm các Node
template <class T>
class Stack {
private:
  Node<T>* head, *tail;
public:
  void Push(T);
  void DelHead();
  void DelTail();
  void Destroy();
  void DelAny(int);

  string toString() const;           // Chỉ dùng được khi T thuộc kiểu string, chiều dưới lên
  string getString() const;          // Tương tự toString nhưng có thêm khoảng trắng
  string toStringTopDown() const;    //chiều từ trên xuống

  T Pop();
  T Top() const;

  int Capacity() const;

  bool isEmpty() const;

  Node<T>* GetNodeAt(int) const;
  
  template <class U> friend ostream &operator<<(ostream &, const Stack<U> &);

  Stack(Node<T>* head = NULL, Node<T>* tail = NULL) : head(head), tail(tail) {}
  ~Stack();
};

//Add thêm vào stack
template <class X>
void Stack<X>::Push(X data){
    Node<X>* p = p->CreateNode(data);
    if (this->head == NULL){
        this->head = this->tail = p;
    }
    else{
        p->next = this->head;
        this->head = p;
    }
}

//Xóa Node đầu
template <class X>
void Stack<X>::DelHead(){
    if (this->head == nullptr) return;
    else{
        Node<X>* p = this->head;
        this->head = this->head->next;
        delete p;
    }
}

//Xóa Node cuối
template <class X>
void Stack<X>::DelTail(){
    if (this->head == NULL) return;
    else
    {
        Node<X> *p = this->GetNodeAt(this->Capacity()-2);
        this->tail = p;
        Node<X> *q = this->tail->next;
        this->tail->next = NULL;
        delete q;
    }
}

template <class X>
void Stack<X>::Destroy(){
  while(this->head != NULL){
    Node<X>* p = this->head;
    this->head = this->head->next;
    delete p;
  }
}

//Xóa Node bất kỳ
template <class X>
void Stack<X>::DelAny(int pos){
    if (this->head == NULL || pos > this->Capacity() - 1 || pos < 0)
       cout << "Khong co gi de xoa ca !" << endl;
   else{  
       if (pos == 0) this->DelHead();
       else if (pos == this->Capacity() - 1) this->DelTail();
       else{
           Node<X> *k = this->GetNodeAt(pos);
           Node<X> *p = this->GetNodeAt(pos - 1);
           p->next = k->next;
           delete k;
       }
   }
}

template <class X>
string Stack<X>::toString() const{
    string output = "";
    LinkedList<X> list;
    for (Node<X>* p = this->head; p != NULL; p = p->next){
        list.AddHead(p->data);
    }
    for (Node<X>* p = list.head; p!= NULL; p = p->next){
        output += p->data;
    }
    return output;
}

template <class X>
string Stack<X>::getString() const{
    string output = "";
    LinkedList<X> list;
    for (Node<X>* p = this->head; p != NULL; p = p->next){
        list.AddHead(p->data);
    }
    for (Node<X>* p = list.head; p!= NULL; p = p->next){
        output += p->data + " ";
    }
    return output;
}

template <class X>
string Stack<X>::toStringTopDown() const{
    string output = "";
    for (Node<X>* p = this->head; p!= NULL; p = p->next){
        output += p->data;
    }
    return output;
}

//Xóa đỉnh
template <class X>
X Stack<X>::Pop(){
    X a;
    if (this->head != NULL){
        a = this->head->data;
        this->DelAny(0);
    }
    return a;
}

//Trả về Phần tử trên cùng
template <class X>
X Stack<X>::Top() const{
    X a;
    if (this->head != NULL) return this->head->data;
    return a;
}

//Đếm số phần tử trong Stack
template <class X>
int Stack<X>::Capacity() const{
    int count = 0;
    for (Node<X>* p = this->head; p != NULL; p = p->next) ++count;
    return count;
}

template <class X>
bool Stack<X>::isEmpty() const{
    if (this->head == NULL) return true;
    return false;
}

//Lấy Node tại vị trí thứ N
template <class X>
Node<X>* Stack<X>::GetNodeAt(int pos) const{
    if (this->head == NULL || pos > this->Capacity())
    {
        return NULL;
    }
    else
    {
        Node<X> *k = this->head;
        for (int i = 0; i < pos; i++)
        {
           k = k->next;
        }
        return k;
    }
}

//In toàn bộ stack
template <class X>
ostream &operator << (ostream &out, const Stack<X> &x){
    if (x.isEmpty()) cout << "Stack rỗng";
    else{
        for (Node<X>* p = x.head; p != NULL; p = p->next){
            cout << setw(3) << left << "| " << setw(6) << left << p->data << setw(3) << right << "|" << endl;
        }
    }
    return out;
}

//Hàm Destructor
template <class X>
Stack<X>::~Stack(){
    while(this->head != NULL){
        Node<X>* p = this->head;
        this->head = this->head->next;
        delete p;
    }
}

#endif