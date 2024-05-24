#ifndef _Prod_
#define _Prod_

#include <string>
#include "LinkedListTemplate.h"
#include "anyFunction.h"
//Tạo sản xuất A => alpha/beta
class Prod
{
public:
    string A;
    LinkedList<string> alpha;

    string toString() const;
    string getAlpha() const;
    string getUniqueSymbol();

    bool operator == (const Prod);

    Prod& operator = (const Prod &);

    friend ostream &operator<<(ostream &, const Prod &);

    Prod(string, LinkedList<string>);
    Prod();
    ~Prod();
};

string Prod::toString() const{
    string output = this->A + " -> ";
    for (Node<string>* p = this->alpha.head; p != NULL; p = p->next){
        output += p->data;
    }
    return output;
}

string Prod::getAlpha() const{
    string input = "";
    for (Node<string>* p = this->alpha.head; p != NULL; p = p->next){
        input += p->data;
    }
    return input;
}

string Prod::getUniqueSymbol(){
    string output = "";
    for (Node<string>* p = this->alpha.head; p != NULL; p = p->next){
        output += getUnique(p->data);
    }
    return getUnique(output);
}

bool Prod::operator==(const Prod other){
    return (this->A == other.A) && (this->alpha == other.alpha);
}

Prod& Prod::operator = (const Prod &Prod){
    this->A = Prod.A;
    this->alpha = Prod.alpha;
    return *this;
}

ostream &operator<<(ostream &out,const Prod &Prod){
    if (Prod.A == "") cout << "Empty Prod";
    else{
        cout << Prod.A << " -> ";
        for (Node<string>* p = Prod.alpha.head; p != NULL; p = p->next){
            cout << p->data;
            if (p != Prod.alpha.tail) cout << " | ";
        }
    }
    return out;
}

Prod::Prod(string A, LinkedList<string> alpha)
{
    this->A = A;
    this->alpha = alpha;
}

Prod::Prod(){
    this->A = "";
    this->alpha.Destroy();
}

Prod::~Prod()
{
    this->alpha.Destroy();
}

#endif