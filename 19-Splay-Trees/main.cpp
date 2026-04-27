/** 
* Ejemplo que implementa un Splay Tree
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -Wall -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/
#include <iostream>
#include "SplayTree.h"
using std::cout;
using std::endl;

int main() {
    std::cout << "Prueba de un Splay Tree!";
    SplayTree<int> mySplayTree;
    cout << "Construimos el Splay Tree de la figura" << endl;
    mySplayTree.buildTestTree();
    /*
              100    
              /  \   
            50   200 
          /         
         40         
        /          
       30          
      /                                                          
     20 
    */
    mySplayTree.print();
    cout << "Recorrido preorder del Splay Tree" << endl;
    mySplayTree.preorder();
    // getSize
    cout << "getSize(): " << mySplayTree.getSize() << endl;
    cout << endl;
    // add
    cout << "add(25)" << endl;
    mySplayTree.add(25);
    cout << "Recorrido preorder del Splay Tree modificado" << endl;
    mySplayTree.preorder();
    mySplayTree.print();
    cout << "getSize(): " << mySplayTree.getSize() << endl;
    cout << endl;
    // find
    cout << "find(20)" << endl;
    mySplayTree.find(20);
    cout << "Recorrido preorder del Splay Tree modificado" << endl;
    mySplayTree.preorder();
    cout << "getSize(): " << mySplayTree.getSize() << endl;
    cout << endl;
    // remove 
    mySplayTree.print();
    cout << "remove(40)" << endl;
    mySplayTree.remove(40);
    cout << "Recorrido preorder del Splay Tree modificado" << endl;
    mySplayTree.preorder();
    cout << "getSize(): " << mySplayTree.getSize() << endl;
    mySplayTree.print();
    return 0;
}