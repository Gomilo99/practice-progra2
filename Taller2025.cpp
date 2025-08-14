#include "lib/lista.hpp"
#include "lib/pila.hpp"
#include "lib/cola.hpp"
#include <iostream>

using namespace std;

int main(){
    int i, k, totalCasos;
    string palabra;
    Lista<int> pasosCirculo;
    Lista<Lista<string>> caso;
    Lista<string> circulo;
    cin >> totalCasos;
    while(i < totalCasos){
        cin >> k;
        pasosCirculo.addToEnd(k);
        i++;
    }
    while(!pasosCirculo.isEmpty()){
        circulo.addToEnd(palabra);
        caso.addToEnd(circulo);
        pasosCirculo.removeToStart();
    }
    while(!caso.isEmpty()){
        caso.getHead()->getInfo().printList();
        caso.removeToStart();
    }
    return 0;
}

