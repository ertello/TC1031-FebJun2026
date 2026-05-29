
#ifndef __DISJOINT_SET_H_
#define __DISJOINT_SET_H_

  #include <iostream>
  #include <vector>
  #include <unordered_map>
  #include <map>
  

  template<class T>
  class DisjointSet {
    private:
      // universo de elementos
      std::vector<T> universe;
      // padre de cada elemento
      std::unordered_map<int, T> parent;
      // altura de cada arbol
      std::unordered_map<int, int> rank;
      // indices de cada objeto del universo
      std::map<T, int> index;
      // maximo numero de elementos en el universo
      int maxSize;
    
    public:
      DisjointSet();
      DisjointSet(std::vector<T> &objs);
      ~DisjointSet();
      T find(T element);
      void printSubsets();
      void unionSets(T rootX, T rootY);

  };
  
  template<class T>
  DisjointSet<T>::DisjointSet() {
      maxSize = 0;  
  }

  template<class T>
  DisjointSet<T>::DisjointSet(std::vector<T> &objs) {
      universe = std::vector<T> (objs.begin(), objs.end());
      int j = 0;
      typename std::vector<T>::iterator it;
      for(it = objs.begin(); it != objs.end(); it++) {
        index.insert({*it, j});
        parent[j] = *it; 
        rank[j] = 0;
        j++;
      }
      maxSize = objs.size();
  }

  template<class T>
  DisjointSet<T>::~DisjointSet() {
      index.clear();
      parent.clear();
      rank.clear();
      maxSize = 0; 
  }
  
  template<class T>
  T DisjointSet<T>::find(T element) {
      // Si element no es la raiz de su arbol
      if (parent[index[element]] != element) {
        // path compression
        parent[index[element]] = find(parent[index[element]]);
      }
      return parent[index[element]];
  }

  template<class T>
  void DisjointSet<T>::printSubsets() {
      std::cout << "Subsets: " << std::endl;
      typename std::vector<T>::iterator it;
      for(it=universe.begin(); it != universe.end(); it++) {
          std::cout <<"Element: " << *it << " parent: " << find(*it) << " rank: " << rank[index[*it]] << std::endl;
      }
  }

  template<class T>
  void DisjointSet<T>::unionSets(T a, T b) {
    // localiza la raiz de los conjuntos a los que pertenecen los elementos a y b
    T x = find(a);
    T y = find(b);
    // si a y b pertenecen al mismo conjunto 
    if (x == y) {
      return;
    }
    // El arbol con menos niveles se agrega al de mayor profundidad (union by rank).
    if (rank[index[x]] > rank[index[y]]) {
      parent[index[y]] = x;
    }
    else if (rank[index[x]] < rank[index[y]]) {
      parent[index[x]] = y;
    }
    else {
      parent[index[x]] = y;
      rank[index[y]]++;
    }
  }

 
#endif // __DISJOINT_SET_H_ 