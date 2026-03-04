#ifndef _SORT_ALGORITHMS_H_
#define _SORT_ALGORITHMS_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

template <class T>
class SortAlgorithms {
  private:
    // semilla del generador de numeros aleatorios (time-based)
    unsigned seed; 
    // generador de numeros aleatorios (Mersenne Twister 64 bits)
    std::mt19937_64 gen;

  public:
    SortAlgorithms();
    ~SortAlgorithms();
    void randomShuffle(std::vector<T> &A);
    void printVector(std::vector<T> A);
    
    void swapSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap);
    void selectionSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap);
    void bubbleSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap);
    
};

// O(1)
template<class T>
SortAlgorithms<T>::SortAlgorithms() {
    // semilla del generador de numeros aleatorios (time-based)
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    // generador de numeros aleatorios (Mersenne Twister 64 bits)
    std::mt19937_64 gen;
    // inicializar el generador con la semilla creada
    gen.seed(seed);
}

template<class T>
SortAlgorithms<T>::~SortAlgorithms() {}

// Mezcla los elementos del vector en forma aleatoria
// O(n)
template<class T>
void SortAlgorithms<T>::randomShuffle(std::vector<T> &A) {
    std::shuffle(A.begin(), A.end(), gen);
}

// Imprime en pantalla los elementos del vector
// O(n)
template<class T>
void SortAlgorithms<T>::printVector(std::vector<T> A) {
    std::cout << "Los elementos del vector ordenado son: " << std::endl;
    for(size_t i = 0; i < A.size(); i++) {
      std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

// O(n^2) en el peor caso
template<class T>
void SortAlgorithms<T>::swapSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap) {
    compara = swap = 0;
    for (size_t i = 0; i < n-1; i++) {
        for (size_t j = i + 1; j < n; j++) {
            compara++;
            if (A[i] > A[j]) {
                std::swap(A[i], A[j]);
                swap++;
            }
        }
    }
}

// O(n^2) en el peor caso
template<class T>
void SortAlgorithms<T>::selectionSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap) {
    compara = swap = 0;
    for (size_t i = 0; i < n-1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < n; j++) {
            compara++;
            if (A[j] < A[minIndex])
                minIndex = j;
        }
        std::swap(A[i], A[minIndex]);
        swap++;
    }
}

// O(n^2) en el peor caso
template<class T>
void SortAlgorithms<T>::bubbleSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap) {
    compara = swap = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n-i-1; j++) {
            compara++;
            if (A[j] > A[j+1]) {
                std::swap(A[j], A[j+1]);
                swap++;
            }
        }
    }
}


#endif   // _SORT_ALGORITHMS_H_