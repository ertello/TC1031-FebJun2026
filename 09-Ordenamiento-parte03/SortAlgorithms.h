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

    void merge(std::vector<T> &A, size_t low, size_t m, size_t high, size_t &compara);
    int partition(std::vector<T> &A, int low, int high, size_t &compara, size_t &swap);

  public:
    SortAlgorithms();
    ~SortAlgorithms();
    void randomShuffle(std::vector<T> &A);
    void printVector(std::vector<T> A);
    
    void swapSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap);
    void selectionSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap);
    void bubbleSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap);
    void insertionSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap);
    void mergeSort(std::vector<T> &A, size_t low, size_t high, size_t &compara);
    void quickSort(std::vector<T> &A, int low, int high, size_t &compara, size_t &swap);

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

// O(n^2) en el peor caso
template<class T>
void SortAlgorithms<T>::insertionSort(std::vector<T> &A, size_t n, size_t &compara, size_t &swap) {
    compara = swap = 0;
    for (size_t i = 1; i < n; i++) {
        T key = A[i];
        size_t j = i;
        while (j > 0 && A[j-1] > key) {
            A[j] = A[j-1];
            j--;
            compara++;
            swap++;
        }
        A[j] = key;
    }
}

// O(n)
template<class T>
void SortAlgorithms<T>::merge(std::vector<T> &A, size_t low, size_t m, size_t high, size_t &compara) {
    size_t i, j, k;
    // calcular el tamaño de los vectores L y R
    size_t n1 = m - low + 1;
    size_t n2 = high - m;
    // Crear los vectores auxiliares L y R
    std::vector<T> L(n1); 
    std::vector<T> R(n2);
    for (i = 0; i < n1; i++) L[i] = A[low + i];
    for (j = 0; j < n2; j++) R[j] = A[m + 1 + j];
    // Fusionar los vectores L y R de forma ordenada
    i = j = 0;
    k = low;
    while (i < n1 && j < n2) {
        compara++;
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    // Copiar elementos restantes de L y R, si existen
    while (i < n1) { A[k] = L[i]; i++; k++; }
    while (j < n2) { A[k] = R[j]; j++; k++; }
}

// O(n log n) peor caso
template<class T>
void SortAlgorithms<T>::mergeSort(std::vector<T> &A, size_t low, size_t high, size_t &compara) {
    if (low < high) {
        // encontrar el punto medio
        size_t m = low + (high - low) / 2;
        // Divide el problema en dos partes
        mergeSort(A, low, m, compara);
        mergeSort(A, m+1, high, compara);
        // Fusionar ambas partes ordenadas
        merge(A, low, m, high, compara);
    }
}

// Algoritmo de Lomuto para particionar un vector en torno a un pivote
// O(n)
template<class T>
int SortAlgorithms<T>::partition(std::vector<T> &A, int low, int high, size_t &compara, size_t &swap) {
    T pivot = A[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        compara++;
        if (A[j] <= pivot) {
            i++;
            std::swap(A[i], A[j]);
            swap++;
        }
    }
    // posicion correcta del pivote es i+1
    std::swap(A[i+1], A[high]);
    swap++;
    return i + 1;
}

// O(n^2) peor caso, particiones desequilibradas
// O(n log n) caso promedio, particiones equilibradas
template<class T>
void SortAlgorithms<T>::quickSort(std::vector<T> &A, int low, int high, size_t &compara, size_t &swap) {
    if (low < high) {
        // encontrar la particion del vector
        int pi = partition(A, low, high, compara, swap);
        // ordenar recursivamente las particiones derecha e izquierda
        quickSort(A, low, pi-1, compara, swap); 
        quickSort(A, pi+1, high, compara, swap);
    }
}

#endif   // _SORT_ALGORITHMS_H_