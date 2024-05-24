#ifndef _RCV_
#define _RCV_
#include "Pair.h"
#include "Prod.h"
//RCV<Pair, string>
class RCP{
public:
    Pair<string, string> pair;
    Prod value;

    bool operator==(const RCP&);
    bool operator!=(const RCP&);

    RCP& operator=(const RCP&);

    friend ostream &operator<<(ostream &, const RCP &);

    RCP();
    RCP(Pair<string,string> pa, Prod po);  
};

bool RCP::operator==(const RCP& other){
    return (this->pair == other.pair) && (this->value == other.value);
}

bool RCP::operator!=(const RCP& other){
    return !(*this == other);
}

RCP& RCP::operator=(const RCP& other){
    this->pair = other.pair;
    this->value = other.value;
    return *this;
}

ostream &operator << (ostream &out, const RCP &rcp){
    cout << "M[" << rcp.pair.key << "," << rcp.pair.value << "] = " << rcp.value;
    return out;
}

RCP::RCP(){
    Pair<string,string> p;
    this->pair = p;
    Prod prod;
    this->value = prod;
}

RCP::RCP(Pair<string, string> pair, Prod prod){
    this->pair = pair;
    this->value = prod;
}



#endif