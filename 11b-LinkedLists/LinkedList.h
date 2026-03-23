#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "NodeLinkedList.h"

template <class T> 
class LinkedList {
  private:
    NodeLinkedList<T> *head; // apunta al primer nodo de la lista
    NodeLinkedList<T> *tail; // apunta al ultimo nodo de la lista
    int numElements;
  public:
    LinkedList();
    ~LinkedList();
    int getNumElements();
    void printList();
    void addFirst(T value);
    void addLast(T value);
};

// Complejidad O(1)
template <class T>
LinkedList<T>::LinkedList() {
  std::cout << "-->Constructor LinkedList llamado automaticamente: " << this << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T>
LinkedList<T>::~LinkedList() {
  std::cout << "-->Destructor LinkedList llamado automaticamente: " << this << std::endl;
  NodeLinkedList<T> *p = head, *q = nullptr;
  while(p != nullptr) {
    q = p->next;
    //std::cout << "Liberando nodo: " << p->data << std::endl;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(1)
template <class T>
int LinkedList<T>::getNumElements() {
  return numElements;
}

// Complejidad O(n)
template <class T>
void LinkedList<T>::printList() {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido de la lista es:" << std::endl;
    NodeLinkedList<T> *p = head;
    while(p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }  
}

// Complejidad O(1)
template <class T>
void LinkedList<T>::addFirst(T value) {
  // 1. crear nuevo nodo en memoria
  NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
  // 2. apuntar newNode->next al nodo apuntado por head
  newNode->next = head;
  // 3. actualizar head para apuntar a newNode
  head = newNode;
  if (numElements == 0)
    tail = newNode;
  numElements++;
}

// Complejidad O(1)
template <class T>
void LinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else {
    // 1. crear nuevo nodo en memoria
    NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
    // 2. apuntar tail->next a newNode
    tail->next = newNode;
    // 3. actualizar tail para apuntar a newNode
    tail = newNode;
    numElements++;
  }
}


#endif // _LINKEDLIST_H_