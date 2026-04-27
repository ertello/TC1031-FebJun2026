#ifndef _SPLAY_TREE_H_
#define _SPLAY_TREE_H_

  #include <iostream>
  #include "NodeSplayTree.h"
  #include "QueueLL.h"

  template <class T>
  class SplayTree { 
    private:
      NodeSplayTree<T> *root;
      int size;
      void clearMemory(NodeSplayTree<T> *p);
      void print2D(NodeSplayTree<T> *p, int space);
      // Metodos auxiliares para recorridos
      void recursivePreorder(NodeSplayTree<T> *root);
      void recursiveInorder(NodeSplayTree<T> *root);
      void recursivePostorder(NodeSplayTree<T> *root);
      void auxiliarLevelByLevelOrder(NodeSplayTree<T> *root);
      // Operaciones de un splay tree
      NodeSplayTree<T>* zig(NodeSplayTree<T> *x);
      NodeSplayTree<T>* zag(NodeSplayTree<T> *x);
      NodeSplayTree<T>* splay(NodeSplayTree<T> *root, T value);
      NodeSplayTree<T>* insertRec(NodeSplayTree<T> *root, T value);
      NodeSplayTree<T>* searchRec(NodeSplayTree<T> *root, T value);
      NodeSplayTree<T>* removeRec(NodeSplayTree<T> *root, T value);

    public: 
      SplayTree();
      ~SplayTree();
      void print();
      // Recorridos
      void preorder();
      void inorder();
      void postorder();
      void levelByLevel();
      // Splay Tree methods
      void buildTestTree();
      void add(T value);
      void find(T value);
      void remove(T value);
      int getSize();

  };

  // O(1)
  template<class T>
  SplayTree<T>::SplayTree() {
    root = nullptr;
    size = 0;
  }
  
  // O(n)
  template<class T>
  SplayTree<T>::~SplayTree() {
    clearMemory(root);
  }
  
  // O(n)
  template<class T>
  void SplayTree<T>::clearMemory(NodeSplayTree<T> *p) {
    if (p != nullptr) {
      clearMemory(p->left);
      clearMemory(p->right);
      delete p;
      p = nullptr;
    }
  }
  
  // O(n)
  template <class T>
  void SplayTree<T>::print() {
      print2D(root, 0);
  }
  
  // O(n)
  template <class T>
  void SplayTree<T>::print2D(NodeSplayTree<T> *root, int space) {
      // Caso base
      if (root == nullptr)
          return;
      // Incrementa la distancia entre niveles
      space += 5;

      // Procesa hijo derecho
      print2D(root->right, space);
      // Imprime el nodo actual despues de los espacios necesarios
      std::cout << std::endl;
      for (int i = 5; i < space; i++)
          std::cout << " ";
      std::cout << root->data << std::endl;
      // Procesa el hijo izquierdo 
      print2D(root->left, space);
  }
  
  // O(n)
  template <class T>
  void SplayTree<T>::recursivePreorder(NodeSplayTree<T> *p) {
    if (p != nullptr) {
        std::cout << p->data << ", ";
        recursivePreorder(p->left);
        recursivePreorder(p->right);
    }
  }

  // O(n)
  template <class T>
  void SplayTree<T>::preorder() {
    std::cout << "preorder(): " << std::endl;
    recursivePreorder(root);
    std::cout << std::endl;
  }

  // O(n)
  template <class T>
  void SplayTree<T>::recursiveInorder(NodeSplayTree<T> *p) {
    if (p != nullptr) {
        recursiveInorder(p->left);
        std::cout << p->data << ", ";
        recursiveInorder(p->right);
    }
  }

  // O(n)
  template <class T>
  void SplayTree<T>::inorder() {
    std::cout << "inorder(): " << std::endl;
    recursiveInorder(root);
    std::cout << std::endl;
  }

  // O(n)
  template <class T>
  void SplayTree<T>::recursivePostorder(NodeSplayTree<T> *p) {
    if (p != nullptr) {
        recursivePostorder(p->left);
        recursivePostorder(p->right);
        std::cout << p->data << ", ";
    }
  }

  // O(n)
  template <class T>
  void SplayTree<T>::postorder() {
    std::cout << "postorder(): " << std::endl;
    recursivePostorder(root);
    std::cout << std::endl;
  }

  // O(n)
  template <class T> 
  void SplayTree<T>::auxiliarLevelByLevelOrder(NodeSplayTree<T> *p) {
    QueueLL<NodeSplayTree<T> *> fila;
    fila.enqueue(p);
    while (!fila.isEmpty()) {
      NodeSplayTree<T> *q = fila.peek();
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
  void SplayTree<T>::levelByLevel() {  
    std::cout << "levelByLevel():" << std::endl;
      auxiliarLevelByLevelOrder(root);
    std::cout << std::endl;

  }
  
  // O(n)
  template<class T>
  void SplayTree<T>::buildTestTree() {

      root = new NodeSplayTree<T>(100);
      root->left = new NodeSplayTree<T>(50);
      root->right = new NodeSplayTree<T>(200);
      root->left->left = new NodeSplayTree<T>(40);
      root->left->left->left = new NodeSplayTree<T>(30);
      root->left->left->left->left = new NodeSplayTree<T>(20);
      size+=6;

    /* // Other test tree
      root = new NodeSplayTree<T>(6);
      root->left = new NodeSplayTree<T>(1);
      root->right = new NodeSplayTree<T>(9);
      root->left->right = new NodeSplayTree<T>(4);
      root->left->right->left = new NodeSplayTree<T>(2);
      root->right->left = new NodeSplayTree<T>(7);
      size+=6;
    */
  }

  // O(1) Rotacion derecha
  template<class T>
  NodeSplayTree<T>* SplayTree<T>::zig(NodeSplayTree<T> *x) {
    NodeSplayTree<T> *y = x->left;
    // Realizar la rotacion
    x->left = y->right;
    y->right = x;
    // regresar la nueva raiz
    return y;
  }
  // O(1) Rotacion izquierda
  template<class T>
  NodeSplayTree<T>* SplayTree<T>::zag(NodeSplayTree<T> *x) {
    NodeSplayTree<T> *y = x->right;
    // Realizar la rotacion
    x->right = y->left;
    y->left = x;
    // regresar la nueva raiz
    return y;
  }

  template<class T>
  NodeSplayTree<T>* SplayTree<T>::splay(NodeSplayTree<T> *root, T value) {
      // Base cases: root is nullptr or
      // value is present at root
      if (root == nullptr || value == root->data)
        return root;
      // value lies in left subtree
      if (value < root->data) {
          // value is not in tree, we are done
          if (root->left == nullptr) return root;
          // Zig-Zig (Left Left)
          if (value < root->left->data) {
              // First recursively bring the key as root of left-left
              root->left->left = splay(root->left->left, value);
              // Do first rotation for root, second rotation is done after else
              root = zig(root);
          }
          else if (value > root->left->data) { // Zig-Zag (Left Right)
              // First recursively bring the key as root of left-right
              root->left->right = splay(root->left->right, value); 
              // Do first rotation for root->left
              if (root->left->right != nullptr)
                  root->left = zag(root->left);
          }
          // Do second rotation for root
          return (root->left == nullptr)? root : zig(root);
      }
      else { // Key lies in right subtree
          // Key is not in tree, we are done
          if (root->right == nullptr) return root;
          // Zig-Zag (Right Left)
          if (value < root->right->data) {
              // Bring the key as root of right-left
              root->right->left = splay(root->right->left, value);
              // Do first rotation for root->right
              if (root->right->left != nullptr)
                  root->right = zig(root->right);
          }
          else if (value > root->right->data) { // Zag-Zag (Right Right)
              // Bring the key as root of right-right and do first rotation
              root->right->right = splay(root->right->right, value);
              root = zag(root);
          }
          // Do second rotation for root
          return (root->right == nullptr)? root: zag(root);
      }
  }
  // O(h), donde h es la altura del arbol
  template<class T>
  NodeSplayTree<T>* SplayTree<T>::insertRec(NodeSplayTree<T> *root, T value) {
      // Simple Case: If tree is empty
      if (root == nullptr) {
        NodeSplayTree<T> *newNode = new NodeSplayTree<T>(value);
        size++;
        return newNode;
      }
      // Bring the closest leaf node to root
      root = splay(root, value);
      // If value is already present, then return
      if (value == root->data) return root;

      // Otherwise allocate memory for new node
      NodeSplayTree<T> *newNode = new NodeSplayTree<T>(value);
      size++;
      // If root's key is greater, make
      // root as right child of newnode
      // and copy the left child of root to newnode
      if (value < root->data) {
          newNode->right = root;
          newNode->left = root->left;
          root->left = nullptr;
      }
      // If root's key is smaller, make
      // root as left child of newnode
      // and copy the right child of root to newnode
      else {
          newNode->left = root;
          newNode->right = root->right;
          root->right = nullptr;
      }
      return newNode; // newnode becomes new root
  }
  // O(h), donde h es la altura del arbol
  template<class T>
  void SplayTree<T>::add(T value) {
    root = insertRec(root, value);
  }
  // O(h), donde h es la altura del arbol
  template<class T>
  NodeSplayTree<T>* SplayTree<T>::searchRec(NodeSplayTree<T> *root, T value) {
    return splay(root, value);
  }
  // O(h), donde h es la altura del arbol
  template<class T>
  void SplayTree<T>::find(T value) {
    root = searchRec(root, value);
  }
  // O(h), donde h es la altura del arbol
  template<class T>
  NodeSplayTree<T>* SplayTree<T>::removeRec(NodeSplayTree<T> *root, T value) {
      NodeSplayTree<T> *temp;
      if (!root) 
        return nullptr;

      // Splay the given value    
      root = splay(root, value);

      // If value is not present, then return root
      if (value != root->data)
        return root;

      // If value is present
      // If left child of root does not exist
      // make root->right as root   
      if (!root->left) {
        temp = root;
        root = root->right;
      }
      // Else if left child exits
      else {
          temp = root;
          /* Note: Since value == root->data,
          so after Splay(value, root->lchild),
          the tree we get will have no right child tree
          and maximum node in left subtree will get splayed */
          // New root
          root = splay(root->left, value);

          // Make right child of previous root  as
          // new root's right child
          root->right = temp->right;
      }
      // free the previous root node, that is,
      // the node containing the key
      delete temp;
      size--;
      // return root of the new Splay Tree
      return root;
  }
  // O(h), donde h es la altura del arbol
  template<class T>
  void SplayTree<T>::remove(T value) {
      root = removeRec(root, value);
  }
  // O(1)
  template<class T>
  int SplayTree<T>::getSize() {
    return size;
  }

#endif // _SPLAY_TREE_H_