#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include "nodo.hpp"
template <typename Element>
class Lista {
    private:
        Nodo<Element>* head;
        Nodo<Element>* tail;
        int length;

        Nodo<Element>* getMiddle(Nodo<Element>* head){
            if(isNullNode(head)) return NULL;
            Nodo<Element>* slow = head; //avanza un nodo a la vez
            Nodo<Element>* fast = head; //avanza dos nodos a la vez

            while(!isNullNode(fast->getNext()) && !isNullNode(fast->getNext()->getNext())){
                slow = slow->getNext();
                fast = fast->getNext()->getNext();
            }
            //si fast llego al final, slow está en el medio
            return slow;
        } //O(n)
        Nodo<Element>* sortedMerge(Nodo<Element>* left, Nodo<Element>* right){
            //si una de las listas es NULL, devuelve la otra
            if(isNullNode(left)) return right;
            if(isNullNode(right)) return left;
            //Nodo ficticio para simplificar la fusion
            Nodo<Element> dummy;
            Nodo<Element>* tail = &dummy;
            
            while(!isNullNode(left) && !isNullNode(right)){
                if(left->getInfo() <= right->getInfo()){
                    tail->setNext(left);
                    left = left->getNext();
                }else{
                    tail->setNext(right);
                    right = right->getNext();
                }
                tail = tail->getNext();
            }
            //conecta con la lista no vacia
            if(!isNullNode(left)){
                tail->setNext(left);
            }else{
                tail->setNext(right);
            }
            //devuelve la lista fusionada, excluyendo el nodo ficticio
            return dummy.getNext();
        }//O(n+m)

        Nodo<Element>* mergeSortRec(Nodo<Element>* head){
            if(isNullNode(head, head->getNext())) return head;
            
            Nodo<Element>* middle = getMiddle(head);
            Nodo<Element>* nextMiddle = middle->getNext();
            middle->setNext(NULL);

            Nodo<Element>* left = mergeSortRec(head);
            Nodo<Element>* right = mergeSortRec(nextMiddle);

            return sortedMerge(left, right);
        } //O(n logn)
        
    public:
        Lista() : head(NULL), tail(NULL), length(0) {} //Constructor por defecto
        
        /**
         * @brief constructor con valores especificos
         */
        Lista(Nodo<Element>* head, Nodo<Element>* tail, int length) : head(head), tail(tail), length(length) {} //Constructor con parametros
        //Constructor de copia
        /**
         * @brief constructor copia
         */
        Lista(const Lista<Element>& originalList) : head(NULL), tail(NULL), length(0) {
            Nodo<Element>* current = originalList.head;
            Nodo<Element>* newHead = NULL;
            Nodo<Element>* newTail = NULL;

            while(current != NULL){
                // Use copy constructor to create a deep copy of the element
                Element newElement = current->getInfo(); 
                Nodo<Element>* newNode = new Nodo<Element>(newElement);

                if (newHead == NULL) {
                    newHead = newNode;
                } else {
                    newTail->setNext(newNode);
                }
                newTail = newNode;            
                current = current->getNext();
            }
            
        }//O(n)

        //Destructor
        ~Lista() {
            Nodo<Element>* current = head;
            while (current != NULL) {
                Nodo<Element>* nextNode = current->getNext();
                delete current;
                current = nextNode;
            }
            head = NULL;
            tail = NULL;
            length = 0;
        }// O(n)

        //Getters
        Nodo<Element>* getHead() const { return this->head; }
        Nodo<Element>* getTail() const { return this->tail; }
        int getLength() const { return this->length; }

        //Setters
        void setHead(Nodo<Element>* head) { this->head = head; }
        void setTail(Nodo<Element>* tail) { this->tail = tail; }
        void setLength(int length) { this->length = length; }

        //Metodos de la lista
        /**
         * @brief Evalua si la lista no es vacia (si head es nulo y la longitud es 0)
         */
        bool isEmpty(){ return head == NULL && length == 0; }

