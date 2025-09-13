#include <iostream>
#include <string>
#include <cstring>
#include "librerias/cola.hpp"
#include "librerias/pila.hpp"
#include "librerias/listaCircular.hpp"
void leerEntradaInvitados(ListaCircular<string> *invitados);
using namespace std;

int main(){
    int kBrindis, pBrindis, qBrindis, casos;
    ListaCircular<string> circulo;
    int i=0;
    string nombre;
    cin >> casos;

    while(i < casos){
        //lee entrada estandar
        cin >> kBrindis >> pBrindis >> qBrindis;
        //cout << "\n" << casos << " brindis " << kBrindis << " " << pBrindis << " " << qBrindis;
        leerEntradaInvitados(&circulo);
        ListaCircular<string> copia(circulo);

        //hace la ruleta ceremonial
        while(circulo.getLongitud() > 1){
            //circulo.imprimirLista();
            nombre = circulo.consultar(kBrindis-1);
            //cout << nombre << endl;
            circulo.eliminarPorPosicion(kBrindis-1);
            circulo.rightShift(kBrindis);
            //cout << copia.buscar(nombre) << endl;
            if((copia.buscar(nombre)+1) % 2 == 0){
                    kBrindis = pBrindis;
                }else{
                    kBrindis = qBrindis;
                }
            //cout << kBrindis;
            //circulo.imprimirLista();
            
            circulo.invertir();
            //circulo.imprimirLista();
        }
        cout << circulo.consultar(0) << endl;
        circulo.liberarLista();
        i++;
    }
    return 0;
}

//funcion para leer entrada estandar
void leerEntradaInvitados(ListaCircular<string> *invitados){
    string lord;
    char comilla;

    cin.get(comilla); // Consume the newline character after qBrindis
        if (comilla == '\n')
            cin.get(comilla);
        while(comilla == '"'){
            getline(cin, lord, '"');
            cin.get(comilla); // Read the comma or newline after the name
            if (comilla == ',') {
                cin.get(comilla); // Read the space after the comma
            }
            //cout << lord << " - ";
            invitados->insertarEnPosicion(lord, invitados->getLongitud());
            if(comilla == '\n') break;
            cin >> comilla;
        }
}