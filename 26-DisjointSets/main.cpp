/** 
* Ejemplo que implementa Disjoint sets
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
#include <vector>
#include "DisjointSet.h"

void test01() {
  std::cout << "Ejemplo 1 Disjoint sets!\n";
  // universo de elementos
  std::vector<double> elements = {1000.2345, 0.67, 1.45, 3.46, 65.34, 100.98};
  DisjointSet<double> ds(elements);
  ds.printSubsets();
  std::cout << "Union 1000.2345 y 3.46" << std::endl;
  ds.unionSets(1000.2345, 3.46);
  ds.printSubsets();
  std::cout << std::endl;
  ds.unionSets(1000.2345, 1.45);
  ds.printSubsets();
  std::cout << std::endl;
}


void test02() {
  std::cout << "Ejemplo 2 Disjoint sets!\n";
  // universo de elementos 
  std::vector<std::string> elements = {"cero", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete"};
  DisjointSet<std::string> ds(elements);
  ds.printSubsets();
  std::cout << "Union cuatro y tres" << std::endl;
  ds.unionSets("cuatro", "tres");
  ds.printSubsets();
  std::cout << "Union dos y uno" << std::endl;
  ds.unionSets("dos", "uno");
  ds.printSubsets();
  std::cout << "Union uno y tres" << std::endl;
  ds.unionSets("uno", "tres");
  ds.printSubsets();
  std::cout << std::endl;

  std::cout << "find(dos) " << ds.find("dos") << std::endl;
  
}


int main() {
  //test01();
  test02();
  return 0;
}