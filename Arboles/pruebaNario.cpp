#include <iostream>
#include "lib/arbol.hpp"  // Tu archivo de clases
using namespace std;

int main() {

    // Crear nodos individuales
    NodoN<string>* nodoA = new NodoN<string>();
    nodoA->setInfo("A");

    NodoN<string>* nodoB = new NodoN<string>();
    nodoB->setInfo("B");

    NodoN<string>* nodoC = new NodoN<string>();
    nodoC->setInfo("C");

    NodoN<string>* nodoD = new NodoN<string>();
    nodoD->setInfo("D");

    NodoN<string>* nodoE = new NodoN<string>();
    nodoE->setInfo("E");


    // Armar jerarquía: A → B → C → D, B → E
    nodoA->setHijoIzq(nodoB);
    nodoB->setHnoDer(nodoC);
    nodoC->setHnoDer(nodoD);
    nodoB->setHijoIzq(nodoE);

    // Crear árbol original
    ArbolN<string> arbol(nodoA);

    cout << "🌳 Arbol original:\n";
    arbol.imprimirArbol();
    cout << arbol.getPeso() << endl;

    // Crear subárbol con F como raíz
    NodoN<string>* nodoRaizF = new NodoN<string>();
    nodoRaizF->setInfo("F");

    NodoN<string>* nodoG = new NodoN<string>();
    nodoG->setInfo("G");

    NodoN<string>* nodoH = new NodoN<string>();
    nodoH->setInfo("H");

    nodoRaizF->setHijoIzq(nodoG);
    nodoG->setHnoDer(nodoH);

    ArbolN<string> subarbolF(nodoRaizF);
    subarbolF.imprimirArbol();
    cout << subarbolF.getPeso() << endl;
    // Insertar subárbol F como hijo de nodo C (posición 2)
    arbol.insertarSubArbol(subarbolF);
    cout << arbol.getPeso() << endl;
    cout << "\n🌱 Arbol después de insertar subarbol F:\n";
    arbol.imprimirArbol();

    // Copiar el árbol
    ArbolN<string> copia(arbol);

    cout << "\n📋 Arbol copiado:\n";
    copia.imprimirArbol();

    // Eliminar nodo en posición 3 (D)
    arbol.eliminarSubArbol(3);

    cout << "\n🗑️ Arbol despues de eliminar posicion 3:\n";
    arbol.imprimirArbol();

    return 0;
}