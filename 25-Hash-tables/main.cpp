/**
* Ejemplo que implementa una Tabla Hash que utiliza 
* el método de Dirección Abierta (hashing cerrado)
* con Muestreo Cuadrático para manejo de colisiones
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
#include <iomanip>
#include "HashTable.h"

int main() {
  std::cout << "Hash Table Example!\n";

  HashTable<int, std::string> myHashTable;

  myHashTable.setMaxSize(7);
  std::cout << "Table current size: " << myHashTable.getNumElements() << std::endl;
  std::cout << std::setprecision(4);
  std::cout << "Table alfa: " << (double)myHashTable.getAlfa() << std::endl;
  try {
    std::cout << "Add (50, Hello)" << std::endl;
    myHashTable.add(50, "Hello");
    std::cout << "Add (700, World)" << std::endl;
    myHashTable.add(700, "World");
    std::cout << "Add (85, Collision element 1)" << std::endl;
    myHashTable.add(85, "Collision element 1");
    std::cout << "Add (86, Collision element 2)" << std::endl;
    myHashTable.add(86, "Collision element 2");
  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico la Tabla Hash" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico la Tabla Hash" << std::endl;
  }
  std::cout << "Table current size: " << myHashTable.getNumElements() << std::endl;
  std::cout << "Table alfa: " << myHashTable.getAlfa() << std::endl;
  std::cout << "Table colisiones: " << myHashTable.getColisiones() << std::endl;
  myHashTable.print();
  std::cout << std::endl;

  std::cout << "Find 51: " << std::endl;
  int index = myHashTable.find(51);
  std::cout << "Result index: " << index << std::endl;
  if (index == -1)
    std::cout << "\tElement not found" << std::endl;
  else
    std::cout << "\tData: " << myHashTable.getDataAt(index) << std::endl;

  std::cout << "Find 50: " << std::endl;
  index = myHashTable.find(50);
  std::cout << "Result index: " << index << std::endl;
  if (index == -1)
    std::cout << "\tElement not found" << std::endl;
  else
    std::cout << "\tData: " << myHashTable.getDataAt(index) << std::endl;

  std::cout << "Find 86: " << std::endl;
  index = myHashTable.find(86);
  std::cout << "\tResult index: " << index << std::endl;
  if (index == -1)
    std::cout << "\tElement not found" << std::endl;
  else
    std::cout << "\tData: " << myHashTable.getDataAt(index) << std::endl;
  std::cout << std::endl;

  std::cout << "Remove 85: " << std::endl;
  myHashTable.remove(85);
  std::cout << "Table current size: " << myHashTable.getNumElements() << std::endl;
  myHashTable.print();
  std::cout << std::endl;

  try {
    std::cout << "Add (79, Collision element 3)" << std::endl;
    myHashTable.add(79, "Collision element 3");
    std::cout << "Table current size: " << myHashTable.getNumElements() << std::endl;
    myHashTable.print();
    std::cout << std::endl;

    std::cout << "Add (79, Prueba repetido)" << std::endl;
    myHashTable.add(79, "Prueba repetido");

  }
  catch (std::out_of_range &e) {
    std::cout << "Error: " << e.what() << std::endl << "No se modifico la Tabla Hash" << std::endl;
  }
  catch (...) {
    std::cout << "Error desconocido, no se modifico la Tabla Hash" << std::endl;
  }
  std::cout << "Table current size: " << myHashTable.getNumElements() << std::endl;
  std::cout << "Table alfa: " << myHashTable.getAlfa() << std::endl;
  std::cout << "Table colisiones: " << myHashTable.getColisiones() << std::endl;
  myHashTable.print();
  std::cout << std::endl;
  return 0;
}