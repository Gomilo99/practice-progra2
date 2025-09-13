#ifndef NODOS_H

#include <iostream>
#include <cstddef>
#define NODON_H
using namespace std;
template <typename Element>
class NodoN {
    private:
        NodoN<Element> *hijoIzq;
        NodoN<Element> *hnoDer;
        Element info;
    public:
        NodoN() : hijoIzq(NULL), hnoDer(NULL), info(Element()) {}
        NodoN(NodoN<Element> *hijoIzq, NodoN<Element> *hnoDer, Element info) : hijoIzq(hijoIzq), hnoDer(hnoDer), info(info) {}
        NodoN(Element e) : hijoIzq(NULL), hnoDer(NULL), info(e) {}
        //NodoN(NodoN<Element> *hijoIzq, Element info) : hijoIzq(hijoIzq), hnoDer(NULL), info(info) {}
        //NodoN(NodoN<Element> *hnoDer, Element info) : hijoIzq(NULL), hnoDer(hnoDer), info(info) {}

        NodoN<Element>* getHijoIzq() { return this->hijoIzq; }
        NodoN<Element>* getHnoDer() { return this->hnoDer; }
        Element getInfo() { return this->info; }

        void setHijoIzq(NodoN<Element> *nuevoNodo) { this->hijoIzq = nuevoNodo; }
        void setHnoDer(NodoN<Element> *nuevoNodo) { this->hnoDer = nuevoNodo; }
        void setInfo(Element nuevoInfo) { this->info = nuevoInfo; }
};

#define NODOBIN_H
template <typename Element>
class NodoBin {
private:
    NodoBin<Element>* hijoIzq;
    NodoBin<Element>* hijoDer;
    Element info;

public:
    // Constructor por defecto
    NodoBin() : hijoIzq(NULL), hijoDer(NULL), info(Element()) {}

    // Constructor con valor
    NodoBin(const Element& e) : hijoIzq(NULL), hijoDer(NULL), info(e) {}

    // Constructor con hijos e info
    NodoBin(NodoBin<Element>* izq, NodoBin<Element>* der, const Element& e)
        : hijoIzq(izq), hijoDer(der), info(e) {}

    // Getters
    NodoBin<Element>* getHijoIzq() { return hijoIzq; }
    NodoBin<Element>* getHijoDer() { return hijoDer; }
    Element getInfo() const { return info; }

    // Setters
    void setHijoIzq(NodoBin<Element> *nuevoNodo) { hijoIzq = nuevoNodo; }
    void setHijoDer(NodoBin<Element> *nuevoNodo) { hijoDer = nuevoNodo; }
    void setInfo(const Element& nuevoInfo) { info = nuevoInfo; }
};

#endif