#include <iostream>
#include "lib/lista.hpp"
#include "lib/pila.hpp"
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
    Lista< Lista<int> > anidada;

    for(int i = 0; i < 4; i++)
    {
        Lista<int> aux;
        aux.addToStart(i*i);
        anidada.addToStart(aux);
        aux.printList();
    }
    /*
    cout << "ListaListas";
    string elemento;
    Lista<string> prueba;
    int n = 0;
    while(n < 4){
        cin >> elemento;
        cout << elemento;
        prueba.addToEnd(elemento);
        n++;
    }
    prueba.printList();
    */
   /*
    while(!anidada.isEmpty()){
        anidada.getHead()->getInfo().printList();
        anidada.removeToStart();
    }
        */
    
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
