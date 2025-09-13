#ifndef ARBOL_H
#include "nodo.hpp"
#include <list>
#include <queue>
#include <stack>
#include "juego.hpp"

#define ARBOLN_H
class Estudiante{
    private:
    int eficienLocal;
    int valor;
    public:
    Estudiante() : eficienLocal(0), valor(0) {}
    Estudiante(int valor) : eficienLocal(0), valor(valor) {}
    Estudiante(int valor, int efi) : eficienLocal(efi), valor(valor) {}
    // Getters y Setters
    int getEficienLocal() const { return eficienLocal; }
    int getValor() const { return valor; }

    void setEficienLocal(int el) { eficienLocal = el; }
    void setValor(int v) { valor = v; }
    void imprimirEstudiante(){
        cout << this->valor << " efi(" <<this->eficienLocal << ")" << endl;
    }
};
template<typename Element>
class ArbolN{
    private:
        NodoN<Element> *raiz;
        int peso;

        NodoN<Element>* copiarNodo(NodoN<Element>* nodo) {
            if (nodo == NULL) return NULL;
            NodoN<Element>* nuevo = new NodoN<Element>();
            nuevo->setInfo(nodo->getInfo());
            nuevo->setHijoIzq(copiarNodo(nodo->getHijoIzq()));
            nuevo->setHnoDer(copiarNodo(nodo->getHnoDer()));
            return nuevo;
        }

        void destruir(NodoN<Element> *nodo){
            if(nodo == NULL) return;
            destruir(nodo->getHijoIzq()); // Elimina hijos
            destruir(nodo->getHnoDer()); // Elimina hermanos
            delete nodo;
            this->peso--;
        }
        void eliminarRecursivoPorPosicion(NodoN<Element> *padre, NodoN<Element> *actual, int &pos, int objetivo) {
            if (actual == NULL) return;
            NodoN<Element> *hijo;
            if (pos == objetivo) {
                if (padre != NULL) {
                    // Eliminar desde hijos
                    hijo = padre->getHijoIzq();
                    if (hijo == actual) {
                        padre->setHijoIzq(actual->getHnoDer()); // Si es primer hijo
                    } else {
                        // Si es otro hermano
                        while (hijo != NULL && hijo->getHnoDer() != actual) {
                            hijo = hijo->getHnoDer();
                        }
                        if (hijo != NULL) {
                            hijo->setHnoDer(actual->getHnoDer());
                        }
                    }
                }
                destruir(actual);
                return;
            }
            // Recorrer hijos
            pos++;
            hijo = actual->getHijoIzq();
            while (hijo != NULL) {
                eliminarRecursivo(actual, hijo, pos, objetivo);
                hijo = hijo->getHnoDer();
            }
        }

        // Metodos Privados de los Recorridos
        void preOrden(NodoN<Element> *p, list<Element> *result){
            NodoN<Element> *hijo;
            if(p != NULL){
                result->push_back(p->getInfo());
                hijo = p->getHijoIzq();
                while(hijo != NULL){
                    this->preOrden(hijo, result);
                    hijo = hijo->getHnoDer();
                }
            }
        }
        void postOrden(NodoN<Element> *p, list<Element> *result){
            NodoN<Element> *hijo;
            if(p != NULL){
                hijo = p->getHijoIzq();
                while(hijo != NULL){
                    this->postOrden(hijo, result);
                    hijo = hijo->getHnoDer();
                }
                result->push_back(p->getInfo());
            }
        }
        void inOrden(NodoN<Element> *p, list<Element> *result){
            NodoN<Element> *hijo;
            if(p != NULL){
                hijo = p->getHijoIzq();
                this->inOrden(hijo, result);
                result->push_back(p->getInfo());
                while(hijo != NULL){
                    hijo = hijo->getHnoDer();
                    this->inOrden(hijo, result);
                }
                
            }
        }
        void imprimirDesde(NodoN<Element>* nodo, string prefijo, bool esUltimo) {
            if (nodo == NULL) return;

            cout << prefijo;
            cout << (esUltimo ? "+-- " : "|-- ");
            cout << nodo->getInfo() << endl;

            string nuevoPrefijo = prefijo + (esUltimo ? "    " : "|   ");

            NodoN<Element>* hijo = nodo->getHijoIzq();
            while (hijo != NULL) {
                bool esHermanoUltimo = (hijo->getHnoDer() == NULL);
                imprimirDesde(hijo, nuevoPrefijo, esHermanoUltimo);
                hijo = hijo->getHnoDer();
            }
        }

