/**
 * Ejemplo que implementa un stack utilizando una lista ligada
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
#include "StackLL.h"

int main() {
  StackLL<int> myStack;
  // isEmpty()
  std::cout << "isEmpty(): " << std::boolalpha << myStack.isEmpty() << std::endl;
  std::cout << "numElements: " << myStack.getNumElements() << std::endl;
  std::cout << std::endl;

  // push
  std::cout << "Push de 5 elementos..." << std::endl;
  for (int i = 1; i < 6; i++) {
    std::cout << "push(" << i+10 << ")" << std::endl;
    myStack.push(i+10);
  }
  std::cout << "numElements: " << myStack.getNumElements() << std::endl;
  myStack.printStack();
  std::cout << std::endl;

  // pop excepcion
  std::cout << "Pop de 3 elementos..." << std::endl;
  for (int i = 1; i < 4; i++) {
    try {
      myStack.pop();
    }
    catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl << "No se modifico la lista" << std::endl;
    }    
    catch (...) {
      std::cout << "Error desconocido, no se modifico el stack" << std::endl;
    }
  }
  std::cout << "numElements: " << myStack.getNumElements() << std::endl;
  myStack.printStack();
  std::cout << std::endl;

  // peek excepcion
  try {
    std::cout << "peek: " << myStack.peek() << std::endl;
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico el stack" << std::endl;
  }    
  catch (...) {
    std::cout << "Error desconocido, no se modifico el stack" << std::endl;
  }
  // isEmpty()
  std::cout << "isEmpty(): " << std::boolalpha << myStack.isEmpty() << std::endl;
  myStack.printStack();
  std::cout << std::endl;

  return 0;
}