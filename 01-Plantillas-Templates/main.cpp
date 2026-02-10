/**
 * Compilar:
 *   g++ -std=c++17 -Wall -o main *.cpp
 *
 * Ejecutar:
 *   ./main
 **/
#include "Lista.h"
#include <iostream>

int main() {
  Lista<int> listaInt; // Lista de enteros
  for (int i = 0; i < 6; i++) {
    if (!listaInt.insert(i * 10))
      std::cout << "No se pudo inserta el valor: " << i * 10 << std::endl;
  }
  listaInt.print();
}