        int contarNodos(NodoN<Element>* nodo) {
            if (nodo == NULL) return 0;

            int total = 1; // contar el nodo actual

            NodoN<Element>* hijo = nodo->getHijoIzq();
            while (hijo != NULL) {
                total += contarNodos(hijo);
                hijo = hijo->getHnoDer();
            }

            return total;
        }
        void imprimirDesdeEstudiante(NodoN<Estudiante>* nodo, string prefijo, bool esUltimo) {
            if (nodo == NULL) return;
            cout << prefijo;
            cout << (esUltimo ? "+-- " : "|-- ");
            Estudiante estu = nodo->getInfo();
            cout << estu.getValor() << "(" << estu.getEficienLocal() << ")" << endl;
            string nuevoPrefijo = prefijo + (esUltimo ? "    " : "|   ");

            NodoN<Estudiante>* hijo = nodo->getHijoIzq();
            while (hijo != NULL) {
                bool esHermanoUltimo = (hijo->getHnoDer() == NULL);
                imprimirDesdeEstudiante(hijo, nuevoPrefijo, esHermanoUltimo);
                hijo = hijo->getHnoDer();
            }
        };  
        void maxSumaIndependiente(NodoN<Estudiante> *p, int *sumIncluido, int *sumExcluido){
            if(p == NULL){
                sumIncluido = 0;
                sumExcluido = 0;
                return;
            }
            Estudiante eAuxiliar = p->getInfo();
            *sumIncluido = eAuxiliar.getEficienLocal();
            sumExcluido = 0;
            NodoN<Estudiante> *hijo = p->getHijoIzq();
            while(hijo != NULL){
                int i, e;
                maxSumaIndependiente(hijo, &i, &e);
                sumIncluido += i;
                sumExcluido += (i > e) ? i : e;
                hijo = hijo->getHnoDer();
            }
        }
    public:
        ArbolN() : raiz(NULL), peso(0){}
        ArbolN(Element e){
            this->raiz = new NodoN<Element>(e);
            this->peso++;
        }
        ArbolN(NodoN<Element> *nuevaRaiz) {
            this->raiz = nuevaRaiz;
            this->peso = contarNodos(nuevaRaiz); // opcional: calcular el peso real
        }

        ArbolN(const Element e, list<NodoN<Element>> listaNodos){
            this->raiz = new NodoN<Element>(e);
            this->raiz->setHijoIzq(listaNodos.front());
            NodoN<Element> *p = this->raiz->getHijoIzq();
            listaNodos.erase(0);
            while(!listaNodos.empty()){
                p->setHnoDer(listaNodos.front());
                p = p->getHnoDer();
                listaNodos.pop_front();
            }
        }
        ArbolN(list<Element> listaElements){
            if(listaElements.empty()){
                this->raiz = NULL;
                return;
            }
            this->raiz = new NodoN<Element>(listaElements.front());
            listaElements.pop_front();
            if(listaElements.empty()) return;

            NodoN<Element> *nodo = new NodoN<Element>(listaElements.front());
            this->raiz->setHijoIzq(nodo);
            listaElements.pop_front();
            NodoN<Element> *actual = nodo;
            while(!listaElements.empty()){
                nodo = new NodoN<Element>(listaElements.front());
                listaElements.pop_front();
                actual->setHnoDer(nodo);
                actual = nodo;
            }
        }
        ArbolN(const ArbolN<Element> &otro) {
            this->raiz = copiarNodo(otro.raiz); // copia profunda del árbol
            this->peso = otro.peso;             // copia directa del peso
        }

        ~ArbolN(){
            destruir(this->raiz);
        }

        bool esVacio(){ return this->raiz == NULL; } 
        Element getRaiz(){ return this->raiz->getInfo(); }
        NodoN<Element>* getNodoRaiz() { return this->raiz; }
        int getPeso(){ return this->peso; }

        void setRaiz(NodoN<Element> *nuevaRaiz){ this->raiz = nuevaRaiz; }
        void setPeso(Element element){ this->peso = peso; }

