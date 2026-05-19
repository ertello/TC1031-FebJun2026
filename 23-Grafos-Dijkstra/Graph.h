#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <queue>
#include "LinkedList.h"
#include "StackLL.h"

// https://stackoverflow.com/questions/18429021/why-is-infinity-0x3f3f3f3f
#define INF 0x3f3f3f3f

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
  void printAdjList(int flagInfo = 0);
  void printAdjMatrix(int flagInfo = 0);

public:
  Graph();
  ~Graph();
  void loadDirWeightedGraphList(std::istream &input);
  void loadDirWeightedGraphMatrix(std::istream &input);
  void print(int flagInfo = 0);
  void DFS(int v); // recibe un vertice cero basado
  std::pair<std::vector<int>, std::vector<int>> shortestPath(int v);

  // To-do act 4.2
  bool isBipartite();
  bool isDAG();
  
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
void Graph<T>::loadDirWeightedGraphList(std::istream &input) {
  std::string line;
  int i = 0;
  representation = 1; // Adjacency list
  directedGraph = 1; // Grafo dirigido
  weightedGraph = 1; // Grafo ponderado
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
    int weight = res[2];
    // Se agrega solo la arista (nodeU, nodeV), grafo dirigido
    adjList[nodeU].addLast(std::make_pair(nodeV, weight));
    i++;
  }
}

// O(n+m), n - numero de nodos, m - numero de aristas
template <class T> 
void Graph<T>::loadDirWeightedGraphMatrix(std::istream &input) {
  std::string line;
  int i = 0;
  representation = 0; // Adjacency matrix
  directedGraph = 1; // Grafo dirigido
  weightedGraph = 1; // Grafo ponderado
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
    int weight = res[2];
    // Se agrega solo la arista (nodeU, nodeV), grafo dirigido
    adjMatrix[nodeU][nodeV] = weight;
    i++;
  }
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

// O(n+m), n - numero de nodos, m - numero de aristas
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

// O(n+m) donde n=|V| y m=|E|
// recibe un vertice cero basado
template <class T> 
void Graph<T>::DFS(int v) {
  // Declaramos un stack
  StackLL<int> stack;
  // Declaramos un conjunto (set) del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Marcar como visitado el vertice de partida y meterlo en el stack
  stack.push(v);
  std::cout << "Recorrido DFS: " << std::endl;
  while (!stack.isEmpty()) {
    // Extraer un vertice del stack
    v = stack.peek();
    stack.pop();
    // Procesar el vertice si no ha sido visitado
    bool isVisited = visited.find(v) != visited.end();
    if (!isVisited) { // No ha sido visitado
      visited.insert(v);
      std::cout << v+1 << ", ";
    }
    //Obtener vecinos del vertice v
    // Si estos no han sido visitados marcarlos como visitados
    // y los metemos al stack
    if (representation == 1) { // Lista de adyacencia
      NodeLinkedList<std::pair<int, int>> *ptr = adjList[v].getHead();
      while (ptr != nullptr) {
        std::pair<int, int> par = ptr->data;
        int u = par.first;
        bool isVisited = visited.find(u) != visited.end();
        if (!isVisited) { // No ha sido visitado
          stack.push(u);
        }
        ptr = ptr->next;
      }
    }
    else { // Matriz de adyacencia
      for (int u = 0; u < numNodes; u++) {
        if (adjMatrix[v][u] > 0) {
          bool isVisited = visited.find(u) != visited.end();
          if (!isVisited) // No ha sido visitado
            stack.push(u);
        }
      }
    }
  }
  std::cout << std::endl;
}

// Algoritmo de Dijstra, complejidad O((n+m)*log n)
template <class T> std::pair<std::vector<int>, std::vector<int>> Graph<T>::shortestPath(int v) {
  // vector de distancias con el resultado del algoritmo
  std::vector<int> dist(numNodes, INF);
  // vector con los predecesores en el camino mas corto desde v
  std::vector<int> prev(numNodes, -1);
  // Crear una priority queue del STL
  // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
  // Insertar el nodo de origen v en la cola de prioridad -- pares <dist, nodo>
  pq.push(std::make_pair(0, v));
  dist[v] = 0;
  prev[v] = -1;
  // Mientras la cola de prioiridad no este vacia
  while (!pq.empty()) {
    // Extraer un nodo nodeU de la cola de prioridad
    int nodeU = pq.top().second; // pares <dist, nodo>
    pq.pop();
    // Obtener los nodos vecinos de nodeU
    if (representation == 1) { // Lista de adyacencia
      NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
      while (ptr != nullptr) {
        std::pair<int, int> par = ptr->data;
        int nodeV = par.first; // nodeV es vecino de nodeU
        int weight = par.second; // peso de la arista (nodeU, nodeV) 
        if (dist[nodeV] > dist[nodeU] + weight) {
          // Actualizar la distancia mas corta hasta nodeV
          dist[nodeV] = dist[nodeU] + weight;
          prev[nodeV] = nodeU;
          pq.push(std::make_pair(dist[nodeV], nodeV));
        }
        ptr = ptr->next;
      }
    }
    else { // Matriz de adyacencia
      for (int nodeV = 0; nodeV < numNodes; nodeV++) {
        int weight = adjMatrix[nodeU][nodeV]; // peso de la arista (nodeU, nodeV) 
        if (weight > 0) {
          if (dist[nodeV] > dist[nodeU] + weight) {
            // Actualizar la distancia mas corta hasta nodeV
            dist[nodeV] = dist[nodeU] + weight;
            prev[nodeV] = nodeU;
            pq.push(std::make_pair(dist[nodeV], nodeV));
          }
        }
      }
    }
  }
  // El resultado almacenado en dist y prev 
  std::cout << "Vertices \t\t Distancia desde v" << std::endl;
  for (int i = 0; i < numNodes; i++) {
    if (dist[i] == INF)
      std::cout << i+1 << "\t\tINF" << std::endl;
    else
      std::cout << i+1 << "\t\t" << dist[i] << std::endl;
  }
  std::cout << "Vertices \t\t Predecesor" << std::endl;
  for (int i = 0; i < numNodes; i++) {
    if (prev[i] == -1)
      std::cout << i+1 << "\t\tNULL" << std::endl;
    else
      std::cout << i+1 << "\t\t" << prev[i]+1 << std::endl;
  }
  return std::make_pair(dist, prev);
}


#endif // _GRAPH_H_
