#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include "NodeBST.h"

template <class T>
class BST {
  private:
    NodeBST<T> *root;

    void clearMemory(NodeBST<T> *p);
    void print2D(NodeBST<T> *root, int space);
    NodeBST<T>* insertRecursive(NodeBST<T>*root, T value);
    NodeBST<T>* deleteRecursive(NodeBST<T> *root, T value);
    NodeBST<T>* getSuccesor(NodeBST<T> *root);

  public:
    BST();
    ~BST();
    void printTree();
    bool search(T value);
    void insert(T value);
    void deleteNode(T value);
};

// O(1)
template <class T>
BST<T>::BST() : root(nullptr) {}

// O(n)
template <class T>
BST<T>::~BST() {
  clearMemory(root);
}

// O(n)
template <class T>
void BST<T>::clearMemory(NodeBST<T> *p) {
  if (p != nullptr) {
    clearMemory(p->left);
    clearMemory(p->right);
    delete p;
    p = nullptr;
  }
}

// O(n)
template <class T> 
void BST<T>::print2D(NodeBST<T> *p, int space) {
  // Caso base
  if (p == nullptr)
    return;
  // Incrementa la distancia entre niveles
  space += 5;
  // Procesa hijo derecho
  print2D(p->right, space);
  // Imprime el nodo actual despues de los espacios necesarios
  std::cout << std::endl;
  for (int i = 5; i < space; i++)
    std::cout << " ";
  std::cout << p->data << std::endl;
  // Procesa el hijo izquierdo
  print2D(p->left, space);
}

// O(n)
template <class T> 
void BST<T>::printTree() {
  print2D(root, 0); 
}

// Peor caso O(h) donde h es la altura del BST
template <class T>
bool BST<T>::search(T value) {
  NodeBST<T> *p = root;
  while (p != nullptr) {
    if (p->data == value)
      return true;
    else 
      p = (value < p->data) ? p->left : p->right;
  }
  return false;
}

// Peor caso complejidad O(h) donde h es la altura del BST
template <class T>
NodeBST<T>* BST<T>::insertRecursive(NodeBST<T>*p, T value) {
  if (p == nullptr) // El BST esta vacio
    p = new NodeBST<T>(value);
  else if (value < p->data) // insert a la izquierda
    p->left = insertRecursive(p->left, value);
  else if (value > p->data) // insert a la derecha
      p->right = insertRecursive(p->right, value);
  else
    std::cout << "El elemento " << value << " ya existe en el BST" << std::endl;
  return p;
}

// Peor caso complejidad O(h) donde h es la altura del BST
template <class T>
void BST<T>::insert(T value) {
  root = insertRecursive(root, value);
}

// Peor caso complejidad O(h) donde h es la altura del BST
template <class T> 
NodeBST<T>* BST<T>::getSuccesor(NodeBST<T> *root) {
  NodeBST<T> *current = root;
  while (current != nullptr && current->left != nullptr) {
    current = current->left;
  }
  return current;
}

// Peor caso complejidad O(h) donde h es la altura del BST
template <class T> 
NodeBST<T>* BST<T>::deleteRecursive(NodeBST<T> *p, T value) {
  NodeBST<T> *current = p;
  // caso base, arbol BST esta vacio
  if (p == nullptr) // ERROR corregido, p->data no puede accederse 
    return p;
  if (value < p->data)
    p->left = deleteRecursive(p->left, value);
  else if (value > p->data)
    p->right = deleteRecursive(p->right, value);
  else { // localizamos el nodo a borrar
    // Caso 1. El nodo a borrar no tiene hijos
    if (p->left == nullptr && p->right == nullptr) {
      delete p;
      p = nullptr;
      return p;
    } // Caso 2. El nodo a borrar solo tiene un hijo
    else if (p->left == nullptr) { // solo tiene hijo derecho
      current = p->right;
      delete p;
      p = nullptr;
      return current;
    } 
    else if (p->right == nullptr) { // solo tiene hijo izquierdo
      current = p->left;
      delete p;
      p = nullptr;
      return current;
    }
    //Caso 3. El nodo a borrar tiene dos hijos
    current = getSuccesor(p->right);
    p->data = current->data;
    p->right = deleteRecursive(p->right, current->data);
  }
  return p;
}

// Peor caso complejidad O(h) donde h es la altura del BST
template <class T>
void BST<T>::deleteNode(T value) {
  root = deleteRecursive(root, value);
}

#endif // _BST_H_