/**
 * Ejemplo que implementa una lista ligada con head y tail
 * primera parte (addFirst, addLast)
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -Wall -g -o main *.cpp
 * Ejecucion con valgrind:
 *    valgrind --run-libc-freeres=no --leak-check=full ./main
 *    https://www.youtube.com/watch?v=8JEEYwdrexc 
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -Wall -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/

#include <iostream>
#include "LinkedList.h"

int main() {
  LinkedList<int> miLista;
  //std::cout << "numElements: " << miLista.getNumElements() << std::endl;

  // addFirst
  std::cout << "Agregando 10 elementos al frente..." << std::endl;
  for (int i = 1; i < 11; i++) {
    miLista.addFirst(i);
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << std::endl;

  // addLast
  std::cout << "Agregando 5 elementos al final..." << std::endl;
  for (int i = 20; i < 26; i++) {
    miLista.addLast(i);
  }
  std::cout << "numElements: " << miLista.getNumElements() << std::endl;
  miLista.printList();
  std::cout << std::endl;

  return 0;
}