        list<ArbolN<Element>> getHijos(){
            NodoN<Element> *p;
            p = this->raiz->getHijoIzq();
            list<Element> lista;
            while(p != NULL){
                lista.insert(p->getInfo());
                p = p->getHnoDer();
            }
            return lista;
        }
        void copiar(ArbolN<Element> arbol){
            this->raiz = copiarNodo(arbol->raiz);
            this->peso = arbol->peso;
        }

        // Metodos de Insercion y Eliminacion
        void insertarSubArbol(ArbolN<Element> nuevo) {
            if (nuevo.raiz == NULL) return;

            NodoN<Element>* copia = copiarNodo(nuevo.raiz); // copia profunda

            if (this->raiz->getHijoIzq() == NULL) {
                this->raiz->setHijoIzq(copia);
            } else {
                NodoN<Element>* p = this->raiz->getHijoIzq();
                while (p->getHnoDer() != NULL) {
                    p = p->getHnoDer();
                }
                p->setHnoDer(copia);
            }
            this->peso += nuevo.getPeso();
        }
        
        void eliminarSubArbol(int posicionDeseada){
            NodoN<Element> *anterior = NULL, *p = this->raiz->getHijoIzq();
            int pos = 0;
            while(p != NULL && pos != posicionDeseada){
                pos++;
                anterior = p;
                p = p->getHnoDer();
            }
            if(pos == posicionDeseada){
                anterior->setHnoDer(p->getHnoDer());
                destruir(p);
            }
        }
        void eliminarSubArbolDesdePadre(int posicionPadre) {
            if (raiz == NULL) return;
            if (posicionPadre == 0) {
                destruir(raiz);
                raiz = NULL;
                peso = 0;
                return;
            }
            int pos = 0;
            eliminarRecursivo(NULL, raiz, pos, posicionPadre);
        }

        // Recorridos VERSION PUBLICA
        list<Element> preOrden(){
            list<Element> result;
            preOrden(this->raiz, &result);
            return result;
        }
        list<Element> postOrden(){
            list<Element> result;
            postOrden(this->raiz, &result);
            return result;
        }
        list<Element> inOrden(){
            list<Element> result;
            inOrden(this->raiz, &result);
            return result;
        }
        list<Element> porNiveles(){
            list<Element> result;
            queue<NodoN<Element>*> aux;
            NodoN<Element> *actual;
            actual = this->raiz;
            aux.push(actual);
            while(!aux.empty()){
                result.push_back(actual->getInfo());
                actual = actual->getHijoIzq();
                while(actual != NULL){
                    aux.push(actual);
                    actual = actual->getHnoDer();
                }
                aux.pop();
                actual = aux.front();
            }
            return result;
        }

        // Imprimir arbol (Publico)
        void imprimirArbol() {
            imprimirDesde(this->raiz, "", true);
        }
        void insertarJuego(Juego juego);
        void insertarNodoPorPadre(int padre, int hijoNuevo, int eficienciaLocal) {
            if(this->esVacio()) return;

            queue<NodoN<Estudiante>*> cola;
            NodoN<Estudiante> *nodoPadre = NULL;
            NodoN<Estudiante> *p;
            NodoN<Estudiante> *hijo;
            Estudiante aux;

            cola.push(this->getNodoRaiz());
            while(!cola.empty()){
                p = cola.front();
                cola.pop();
                aux = p->getInfo();
                // Si encuentra al padre sale del ciclo
                if(aux.getValor() == padre){
                    nodoPadre = p;
                    break;
                }
                hijo = p->getHijoIzq();
                // Si no lo encuentra, busca en los hijos y hermanos
                while(hijo != NULL){
                    cola.push(hijo);
                    hijo = hijo->getHnoDer();
                }
            }
            // Si se encontro el padre, inserta el hijo
            if(nodoPadre != NULL){
                Estudiante nuevoEstudiante(hijoNuevo, eficienciaLocal);
                NodoN<Estudiante> *nuevo = new NodoN<Estudiante>(nuevoEstudiante);
                hijo = nodoPadre->getHijoIzq();
                if(hijo == NULL){
                    nodoPadre->setHijoIzq(nuevo);
                }else{
                    while(hijo->getHnoDer() != NULL){
                        hijo = hijo->getHnoDer();
                    }
                    hijo->setHnoDer(nuevo);
                }
                this->peso++;
            }
        };
        int balanceHojas(){
            if(this->esVacio()) return 0;

            queue<NodoN<Element>*> cola, cAux;
            NodoN<Element> *p;
            NodoN<Element> *hijo;
            Element aux;
            int par = 0, impar = 0, nivel = 0;

            cola.push(this->getNodoRaiz());
            while(!cola.empty()){
                cAux = cola;
                while(!cAux.empty()){
                    p = cAux.front();
                    hijo = p->getHijoIzq();
                    if(hijo == NULL) (nivel % 2 == 0) ? par++ : impar++;
                    while(hijo != NULL){
                        cola.push(hijo);
                        hijo = hijo->getHnoDer();
                    }
                    cAux.pop();
                    cola.pop();
                }
                nivel++;
            }
            return par - impar;
        }
        void imprimirArbolEstudiantes(){
            imprimirDesdeEstudiante(this->raiz, "", true);
        }
        int maxSumaIndependiente(){
            int i, e;
            maxSumaIndependiente(this->raiz, &i, &e);
            return i > e ? i : e;
        }
};


