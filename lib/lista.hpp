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
        Lista(Nodo<Element>* head, Nodo<Element>* tail, int length) : head(head), tail(tail), length(length) {} //Constructor con parametros
        //Constructor de copia
        Lista(const Lista<Element>& originalList) : head(NULL), tail(NULL), length(0) {
            Nodo<Element>* current = originalList.head, *otroActual = NULL;
            this->head = otroActual;
            while(current != NULL){
                otroActual = new Nodo<Element>(current->getInfo());
                current = current->getNext();
                otroActual = otroActual->getNext();
            }
            this->length = originalList.length;
            
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
        bool isEmpty(){ return head == NULL && length == 0; }
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
        Nodo<Element>* findNodo(Element consulta){
            Nodo<Element>* current = this->front;
            bool flag = true;
            while(current != NULL){
                if(current->getInfo() == consulta) return current;
            }
            return NULL;
        }
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
        void mergeSort(){
            if(this->length <= 1) return;
            this->head = mergeSortRec(this->head);

            Nodo<Element>* current = this->head;
            while(current != NULL && current->getNext() != NULL){
                current = current->getNext();
            }
            this->tail = current;
        }
};
#endif