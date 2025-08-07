#include <iostream>
#include <cstddef>
#include "lib/lista.hpp"
#include "lib/nodo.hpp"
// #include "lib/pila.hpp"
#include "lib/cola.hpp"

using namespace std;

int main(){
    Lista<int> listawapa;
    int sum=1;
    Nodo<string> kiko("\ngraciaaaas");
    listawapa.addToStart(sum);
    while(!listawapa.isEmpty() && sum <=10){
        listawapa.addToStart(sum);
        sum++;
    }
    listawapa.printList();

    cout << "anidada" << endl;
    Lista<Lista<int>> anidada;

    for(int i = 0; i < 4; i++)
    {
        Lista<int> aux;
        aux.addToStart(i*i);
        anidada.addToStart(aux);
        aux.printList();
    }


    
    cout << kiko.getInfo() << endl;

    Cola<int> colaClap;
    int bachaquera=1;
    while(bachaquera <= 10){
        colaClap.enqueue(bachaquera);
        bachaquera++;
    }
    colaClap.printQueue();

    return 0;
}
