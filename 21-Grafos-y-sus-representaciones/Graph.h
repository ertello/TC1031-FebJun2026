#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "LinkedList.h"

template <class T> 
class Graph {
private:
  int numNodes;
  int numEdges;
  int representation; // 1: Adjacency list;  0: Adjacency matrix
  int directedGraph;  // 1 dirigido; 0 no-dirigido
  int weightedGraph;  // 1 ponderado; 0 no-ponderado
  // Cada nodo tiene un id y un objeto de datos tipo T
  std::map<int, T> nodesInfo;
  // Lista de adyacencia (vector de listas de pares <nodo,peso>)
  std::vector<LinkedList<std::pair<int, int>>> adjList;
  // Matriz de adyacencia (vector de vectores)
  std::vector<std::vector<int>> adjMatrix;

  void split(std::string line, std::vector<int> &res);
  void loadGraphList(std::istream &input);
  void loadGraphMatrix(std::istream &input);
  void printAdjList(int flagInfo = 0);
  void printAdjMatrix(int flagInfo = 0);

public:
  Graph();
  ~Graph();
  void readGraph(std::istream &input, int _representation, int _directed, int _weighted);
  void print(int flagInfo = 0);
};

// O(1)
template <class T> 
Graph<T>::Graph() {
  numNodes = 0;
  numEdges = 0;
  representation = 1;
  directedGraph = 1;
  weightedGraph = 1;
}

// O(1)
template <class T> 
Graph<T>::~Graph() {
  if (representation == 0)
    adjMatrix.clear();
  if (representation == 1)
    adjList.clear();
  numNodes = 0;
  numEdges = 0;
  representation = 1;
  directedGraph = 1;
  weightedGraph = 1;
}
// O(k), k - numero de elementos en la linea
template <class T>
void Graph<T>::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

// O(n+m), n - numero de nodos, m - numero de aristas
template <class T> 
void Graph<T>::loadGraphList(std::istream &input) {
  std::string line;
  int i = 0;
  while (std::getline(input, line)) {
    if (i == 0) { // Ignorar primera linea de texto (comentario)
      i++;
      continue;
    }
    if (i == 1) { // Leemos numNodes y numEdges
      std::vector<int> res;
      split(line, res);
      numNodes = res[0];
      numEdges = res[1];
      // Reservar memoria para los numNodes renglones (cero basado) y 
      // listas vacias de pares (nodo, peso) 
      adjList.resize(numNodes, LinkedList<std::pair<int, int>>());
      i++;
      continue;
    }
    if (i > 1 && i < numNodes + 2) { // Para cada nodo se lee su informacion
      T data = line; // ATENCION: convertir al tipo de dato adecuado
      // map <key, data> con los nodos indexados cero basados
      nodesInfo.insert(std::make_pair(i - 2, data));
      i++;
      continue;
    }
    // Lee las aristas
    std::vector<int> res;
    split(line, res);
    // nodos cero basados
    int nodeU = res[0] - 1;
    int nodeV = res[1] - 1;
    // Si el grafo es ponderado se lee tambien el peso
    // grafo no ponderado entonces aristas con peso 1
    int weight = (weightedGraph == 1) ? res[2] : 1;
    // Siempre se agrega la arista (nodeU, nodeV)
    adjList[nodeU].addLast(std::make_pair(nodeV, weight));
    // Si el grafo es no dirigido agrega tambien la arista (nodeV, nodeU)
    if (directedGraph == 0)
      adjList[nodeV].addLast(std::make_pair(nodeU, weight));
    i++;
  }
}

// O(n+m), n - numero de nodos, m - numero de aristas
template <class T> 
void Graph<T>::loadGraphMatrix(std::istream &input) {
  std::string line;
  int i = 0;
  while (std::getline(input, line)) {
    if (i == 0) { // Ignorar primera linea de texto (comentario)
      i++;
      continue;
    }
    if (i == 1) { // Leemos numNodes y numEdges
      std::vector<int> res;
      split(line, res);
      numNodes = res[0];
      numEdges = res[1];
      // Reservar memoria para los numNodes renglones (cero basado) y 
      // numNode columnas (matriz de adyacencia) con ceros 
      adjMatrix.resize(numNodes, std::vector<int>(numNodes, 0));
      i++;
      continue;
    }
    if (i > 1 && i < numNodes + 2) { // Para cada nodo se lee su informacion
      T data = line; // ATENCION: convertir al tipo de dato adecuado
      // map <key, data> con los nodos indexados cero basados
      nodesInfo.insert(std::make_pair(i - 2, data));
      i++;
      continue;
    }
    // Lee las aristas
    std::vector<int> res;
    split(line, res);
    // nodos cero basados
    int nodeU = res[0] - 1;
    int nodeV = res[1] - 1;
    // Si el grafo es ponderado se lee tambien el peso
    // grafo no ponderado entonces aristas con peso 1
    int weight = (weightedGraph == 1) ? res[2] : 1;
    // Siempre se agrega la arista (nodeU, nodeV)
    adjMatrix[nodeU][nodeV] = weight;
    // Si el grafo es no dirigido agrega tambien la arista (nodeV, nodeU)
    if (directedGraph == 0)
      adjMatrix[nodeV][nodeU] = weight;
    i++;
  }
}

// O(n+m), n - numero de nodos, m - numero de aristas
template <class T>
void Graph<T>::readGraph(std::istream &input, int _representation, int _directed, int _weighted) {
  representation = _representation;
  directedGraph = _directed;
  weightedGraph = _weighted;
  // Matriz de adyacencia
  if (representation == 0)
    loadGraphMatrix(input);
  else // Lista de adyacencia
    loadGraphList(input);
}

// O(nm), n - numero de nodos, m - numero de aristas
template <class T> 
void Graph<T>::printAdjMatrix(int flagInfo) {
  std::cout << "numNodes: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency Matrix" << std::endl;
  for (int nodeU = 0; nodeU < numNodes; nodeU++) {
    if (flagInfo) // Si se imprime la info del nodo
      std::cout << "vertex " << nodeU + 1 << " (" << nodesInfo[nodeU] << "): ";
    else // solo se imprime el numero de nodo
      std::cout << "vertex " << nodeU + 1 << ": ";
    for (int nodeV = 0; nodeV < numNodes; nodeV++) {
      if (flagInfo) { // Si se imprime la info del nodo
        if (adjMatrix[nodeU][nodeV] > 0)
          std::cout << nodesInfo[nodeV] << " ";
        else
          std::cout << 0 << " ";
      } else
        std::cout << " " << adjMatrix[nodeU][nodeV];
    }
    std::cout << std::endl;
  }
}

// O(nm), n - numero de nodos, m - numero de aristas
template <class T> 
void Graph<T>::printAdjList(int flagInfo) {
  std::cout << "numNodes: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 0; nodeU < numNodes; nodeU++) {
    if (flagInfo) // Se imprime la info del nodo
      std::cout << "vertex " << nodesInfo[nodeU] << ": ";
    else // Se imprime el numero de nodo
      std::cout << "vertex " << nodeU + 1 << ": ";
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int nodeV = par.first;
      int weight = par.second;
      std::string nodeData = (flagInfo) ? nodesInfo[nodeV] + ", " : "";
      if (weightedGraph == 1) // grafo ponderado
        std::cout << "{" << nodeData << nodeV + 1 << ", " << weight << "} ";
      else
        std::cout << "{" << nodeData << nodeV + 1 << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

template <class T> void Graph<T>::print(int flagInfo) {
  if (representation == 1)
    printAdjList(flagInfo);
  else
    printAdjMatrix(flagInfo);
}

#endif // _GRAPH_H_
