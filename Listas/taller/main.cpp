#include <iostream>
#include "lib/lista.hpp"
#include "lib/pila.hpp"
#include "lib/cola.hpp"

using namespace std;
void anadir(Lista<Lista<int>> base, Lista<int> nuevalista);

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
    
    //inserta las listas aux a anidada
    for(int i = 0; i < 4; i++)
    {
        Lista<int> aux;

        aux.addToStart(i*i);
        aux.addToEnd(i + 4);
        anidada.addToEnd(aux);
    }
    
    cout << "ListaListas";
    
    Lista<int> aux;
    while(!anidada.isEmpty()){
        aux.copy(anidada.search(0));
        aux.printList();
        anidada.removeToStart();
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

void anadir(Lista<Lista<int>> base, Lista<int> nuevalista){
            Nodo<Lista<int>> *newNode = new Nodo<Lista<int>>(nuevalista);
            if (base.getLength() == 0) {
                base.setTail(newNode);
                base.setHead(newNode);
            }else{
                base.getTail()->setNext(newNode);
                base.setTail(newNode);
            }
            base.setLength(base.getLength() + 1);
        }