        /**
         * @brief Añade un nuevo elemento al final de la lista
         * @param newElement Es el nuevo elemento a agregar
         */
        void addToEnd(Element newElement){
            Nodo<Element>* newNode = new Nodo<Element>(newElement);
            if (this->length == 0) {
                this->tail = newNode;
                this->head = newNode;
            }else{
                this->tail->setNext(newNode);
                this->tail = newNode;
            }
            this->length++;
        }
        /**
         * @brief Inserta el elemento en la cabeza (HEAD)
         */
        void addToStart(Element newElement) {
            Nodo<Element>* newNode = new Nodo<Element>(newElement);
            if (this->length == 0) {
                this->head = newNode;
                this->tail = newNode;
            }else{
                newNode->setNext(this->head);
                this->head = newNode;
            }
            this->length++;
        }

        /**
         * @brief Inserta el elemento en la posicion designada
         * @param index es la posicion deseada
         * @param newElement es el elemento a agregar
         */
        void addAtPosition(int index, Element newElement) {
            if(this->length == 0)
            if (index < 0 || index > this->length) {
                throw out_of_range("\nError: Index out of range\n");
                return;
            }
            if (index == 0) {
                this->addToStart(newElement);
            } else if (index == this->length) {
                this->addToEnd(newElement);
            } else {
                Nodo<Element>* newNode = new Nodo<Element>(newElement);
                Nodo<Element>* current = this->head;
                for (int i = 0; i < index - 1; ++i) {
                    current = current->getNext();
                }
                newNode->setNext(current->getNext());
                current->setNext(newNode);
                this->length++;
            }
        }

        /**
         * @brief Intercambia dos nodos
         * @param pos1 posicion del primer nodo
         * @param pos2 posicon del segundo nodo
         */
        void swap(Element pos1, Element pos2){

            if (pos1 < 0 || pos2 < 0 || pos1 >= this->length || pos2 >= this->length) {
                throw out_of_range("\nError: Index out of range\n");
                return;
            }
            Nodo<Element>* current = this->head;
            Nodo<Element>* node1 = NULL;
            Nodo<Element>* node2 = NULL;
            if(pos1 == pos2) return;
            
            for(int i = 0; i < length; i++){
                if(i == pos1) node1 = current;
                if(i == pos2) node2 = current;
                current = current->getNext();
            }
            if(node1 == NULL || node2 == NULL){
                throw out_of_range("\nError: Index out of range\n");
                return;
            }
            Element temp = node1->getInfo();
            node1->setInfo(node2->getInfo());
            node2->setInfo(temp);
        }

        /**
         * @brief Elimina el primer elemento de la lista
         */
        void removeToStart(){
            if(this->length == 0){
                throw out_of_range("\nError: List is empty\n");
                return;
            }
            Nodo<Element>* nodo = this->head;

            this->head = this->head->getNext();
            delete nodo;
            this->length--;
            if(this->length == 0) this->tail = NULL;
        }

        /**
         * @brief Elimina el elemento en la posicion designada
         * @param index es la posicion del nodo a eliminar (si index = 0 es equivalente a utilziar removeToStart() )
         */
        void removeAtPosition(int index){
            if(this->length == 0){
                throw out_of_range("\nError: List is empty\n");
            }
            if(index == 0) this->removeToStart();
            Nodo<Element>* previous = this->head;
            int i = 0;
            while(i < index-1){
                previous = previous->getNext();
                i++;
            }
            Nodo<Element>* nodo = previous->getNext();
            if(nodo == this->tail) this->tail = previous;
            previous->setNext(nodo->getNext());
            this->length--;
            delete nodo;
        }

        /**
         * @brief Imprime la lista
         */
        void printList(){
            cout << "Lista: ";
            if(this->length == 0) {
                cout << "vacia" << endl;
                return;
            }
            Nodo<Element>* current = this->head;
            while(current != NULL){
                cout << current->getInfo() << " -> ";
                current = current->getNext();
            }
            cout << "NULL" << endl;
        }

