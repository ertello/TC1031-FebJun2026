/**
 * Ejemplo que implementa uso de memoria dinamica
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -g -o main *.cpp
 * Ejecucion con valgrind:
 *    valgrind --leak-check=full ./main
 *
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/

#include <iostream>

int main() {
  int a = 5, *p;
  p = new int;
  *p = a;
  a = *p + 2;
  std::cout << a << " " << *p << std::endl;
  delete p;
  p = nullptr;

  // int arreglo[10];
  // for (int i = 0; i < 10; i++) 
  //   arreglo[i] = i+1;

  // std::cout << "arreglo[4]: " << arreglo[4] << std::endl;
  // std::cout << "*(arreglo+4): " << *(arreglo+4) << std::endl;
  
  // std::cout << "&arreglo[4]: " << &arreglo[4] << std::endl;
  // std::cout << "(arreglo+4): " << (arreglo+4) << std::endl;
  
}
