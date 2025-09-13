#include <iostream>
#include "lib/arbol.hpp" // Incluye tu clase ArbolBin y NodoBin
using namespace std;

template<typename T>
void mostrarLista(const list<T>& lst, const string& nombre) {
    cout << nombre << ": ";
    for (auto& e : lst) cout << e << " ";
    cout << "\n";
}

int main() {
    // 1️⃣ Crear nodos manualmente
    NodoBin<string>* nodoA = new NodoBin<string>("A");
    NodoBin<string>* nodoB = new NodoBin<string>("B");
    NodoBin<string>* nodoC = new NodoBin<string>("C");
    NodoBin<string>* nodoD = new NodoBin<string>("D");
    NodoBin<string>* nodoE = new NodoBin<string>("E");

    // 2️⃣ Armar árbol base
    nodoA->setHijoIzq(nodoB);
    nodoA->setHijoDer(nodoC);
    nodoB->setHijoIzq(nodoD);
    nodoB->setHijoDer(nodoE);

    ArbolBin<string> arbol(nodoA);

    cout << "Arbol inicial:\n";
    arbol.imprimirArbol();
    cout << "Peso: " << arbol.getPeso() << "\n\n";

    // 3️⃣ Recorridos
    mostrarLista(arbol.preOrden(), "PreOrden");
    mostrarLista(arbol.inOrden(), "InOrden");
    mostrarLista(arbol.postOrden(), "PostOrden");
    mostrarLista(arbol.porNiveles(), "PorNiveles");
    cout << "\n \U0001F680 \n";

    // 4️⃣ Crear subárbol izquierdo
    NodoBin<string>* nodoX = new NodoBin<string>("X");
    NodoBin<string>* nodoY = new NodoBin<string>("Y");
    nodoX->setHijoIzq(nodoY);
    ArbolBin<string> subIzq(nodoX);

    arbol.insertarSubArbolIzq(subIzq);
    cout << "Despues de insertar subarbol a la izquierda:\n";
    arbol.imprimirArbol();
    cout << "Peso: " << arbol.getPeso() << "\n\n";

    // 5️⃣ Crear subárbol derecho
    NodoBin<string>* nodoM = new NodoBin<string>("M");
    NodoBin<string>* nodoN = new NodoBin<string>("N");
    nodoM->setHijoDer(nodoN);
    ArbolBin<string> subDer(nodoM);

    arbol.insertarSubArbolDer(subDer);
    cout << "Despues de insertar subarbol a la derecha:\n";
    arbol.imprimirArbol();
    cout << "Peso: " << arbol.getPeso() << "\n\n";

    // 6️⃣ Copia profunda
    ArbolBin<string> copia(arbol);
    cout << "Copia del árbol:\n";
    copia.imprimirArbol();
    cout << "Peso copia: " << copia.getPeso() << "\n\n";

    // 7️⃣ Eliminar subárbol izquierdo
    arbol.eliminarSubArbolIzq();
    cout << "Despues de eliminar subarbol izquierdo:\n";
    arbol.imprimirArbol();
    cout << "Peso: " << arbol.getPeso() << "\n\n";

    // 8️⃣ Eliminar subárbol derecho
    arbol.eliminarSubArbolDer();
    cout << "Despues de eliminar subarbol derecho:\n";
    arbol.imprimirArbol();
    cout << "Peso: " << arbol.getPeso() << "\n\n";

    return 0;
}