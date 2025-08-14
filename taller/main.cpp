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
        anadir(anidada, aux);
    }
    
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
    
    while(!anidada.isEmpty()){
        anidada.search(0).printList();

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