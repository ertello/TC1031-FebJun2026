/**
 * Ejemplo que implementa el factorial recursivo para un numero n
 * y la suma recursiva
 *
 * Compilacion para debug:
 *    g++ -std=c++17 -Wall -g -o main *.cpp
 * Compilacion para ejecucion:
 *    g++ -std=c++17 -Wall -O3 -o main *.cpp
 * Ejecucion:
 *    ./main
 **/
#include <iostream>

size_t factorialRecursivo(size_t n) {
  if (n == 0) // caso base
    return 1;
  else
    return factorialRecursivo(n-1) * n;
}

size_t factorialIterativo(size_t n) {
  size_t result = 1;
  while (n != 0) {
    result = result * n;
    n = n - 1;
  }
  return result;
}

size_t sumaIterativa(size_t n) {
  size_t suma = 0;
  for (size_t i = 1; i <= n; i++)
    suma += i;
  return suma;
}

size_t sumaRecursiva(size_t n) {
  if (n == 1) // caso base
    return 1;
  else
    return n + sumaRecursiva (n-1);
}


int main() {
  size_t value;
  std::cout << "Dame un numero positivo:" << std::endl;
  std::cin >> value;
  std::cout << "Su factorial recursivo es: " << factorialRecursivo(value) << std::endl;
  std::cout << "Su factorial iterativo es: " << factorialIterativo(value) << std::endl;
  std::cout << "Suma iterativa: " << sumaIterativa(value) << std::endl;
  std::cout << "Suma recursiva: " << sumaRecursiva(value) << std::endl;


  return 0;
}