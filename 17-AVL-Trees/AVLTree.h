#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <iostream>
#include "NodeAVL.h"
#include "QueueLL.h"

template <class T>
class AVLTree {
  private:
    NodeAVL<T> *root;
    void clearMemory(NodeAVL<T> *p);
    void print2D(NodeAVL<T> *root, int space);
    // Metodos auxiliares para recorridos
    void recursivePreorder(NodeAVL<T> *root);
    void recursiveInorder(NodeAVL<T> *root);
    void recursivePostorder(NodeAVL<T> *root);
    void auxiliarLevelByLevelOrder(NodeAVL<T> *root);
    // AVL Tree methods
    int height(NodeAVL<T> *node);
    int getBalance(NodeAVL<T> *node);
    NodeAVL<T>* rightRotate(NodeAVL<T>* y);
    NodeAVL<T>* leftRotate(NodeAVL<T>* x);
    NodeAVL<T> *insertRecursive(NodeAVL<T> *p, T value);
    NodeAVL<T> *deleteRecursive(NodeAVL<T> *p, T value);
    NodeAVL<T> *getSuccessor(NodeAVL<T> *p);

  public:
    AVLTree();
    ~AVLTree();
    void printTree();
    // Recorridos
    void preorder();
    void inorder();
    void postorder();
    void levelByLevel();
    // AVL Tree methods
    bool search(T value);
    void insert(T value);
    void remove(T value);
};

// O(1)
template <class T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <class T>
AVLTree<T>::~AVLTree() {
  clearMemory(root);
}

// O(n)
template <class T>
void AVLTree<T>::clearMemory(NodeAVL<T> *p) {
  if (p != nullptr) {
    clearMemory(p->left);
    clearMemory(p->right);
    delete p;
    p = nullptr;
  }
}

