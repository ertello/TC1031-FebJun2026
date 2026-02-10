#ifndef _LISTA_H_
#define _LISTA_H_

#include <iostream>
#include <vector>

const int MAX = 100;

template <class T>
class Lista {
  private:
    std::vector<T> data;
    int currentSize;
  public:
    Lista();
    ~Lista();
    bool insert(T value);
    void print();
    // To-do Act 1.1
    void erase();
    T getData(int index);
    int getSize();
    // findMin
};

template <class T>
Lista<T>::Lista() {
  std::cout << "Constructor llamado por default " << this << std::endl; 
  data.clear();
  currentSize = 0;
}

template <class T>
Lista<T>::~Lista() {
  std::cout << "Destructor llamado por default " << this << std::endl;
  data.clear();
  currentSize = 0;
}

template <class T>
bool Lista<T>::insert(T value) {
  if (currentSize < MAX) {
    data.push_back(value);
    currentSize++;
    return true;
  }
  return false;
}

template <class T>
void Lista<T>::print() {
  for (int i = 0; i < currentSize; i++)
    std::cout << "[" << i << "] - " << data[i] << std::endl;
}




#endif // _LISTA_H_

