#ifndef _STACKLL_H_
#define _STACKLL_H_

#include <iostream>
#include <stdexcept>
#include "NodeStack.h"

template <class T> 
class StackLL {
  private:
    NodeStack<T> *top; // apunta al primer nodo de la lista
    NodeStack<T> *tail; // apunta al ultimo nodo de la lista
    int numElements;
  public:
    StackLL();
    ~StackLL();
    int getNumElements();
    void printStack();
    bool isEmpty();
    void push(T value);
    void pop();
    T peek();
};

// Complejidad O(1)
template <class T>
StackLL<T>::StackLL() {
  top = tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T>
StackLL<T>::~StackLL() {
  NodeStack<T> *p = top, *q = nullptr;
  while(p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  top = tail = nullptr;
  numElements = 0;
}

// Complejidad O(1)
template <class T>
int StackLL<T>::getNumElements() {
  return numElements;
}

// Complejidad O(n)
template <class T>
void StackLL<T>::printStack() {
  if (isEmpty())
    std::cout << "El stack esta vacio" << std::endl;
  else {
    std::cout << "El contenido del stack es:" << std::endl;
    NodeStack<T> *p = top;
    while(p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }  
}

// Complejidad O(1)
template <class T>
bool StackLL<T>::isEmpty() {
  return (top == nullptr && tail == nullptr);
}

// Complejidad O(1)
template <class T>
void StackLL<T>::push(T value) {
  // 1. crear nuevo nodo en memoria
  NodeStack<T> *newNode = new NodeStack<T>(value);
  // 2. apuntar newNode->next al nodo apuntado por top
  newNode->next = top;
  // 3. actualizar top para apuntar a newNode
  top = newNode;
  if (numElements == 0)
    tail = newNode;
  numElements++;
}

// Complejidad O(1)
template <class T>
void StackLL<T>::pop() {
  if (isEmpty())
    throw std::out_of_range("El stack esta vacio");
  else {
    NodeStack<T> *p = top;
    // Si el stack tiene un solo nodo
    if (p != nullptr && p->next == nullptr)
      top = tail = nullptr;
    else
      top = p->next;
    delete p;
    p = nullptr;
    numElements--;
  }
}

// Complejidad O(1)
template <class T>
T StackLL<T>::peek() {
  if (isEmpty())
    throw std::out_of_range("El stack esta vacio");
  else
    return top->data;
}



#endif // _STACKLL_H_