#define ARBOLBIN_H
using namespace std;

template<typename Element>
class ArbolBin {
private:
    NodoBin<Element>* raiz;
    int peso;

    // Copia profunda
    NodoBin<Element>* copiarNodo(NodoBin<Element>* nodo) {
        if (!nodo) return NULL;
        NodoBin<Element>* nuevo = new NodoBin<Element>(nodo->getInfo());
        nuevo->setHijoIzq(copiarNodo(nodo->getHijoIzq()));
        nuevo->setHijoDer(copiarNodo(nodo->getHijoDer()));
        return nuevo;
    }

    // Destruir
    void destruir(NodoBin<Element>* nodo) {
        if (!nodo) return;
        destruir(nodo->getHijoIzq());
        destruir(nodo->getHijoDer());
        delete nodo;
        peso--;
    }

    // Contar nodos
    int contarNodos(NodoBin<Element>* nodo) {
        if (!nodo) return 0;
        return 1 + contarNodos(nodo->getHijoIzq()) + contarNodos(nodo->getHijoDer());
    }

    // Recorridos privados
    void preOrden(NodoBin<Element>* nodo, list<Element>& result) {
        if (!nodo) return;
        result.push_back(nodo->getInfo());
        preOrden(nodo->getHijoIzq(), result);
        preOrden(nodo->getHijoDer(), result);
    }

    void inOrden(NodoBin<Element>* nodo, list<Element>& result) {
        if (!nodo) return;
        inOrden(nodo->getHijoIzq(), result);
        result.push_back(nodo->getInfo());
        inOrden(nodo->getHijoDer(), result);
    }

    void postOrden(NodoBin<Element>* nodo, list<Element>& result) {
        if (!nodo) return;
        postOrden(nodo->getHijoIzq(), result);
        postOrden(nodo->getHijoDer(), result);
        result.push_back(nodo->getInfo());
    }

    void imprimirDesde(NodoBin<Element>* nodo, string prefijo, bool esUltimo) {
        if (!nodo) return;
        cout << prefijo << (esUltimo ? "+-- " : "|-- ") << nodo->getInfo() << endl;
        string nuevoPrefijo = prefijo + (esUltimo ? "    " : "|   ");
        if (nodo->getHijoIzq() || nodo->getHijoDer()) {
            imprimirDesde(nodo->getHijoIzq(), nuevoPrefijo, false);
            imprimirDesde(nodo->getHijoDer(), nuevoPrefijo, true);
        }
    }
    
public:
    // Constructores
    ArbolBin() : raiz(NULL), peso(0) {}
    ArbolBin(NodoBin<Element>* nuevaRaiz) : raiz(nuevaRaiz) {
        peso = contarNodos(nuevaRaiz);
    }
    ArbolBin(const ArbolBin<Element>& otro) {
        raiz = copiarNodo(otro.raiz);
        peso = otro.peso;
    }
    ~ArbolBin() { destruir(raiz); }

    // Getters
    bool esVacio() { return raiz == NULL; }
    Element getRaiz() { return raiz->getInfo(); }
    NodoBin<Element>* getNodoRaiz() { return raiz; }
    int getPeso() { return peso; }

    // Setters
    void setRaiz(NodoBin<Element>* nuevaRaiz) { raiz = nuevaRaiz; peso = contarNodos(nuevaRaiz); }

    // Métodos públicos
    void copiar(const ArbolBin<Element>& arbol) {
        destruir(raiz);
        raiz = copiarNodo(arbol.raiz);
        peso = arbol.peso;
    }

