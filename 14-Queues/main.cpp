/**
 * Ejemplo que implementa un queue utilizando una lista ligada
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -Wall -g -o main *.cpp
 * Ejecucion con valgrind:
 *    valgrind --leak-check=full ./main
 *    https://www.youtube.com/watch?v=8JEEYwdrexc 
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -Wall -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/

#include <iostream>
#include "QueueLL.h"


int main() {
  std::cout << "Ejemplo de queue usando listas ligadas\n";

  QueueLL<int> miQueue;
  // isEmpty()
  std::cout << "isEmpty(): " << std::boolalpha << miQueue.isEmpty() << std::endl;
  std::cout << "numElements: " << miQueue.getNumElements() << std::endl;
  std::cout << std::endl;
  // enqueue()
  std::cout << "Enqueue de 15 elementos ..." << std::endl;
  for (int i = 1; i < 16; i++) {
    std::cout << "enqueue(" << i+10 << ")" << std::endl;
    miQueue.enqueue(i+10);
  }
  std::cout << "numElements: " << miQueue.getNumElements() << std::endl;
  miQueue.printQueue();
  std::cout << std::endl;

  // dequeue()
  std::cout << "Dequeue de 5 elementos ..." << std::endl;
  try {
    for (int i = 1; i < 6; i++) {
      std::cout << "dequeue() " << std::endl;
      miQueue.dequeue();
    }
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico el queue" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico el queue" << std::endl;
  }
  std::cout << "numElements: " << miQueue.getNumElements() << std::endl;
  miQueue.printQueue();
  std::cout << std::endl;

  // peek()
  try {
    std::cout << "peek(): " << miQueue.peek() << std::endl;
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico el queue" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico el queue" << std::endl;
  } 
  miQueue.printQueue();
  std::cout << std::endl;


  return 0;
}
