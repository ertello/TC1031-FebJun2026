#ifndef _QUEUELL_H_
#define _QUEUELL_H_

#include <iostream>
#include <stdexcept>
#include "NodeQueue.h"

template <class T> 
class QueueLL {
  private:
    NodeQueue<T> *front; // apunta al primer nodo del queue
    NodeQueue<T> *rear; // apunta al ultimo nodo del queue
    int numElements;
  public:
    QueueLL();
    ~QueueLL();
    int getNumElements();
    void printQueue();
    bool isEmpty();
    void enqueue(T value);
    void dequeue();
    T peek();

};

// Complejidad O(1)
template <class T>
QueueLL<T>::QueueLL() {
  //std::cout << "-->Constructor QueueLL llamado automaticamente: " << this << std::endl;
  front = nullptr;
  rear = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T>
QueueLL<T>::~QueueLL() {
  //std::cout << "-->Destructor QueueLL llamado automaticamente: " << this << std::endl;
  NodeQueue<T> *p = front, *q = nullptr;
  while(p != nullptr) {
    q = p->next;
    //std::cout << "Liberando nodo: " << p->data << std::endl;
    delete p;
    p = q;
  }
  front = nullptr;
  rear = nullptr;
  numElements = 0;
}

// Complejidad O(1)
template <class T>
int QueueLL<T>::getNumElements() {
  return numElements;
}

// Complejidad O(n)
template <class T>
void QueueLL<T>::printQueue() {
  if (front == nullptr && rear == nullptr)
    std::cout << "El queue esta vacio" << std::endl;
  else {
    std::cout << "El contenido del queue es:" << std::endl;
    NodeQueue<T> *p = front;
    while(p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }  
}

// Complejidad O(1)
template <class T>
bool QueueLL<T>::isEmpty() {
  return (front == nullptr && rear == nullptr);
}

// Complejidad O(1)
template <class T>
void QueueLL<T>::enqueue(T value) {
  NodeQueue<T> *newNode = new NodeQueue<T>(value);
  if (isEmpty())
    front = rear = newNode;
  else {
    rear->next = newNode;
    rear = newNode;
  }
  numElements++;
}

// Complejidad O(1)
template <class T>
void QueueLL<T>::dequeue() {
  // El queue esta vacio
  if (isEmpty())
    throw std::out_of_range("El queue esta vacio");
  else {
    NodeQueue<T> *p = front;
    // Si el queue tiene un solo nodo
    if (p != nullptr && p->next == nullptr)
      front = rear = nullptr;
    else
      front = p->next;
    delete p;
    p = nullptr;
    numElements--;
  }
}

// Complejidad O(1)
template <class T>
T QueueLL<T>::peek() {
  // El queue esta vacio
  if (isEmpty())
    throw std::out_of_range("El queue esta vacio");
  else
    return front->data;
}

#endif // _QUEUELL_H_