    void insertarSubArbolIzq(const ArbolBin<Element>& sub) {
        if (!sub.raiz) return;
        NodoBin<Element>* copia = copiarNodo(sub.raiz);
        if (!raiz->getHijoIzq()) raiz->setHijoIzq(copia);
        else {
            NodoBin<Element>* temp = raiz->getHijoIzq();
            while (temp->getHijoDer()) temp = temp->getHijoDer();
            temp->setHijoDer(copia);
        }
        peso += sub.peso;
    }

    void insertarSubArbolDer(const ArbolBin<Element>& sub) {
        if (!sub.raiz) return;
        NodoBin<Element>* copia = copiarNodo(sub.raiz);
        if (!raiz->getHijoDer()) raiz->setHijoDer(copia);
        else {
            NodoBin<Element>* temp = raiz->getHijoDer();
            while (temp->getHijoIzq()) temp = temp->getHijoIzq();
            temp->setHijoIzq(copia);
        }
        peso += sub.peso;
    }

    void eliminarSubArbolIzq() {
        if (!raiz || !raiz->getHijoIzq()) return;
        destruir(raiz->getHijoIzq());
        raiz->setHijoIzq(NULL);
    }

    void eliminarSubArbolDer() {
        if (!raiz || !raiz->getHijoDer()) return;
        destruir(raiz->getHijoDer());
        raiz->setHijoDer(NULL);
    }

    // Recorridos públicos
    list<Element> preOrden() { 
        list<Element> r; 
        preOrden(raiz, r); 
        return r; 
    }
    list<Element> inOrden() { 
        list<Element> r; 
        inOrden(raiz, r); 
        return r; 
    }
    list<Element> postOrden() { 
        list<Element> r; 
        postOrden(raiz, r); 
        return r; }

    list<Element> porNiveles() {
        list<Element> result;
        if (!raiz) return result;
        queue<NodoBin<Element>*> q;
        q.push(raiz);
        while (!q.empty()) {
            NodoBin<Element>* actual = q.front(); q.pop();
            result.push_back(actual->getInfo());
            if (actual->getHijoIzq()) q.push(actual->getHijoIzq());
            if (actual->getHijoDer()) q.push(actual->getHijoDer());
        }
        return result;
    }

    // Método público para imprimir
    void imprimirArbol() { imprimirDesde(raiz, "", true); }
};

#define ARBOLBST_H
using namespace std;

template<typename Element>
class ArbolBST {
    private:
        NodoBin<Element>* raiz;
        int peso;
        // Inserción recursiva (BST)
        NodoBin<Element>* insertarRec(NodoBin<Element>* nodo, const Element& valor) {
            if (!nodo) {
                peso++;
                return new NodoBin<Element>(valor);
            }
            if (valor < nodo->getInfo()) {
                nodo->setHijoIzq(insertarRec(nodo->getHijoIzq(), valor));
            } else if (valor > nodo->getInfo()) {
                nodo->setHijoDer(insertarRec(nodo->getHijoDer(), valor));
            }
            // Si es igual, no se inserta (evitamos duplicados)
            return nodo;
        }
        // Liberar memoria para destruir
        void destruir(NodoBin<Element>* nodo) {
            if (!nodo) return;
            destruir(nodo->getHijoIzq());
            destruir(nodo->getHijoDer());
            delete nodo;
            peso--;
        }
        // Búsqueda recursiva
        bool contieneRec(NodoBin<Element>* nodo, const Element& valor) const {
            if (!nodo) return false;
            if (valor == nodo->getInfo()) return true;
            if(valor < nodo->getInfo()){
                return contieneRec(nodo->getHijoIzq(), valor);
            }else{
                return contieneRec(nodo->getHijoDer(), valor);
            }
            /* Utilizando condicional ternario
            return valor < nodo->getInfo()
                ? contieneRec(nodo->getHijoIzq(), valor)
                : contieneRec(nodo->getHijoDer(), valor);
            */
            
        }
        // Recorridos
        void inOrden(NodoBin<Element>* nodo, list<Element>& result) const {
            if (!nodo) return;
            inOrden(nodo->getHijoIzq(), result);
            result.push_back(nodo->getInfo());
            inOrden(nodo->getHijoDer(), result);
        }

