/** 
* Ejemplo que implementa dos representaciones de Grafos
* (Matriz de adyacencia y Lista de adyacencia)
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    valgrind --leak-check=full ./main < TestCases/graph01.txt
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main < TestCases/graph01.txt
**/

#include <iostream>
#include <sstream>
#include "Graph.h"

void test01() {
  std::cout << "Ejemplo 1 de grafos (representaciones)!" << std::endl;
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf(); 
  // Construye un grafo
  Graph<std::string> g1;
  // Lee de archivo un grafo representa=1, no-directed=0, no-weighted=0
  // lista de adyacencia
  g1.readGraph(inputInfo, 1, 0, 0);
  g1.print();
  std::cout << std::endl;
  g1.print(1);
  std::cout << std::endl;

  // Regresa a linea cero el archivo de entrada
  inputInfo.clear();
  inputInfo.seekg(0);
  // Lee de archivo un grafo representa=0, no-directed=0, no-weighted=0
  // matriz de adyacencia
  std::cout << "grafo 2"<< std::endl;
  Graph<std::string> g2;
  g2.readGraph(inputInfo, 0, 0, 0);
  g2.print();
  std::cout << std::endl;
  g2.print(1);
  std::cout << std::endl;
}

void test02() {
  std::cout << "Ejemplo 2 de grafos (representaciones)!" << std::endl;
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf(); 
  // Construye un grafo
  Graph<std::string> g1;
  // Lee de archivo un grafo representa=1, directed=1, weighted=1
  // lista de adyacencia
  g1.readGraph(inputInfo, 1, 1, 1);
  g1.print();
  std::cout << std::endl;
  g1.print(1);
  std::cout << std::endl;

  // Regresa a linea cero el archivo de entrada
  inputInfo.clear();
  inputInfo.seekg(0);
  // Lee de archivo un grafo representa=0, directed=1, weighted=1
  // matriz de adyacencia
  std::cout << "grafo 2"<< std::endl;
  Graph<std::string> g2;
  g2.readGraph(inputInfo, 0, 1, 1);
  g2.print();
  std::cout << std::endl;
  g2.print(1);
  std::cout << std::endl;
}

int main() {
  //test01(); // correr con graph01.txt
  test02(); // correr con graph02.txt o graph03.txt

  return 0;
}