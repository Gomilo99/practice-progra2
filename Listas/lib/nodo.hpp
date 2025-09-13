#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <cstddef>
using namespace std;
template <typename Element>
class Nodo {
    private:
        Nodo<Element>* next;
        Element info;

    public:

    Nodo(): next(NULL), info(Element()) {} //Constructor por defecto
    Nodo(Element info): next(NULL), info(info) {} // Coloca puntero Null
    Nodo(Nodo<Element>* next, Element info) : //Construye Nodo full power
        next(next), info(info) {}

    
    //Getters
    Element getInfo() const { return this->info; }
    Nodo<Element>* getNext() const { return this->next; }

    //Setters
    void setInfo(Element info) { this->info = info; }
    void setNext(Nodo<Element>* next) { this->next = next; }
    
    bool isNullNode(Nodo<Element>* nodo) const {
            return nodo == NULL;
        }
    bool isNullNode(Nodo<Element>* first, Nodo<Element>* second){ 
        return this->isNullNode(first) || this->isNullNode(second);
    }
};

#endif