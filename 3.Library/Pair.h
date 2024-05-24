#ifndef _PAIR_
#define _PAIR_
#include <iostream>
using namespace std;

template <class K, class V>
class Pair {
public:
  K key;
  V value;

  Pair<K, V> CreatePair(K, V);
  Pair<K, V>& operator=(const Pair<K, V>&);

  bool operator==(const Pair<K, V>);

  template <class T, class U> friend ostream &operator<<(ostream &, const Pair<K, V> &);

  Pair(K key1 = K(), V value1 = V()) : key(key1), value(value1) {}
};

template <class K, class V>
Pair<K, V> Pair<K, V>::CreatePair(K key, V value) {
  Pair<K, V> p = new Pair<K, V>;
  p->key = key;
  p->value = value;
  return p;
}

template <class K, class V>
Pair<K, V>& Pair<K, V>::operator=(const Pair<K, V>& other){
  this->key = other.key;
  this->value = other.value;
  return *this;
}

template <class K, class V>
bool Pair<K, V>::operator==(const Pair<K, V> other){
    return (this->key == other.key) && (this->value == other.value);
}

template <class K, class V>
ostream &operator << (ostream &out, const Pair<K, V> &x){
    cout << x.key << " : " << x.value ;
    return out;
}


#endif