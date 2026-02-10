#ifndef _LISTATEMPLATE_H_
#define _LISTATEMPLATE_H_

#include <iostream>
#include <vector>

const int MAX = 100;

template <class T>
class ListaTemplate {
  private:
    std::vector<T> data;
    int currentSize;
  public:
    ListaTemplate();
    ~ListaTemplate();
    bool insert(T value);
    void print();
    // To-do Act 1.1
    void erase();
    T getData(int index);
    int getSize();
    // findMin
};

template <class T>
ListaTemplate<T>::ListaTemplate() {
  std::cout << "Constructor llamado por default " << this << std::endl; 
  data.clear();
  currentSize = 0;
}

template <class T>
ListaTemplate<T>::~ListaTemplate() {
  std::cout << "Destructor llamado por default " << this << std::endl;
  data.clear();
  currentSize = 0;
}

template <class T>
bool ListaTemplate<T>::insert(T value) {
  if (currentSize < MAX) {
    data.push_back(value);
    currentSize++;
    return true;
  }
  return false;
}

template <class T>
void ListaTemplate<T>::print() {
  for (int i = 0; i < currentSize; i++)
    std::cout << "[" << i << "] - " << data[i] << std::endl;
}




#endif // _LISTATEMPLATE_H_