// O(n)
template <class T> 
void AVLTree<T>::print2D(NodeAVL<T> *p, int space) {
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
void AVLTree<T>::printTree() {
  print2D(root, 0); 
}

// Peor caso complejidad O(n) donde n es el numero de nodos del AVLTree
template <class T>
void AVLTree<T>::recursivePreorder(NodeAVL<T> *p) {
  if (p != nullptr) {
      std::cout << p->data << ", ";
      recursivePreorder(p->left);
      recursivePreorder(p->right);
  }
}

// Peor caso complejidad O(n) donde n es el numero de nodos del AVLTree
template <class T>
void AVLTree<T>::preorder() {
  std::cout << "preorder(): " << std::endl;
  recursivePreorder(root);
  std::cout << std::endl;
}

// Peor caso complejidad O(n) donde n es el numero de nodos del AVLTree
template <class T>
void AVLTree<T>::recursiveInorder(NodeAVL<T> *p) {
  if (p != nullptr) {
      recursiveInorder(p->left);
      std::cout << p->data << ", ";
      recursiveInorder(p->right);
  }
}

// Peor caso complejidad O(n) donde n es el numero de nodos del AVLTree
template <class T>
void AVLTree<T>::inorder() {
  std::cout << "inorder(): " << std::endl;
  recursiveInorder(root);
  std::cout << std::endl;
}

// Peor caso complejidad O(n) donde n es el numero de nodos del AVLTree
template <class T>
void AVLTree<T>::recursivePostorder(NodeAVL<T> *p) {
  if (p != nullptr) {
      recursivePostorder(p->left);
      recursivePostorder(p->right);
      std::cout << p->data << ", ";
  }
}

// Peor caso complejidad O(n) donde n es el numero de nodos del AVLTree
template <class T>
void AVLTree<T>::postorder() {
  std::cout << "postorder(): " << std::endl;
  recursivePostorder(root);
  std::cout << std::endl;
}

// O(n)
template <class T> 
void AVLTree<T>::auxiliarLevelByLevelOrder(NodeAVL<T> *p) {
  QueueLL<NodeAVL<T> *> fila;
  fila.enqueue(p);
  while (!fila.isEmpty()) {
    NodeAVL<T> *q = fila.peek();
    fila.dequeue();
    std::cout << q->data << ", ";
    if (q->left != nullptr)
      fila.enqueue(q->left);
    if (q->right != nullptr)
      fila.enqueue(q->right);
  }
} 

// O(n)
template <class T> 
void AVLTree<T>::levelByLevel() {  
  std::cout << "levelByLevel():" << std::endl;
    auxiliarLevelByLevelOrder(root);
  std::cout << std::endl;

}

// O(h) donde h es la altura del AVL
template <class T> 
bool AVLTree<T>::search(T value) {
  NodeAVL<T> *p = root;
  while (p != nullptr) {
    if (p->data == value)
      return true;
    else
      p = (value < p->data) ? p->left : p->right;
  }
  return false;
}

// O(1)
template <class T> 
int AVLTree<T>::height(NodeAVL<T> *node) {
  if (node == nullptr)
    return 0;
  else
    return node->height;
}

// O(1)
template <class T> 
int AVLTree<T>::getBalance(NodeAVL<T> *node) {
    if (node == nullptr)
      return 0;
    else
      return height(node->left) - height(node->right);
}

template <class T> 
NodeAVL<T>* AVLTree<T>::rightRotate(NodeAVL<T>* y) {
  NodeAVL<T> *x = y->left;
  NodeAVL<T> *T2 = x->right;
  // Realizar la rotacion
  x->right = y;
  y->left = T2;
  // Actualizamos alturas 
  y->height = std::max(height(y->left), height(y->right)) + 1;
  x->height = std::max(height(x->left), height(x->right)) + 1;
  // regresar la nueva raiz
  return x;
}

template <class T>
NodeAVL<T> * AVLTree<T>::leftRotate(NodeAVL<T> *x) {
  NodeAVL<T> *y = x->right;
  NodeAVL<T> *T2 = y->left;
  // Realizar la rotacion
  y->left = x;
  x->right = T2;
  // Actualizar alturas
  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;
  // regresar la nueva raiz
  return y;
}

template<class T>
NodeAVL<T>* AVLTree<T>::insertRecursive(NodeAVL<T> *node, T key) {
    // 1. Realizar la insercion normal en un BST
    if (node == nullptr)
      return(new NodeAVL<T>(key));
    if (key < node->data)
      node->left = insertRecursive(node->left, key);
    else if (key > node->data)
      node->right = insertRecursive(node->right, key);
    else // Equal keys are not allowed in BST
      return node;

    // 2. Actualizar height de los ancestros del nodo insertado 
    node->height = 1 + std::max(height(node->left), height(node->right));

    // 3. Obtener el factor de balance de su nodo ancestro
    //    para verificar si este se desbalancea
    int balance = getBalance(node);

    // Si se desbalancea, entonces hay 4 casos
    // y es hijo izquierdo de z, además x es hijo izquierdo de y
    // Caso Left Left
    if (balance > 1 && key < node->left->data)
      return rightRotate(node);
    // y es hijo derecho de z, además x es hijo derecho de y
    // Caso Right Right
    if (balance < -1 && key > node->right->data)
      return leftRotate(node);
    // y es hijo izquierdo de z, además x es hijo derecho de y
    // Caso Left Right
    if (balance > 1 && key > node->left->data) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    // y es hijo derecho de z, además x es hijo izquierdo de y
    // Caso Right Left
    if (balance < -1 && key < node->right->data) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
    // Regresar el apuntador a node (sin cambio)
    return node;
  }

  template<class T>
  void AVLTree<T>::insert(T valor) {
    root = insertRecursive(root, valor);  
  }

  template <class T>
  NodeAVL<T>* AVLTree<T>::getSuccessor(NodeAVL<T> *p) {
    NodeAVL<T> *current = p;
    while (current && current->left != NULL) {
      current = current->left;
    }
    return current;
  }

  template <class T>
  NodeAVL<T>* AVLTree<T>::deleteRecursive(NodeAVL<T>* root, T value) { 
    // 1. Realiza borrado estandar en BST
    if (root == nullptr)
      return root;
    // Si key < root->data, entonces esta en subarbol izquierdo
    if (value < root->data)
      root->left = deleteRecursive(root->left, value);
    // Si key > root->data, entonces esta en subarbol derecho
    else if(value > root->data)
      root->right = deleteRecursive(root->right, value);
    // Si key == root->data, entonces este es el nodo a borrar
    else { // Hemos localizado el nodo a borrar
      // Node a borrar con un solo hijo o sin hijos
      if((root->left == nullptr) || (root->right == nullptr)) {
        NodeAVL<T> *temp = root->left ? root->left : root->right;
        // Nodo a borrar sin hijos
        if (temp == nullptr) {
          temp = root;
          root = nullptr;
        }
        else // Nodo a borrar con un solo hijo 
          *root = *temp; // Copiar el contenido del hijo en root
        delete temp;
      }
      else {
        // Nodo a borrar con dos hijos
        NodeAVL<T> *temp = getSuccessor(root->right);
        root->data = temp->data;
        root->right = deleteRecursive(root->right, temp->data);
      }
    }
    // Si el AVL tiene solo un nodo entonces regresalo
    if (root == nullptr)
      return root;
    // 2. Actualizar height del nodo actual 
    root->height = 1 + std::max(height(root->left), height(root->right));
    // 3. Obtener el factor de balance de este nodo 
    int balance = getBalance(root);
    // Si se desbalancea, entonces hay 4 casos
    // Caso Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
      return rightRotate(root);
    // Caso Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Caso Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    // Caso Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
  }

  template<class T>
  void AVLTree<T>::remove(T valor) {
    root = deleteRecursive(root, valor);  
  }


#endif // _AVLTREE_H_