        /**
         * @brief Actualiza un elemento en la lista
         * @param index es la posicion deseada
         * @param newElement es elemento a reemplazar
         */
        void updateElement(int index, Element newElement){
            if(index < 0 || index > this->length){
                throw out_of_range("\nError: Index out of range\n");
                return;
            }
            if(index == 0) {
                this->head->setInfo(newElement);
                return;
            }
            if(index == this->length){
                this->tail->setInfo(newElement);
                return;
            }
            Nodo<Element>* current = this->head;
            int i = 0;
            while(i < index){
                current = current->getNext();
                i++;
            }
            current->setInfo(newElement);
            return;
        }
        
        /**
         * @brief Busca un elemento en la lista. O(1) para los extremos, O(n) para los demas casos
         * @param posicion a consular
         * @return devuelve el contenido del nodo consultado
         */
        Element search(int index) const {
            if(index == 0) return this->head->getInfo();
            if(index == this->length -1){ return this->tail->getInfo(); }

            Nodo<Element>* current = this->head;
            int i = 0; 
            while(current != NULL && i < index){
                current = current->getNext();
                i++;
            }
            return current->getInfo();
        }
        /**
         * @brief Encuentra el Nodo que contiene el elemento
         * @param consulta es el elemento a encontrar
         * @return El apuntador al nodo que contiene el elemento
         */
        Nodo<Element>* findNodo(Element consulta){
            Nodo<Element>* current = this->front;
            bool flag = true;
            while(current != NULL){
                if(current->getInfo() == consulta) return current;
            }
            return NULL;
        }

        /**
         * @brief Encuentra la posicion de un elemento en la lista
         * @param element Argumento a encontrar
         * @return posicion en la lista (-1 si no lo encuentra)
         */
        int findIndex(Element element) const{
            Nodo<Element>* current = this->head;
            int index = 0;
            while(current != NULL){
                if(current->getInfo() == element) return index;
                current = current->getNext();
                index++;
            }
            return -1;
        }
        /**
         * @brief Vacia el contenido de la lista
         */
        void clear(){
            while(this->head != NULL){
                Nodo<Element>* temp = this->head;
                this->head = this->head->getNext();
                delete temp;
            }
            this->length = 0;
            this->head = NULL;
            this->tail = NULL;
        }

        /**
         * @brief invierta la lista y todos sus elementos
         */
        void reverse(){
            if(this->length < 1) return;
            Nodo<Element>* prev = NULL;
            Nodo<Element>* current = this->head;
            Nodo<Element>* originalHead = this->head;

            while(current!= NULL){
                Nodo<Element>* next = current->getNext();
                current->setNext(prev);
                prev = current;
                current = next;
            }
            this->head = prev;
            this->tail = originalHead;
        }

        /**
         * @brief Ordena la lista con MergeSort
         */
        void mergeSort(){
            if(this->length <= 1) return;
            this->head = mergeSortRec(this->head);

            Nodo<Element>* current = this->head;
            while(current != NULL && current->getNext() != NULL){
                current = current->getNext();
            }
            this->tail = current;
        }

        /**
         * @brief copia una lista en la instancia. Vacia la lista actual y da espacio a la nueva
         * @param nuevalista es la lista a copiar en la instancia
         */
        void copy(const Lista<Element> &nuevalista){
            Nodo<Element> *nuevo, *current;
            current = nuevalista.head;
            this->clear();
            if(nuevalista.length <= 0 && nuevalista.head){
                this->head = NULL;
                this->length = nuevalista.length;
                return;
            }
            nuevo = new Nodo<Element>(current->getInfo());
            this->head = nuevo;
            current = current->getNext();
            while(current != NULL){
                nuevo->setNext(new Nodo<Element>(current->getInfo()));
                nuevo = nuevo->getNext();
                current = current->getNext();
            }

        }
        //Sobrecarga de Operadores
        Lista<Element>& operator= (const Lista<Element> &lista){
            if(this != &lista) return this->copy(lista);
        }
        Element operator [](int pos){
            return this->search(pos);
        }
        bool operator >(const Lista<Element> &lista){
            return this->length > lista.length;
        }
        bool operator <(const Lista<Element> &lista){
            return this->length < lista.length;
        }

        void addLista(Lista<Element> lista){
            
        }
};
#endif