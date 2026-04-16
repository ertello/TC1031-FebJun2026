/**
 * Ejemplo que implementa un Binary Search Tree (BST) (insert, remove, search) 
 * Simulador: https://visualgo.net/en/bst
 * y sus recorridos: preorder, inorder, postorder
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    valgrind --leak-check=full ./main
 *    https://www.youtube.com/watch?v=8JEEYwdrexc 
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/

#include <iostream>
#include "BST.h"

int main() {
  BST<int> myBST;
  std::cout << "Insert: 10, 20, 30, 15, 5, 115, 3, 3" << std::endl;

  myBST.insert(10);
  myBST.insert(20);
  myBST.insert(30);
  myBST.insert(15);
  myBST.insert(5);
  myBST.insert(115);
  myBST.insert(3);
  myBST.insert(3);

  /*
                    10
            5               20
        3             15          30
                                      115
  */

  myBST.printTree();
  std::cout << std::endl;
/*
  std::cout << "Delete: 3 (nodo hoja)" << std::endl;
  myBST.deleteNode(3);
  myBST.printTree();
  std::cout << std::endl;
  std::cout << "Delete: 30 (nodo con un hijo)" << std::endl;
  myBST.deleteNode(30);
  myBST.printTree();
  std::cout << std::endl;
  std::cout << "Delete: 20 (nodo con dos hijos)" << std::endl;
  myBST.deleteNode(20);
  myBST.printTree();
  std::cout << std::endl;
  std::cout << "Delete: 320 (nodo no existe)" << std::endl;
  myBST.deleteNode(320);
  myBST.printTree();
  std::cout << std::endl;
  */

  // Recorridos  
  myBST.preorder();
  myBST.inorder();
  myBST.postorder();
  myBST.levelByLevel();


  return 0;
}