        void preOrden(NodoBin<Element>* nodo, list<Element>& result) const {
            if (!nodo) return;
            result.push_back(nodo->getInfo());
            preOrden(nodo->getHijoIzq(), result);
            preOrden(nodo->getHijoDer(), result);
        }

        void postOrden(NodoBin<Element>* nodo, list<Element>& result) const {
            if (!nodo) return;
            postOrden(nodo->getHijoIzq(), result);
            postOrden(nodo->getHijoDer(), result);
            result.push_back(nodo->getInfo());
        }
        // Imprimir árbol
        void imprimirDesde(NodoBin<Element>* nodo, string prefijo, bool esUltimo) const {
            if (!nodo) return;
            cout << prefijo << (esUltimo ? "+-- " : "|-- ") << nodo->getInfo() << endl;
            string nuevoPrefijo = prefijo + (esUltimo ? "    " : "|   ");
            if (nodo->getHijoIzq() || nodo->getHijoDer()) {
                imprimirDesde(nodo->getHijoIzq(), nuevoPrefijo, false);
                imprimirDesde(nodo->getHijoDer(), nuevoPrefijo, true);
            }
        }
        NodoBin<Element>* encontrarMinimo(NodoBin<Element>* nodo) {
            NodoBin<Element>* actual = nodo;
            while (actual && actual->getHijoIzq() != NULL) {
                actual = actual->getHijoIzq();
            }
            return actual;
        }

        NodoBin<Element>* eliminarRec(NodoBin<Element>* nodo, const Element& valor) {
            if (!nodo) return nodo;

            if (valor < nodo->getInfo()) {
                nodo->setHijoIzq(eliminarRec(nodo->getHijoIzq(), valor));
            } else if (valor > nodo->getInfo()) {
                nodo->setHijoDer(eliminarRec(nodo->getHijoDer(), valor));
            } else {
                // Nodo con un solo hijo o sin hijos
                if (nodo->getHijoIzq() == NULL) {
                    NodoBin<Element>* temp = nodo->getHijoDer();
                    delete nodo;
                    peso--;
                    return temp;
                } else if (nodo->getHijoDer() == NULL) {
                    NodoBin<Element>* temp = nodo->getHijoIzq();
                    delete nodo;
                    peso--;
                    return temp;
                }
                // Nodo con dos hijos: obtener el sucesor inorden (el más pequeño en el subárbol derecho)
                NodoBin<Element>* temp = encontrarMinimo(nodo->getHijoDer());
                nodo->setInfo(temp->getInfo()); // Copiar el contenido del sucesor inorden a este nodo
                nodo->setHijoDer(eliminarRec(nodo->getHijoDer(), temp->getInfo())); // Eliminar el sucesor inorden
            }
            return nodo;
        }
    public:
        // Constructores
        ArbolBST() : raiz(NULL), peso(0) {}
        ~ArbolBST() { destruir(raiz); }
        // Getters
        bool esVacio() const { return raiz == NULL; }
        int getPeso() const { return peso; }
        Element getRaiz() const { return raiz->getInfo(); }
        // Setters 
        void setRaiz(NodoBin<Element>* nuevaRaiz) { raiz = nuevaRaiz; }
        void setPeso(Element nuevoPeso){ this->peso = nuevoPeso; }
        
        // Insertar
        void insertar(const Element& valor) {
            this->raiz = insertarRec(raiz, valor);
        }
        // Eliminar un elemento en especifico
        void eliminar(const Element& valor) {
            this->raiz = eliminarRec(raiz, valor);
        }
        
        // Buscar
        bool contiene(const Element& valor) const {
            return contieneRec(raiz, valor);
        }
        // Recorridos públicos
        list<Element> inOrden() const {
            list<Element> r;
            inOrden(raiz, r);
            return r;
        }
        list<Element> preOrden() const {
            list<Element> r;
            preOrden(raiz, r);
            return r;
        }
        list<Element> postOrden() const {
            list<Element> r;
            postOrden(raiz, r);
            return r;
        }
        // Imprimir
        void imprimirArbol() const {
            imprimirDesde(raiz, "", true);
        }
        
};

namespace list_utils {
    template <typename T>
    void imprimir(const list<T>& lista, const string& separador = ", ") {
        for (auto it = lista.begin(); it != lista.end(); ++it) {
            cout << *it;
            if (next(it) != lista.end()) {
                cout << separador;
            }
        }
        cout << endl;
    }

}


#endif