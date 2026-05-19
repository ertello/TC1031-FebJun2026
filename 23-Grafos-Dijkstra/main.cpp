/** 
* Ejemplo que implementa dos representaciones de Grafos
* (Matriz de adyacencia y Lista de adyacencia) y el algortimo
* de Dijkstra
*
* Compilacion para debug:  
*    g++ -std=c++17 -Wall -g -o main *.cpp 
* Ejecucion con valgrind:
*    valgrind --leak-check=full ./main < TestCases/graph01.txt
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -Wall -O3 -o main *.cpp 
* Ejecucion:
*    ./main < TestCases/graph01.txt
**/

#include <iostream>
#include <sstream>
#include "Graph.h"


int main() {
  std::cout << "Ejemplo 1 grafo dirigido y ponderado (lista de adyacencia)!" << std::endl;
  std::stringstream inputInfo;
  inputInfo << std::cin.rdbuf(); 
  // Construye un grafo
  std::cout << "grafo 1"<< std::endl;
  Graph<std::string> g1;
  // lista de adyacencia
  g1.loadDirWeightedGraphList(inputInfo);
  g1.print();
  std::cout << std::endl;
  g1.shortestPath(0);
  std::cout << std::endl;

  // Regresa a linea cero el archivo de entrada
  inputInfo.clear();
  inputInfo.seekg(0);
  // Construye un grafo
  std::cout << "grafo 2"<< std::endl;
  Graph<std::string> g2;
  g2.loadDirWeightedGraphMatrix(inputInfo);
  g2.print();
  std::cout << std::endl;
  g2.shortestPath(0);
  std::cout << std::endl;

  return 0;
}