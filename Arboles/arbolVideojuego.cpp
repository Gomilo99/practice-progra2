#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include "lib/arbol.hpp"
#include "lib/juego.hpp"
#include <queue>

template<>
void ArbolN<string>::insertarJuego(Juego juego){
    NodoN<string> *nuevo;
    if(this->esVacio()){
        nuevo = new NodoN<string>("Videojuegos");
        this->setRaiz(nuevo);
    }
    queue<NodoN<string>*> cola;
    cola.push(this->getNodoRaiz());
    string claves[4];
    claves[0] = juego.getGenero();

    // version para que quede Persona 5 Royal (2017)
    //claves[1] = to_string(juego.getFecha());
    //claves[2] = juego.getDesarrollador();
    //claves[3] = juego.getNombre();
    claves[1] = juego.getDesarrollador();
    claves[2] = juego.getNombre();
    //juego.imprimirJuego();
    string conFecha;
    NodoN<string> *p;
    NodoN<string> *anterior;
    NodoN<string> *hijo;
    bool encontrado;
    for(int nivel = 0; nivel < 3; nivel++){
        p = cola.front();
        cola.pop();
        hijo = p->getHijoIzq();
        anterior = NULL;
        encontrado = false;
        while(hijo != NULL){
            if(hijo->getInfo() == claves[nivel]){
                cola.push(hijo);
                encontrado = true;
                break;
            }
            anterior = hijo;
            hijo = hijo->getHnoDer();
            
        }
        if(!encontrado){
                if(nivel == 2){
                    conFecha = claves[nivel] + " (" + to_string(juego.getFecha()) + ")";
                    nuevo = new NodoN<string>(conFecha);
                }else{
                    nuevo = new NodoN<string>(claves[nivel]);
                }

                if(anterior == NULL){
                    p->setHijoIzq(nuevo);
                }else{
                    anterior->setHnoDer(nuevo);
                }
                cola.push(nuevo);
            }
    }
};
using namespace std;

int main(){
    Juego videojuego;
    ArbolN<string> arbol;
    while(videojuego.lecturaStandar()){
        arbol.insertarJuego(videojuego);
    
    }
    arbol.imprimirArbol();

    return 0;
}