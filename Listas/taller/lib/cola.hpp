#ifndef COLA_H
#define COLA_H
#include "nodo.hpp"
#include <iostream>
using namespace std;
template <typename Element> 
class Cola{
    private:
        Nodo<Element>* front;
        Nodo<Element>* last;
        int length;
    
    public:
    Cola() : front(NULL), last(NULL), length(0) {}
    Cola(Nodo<Element>* front, Nodo<Element>* last, int length) 
    : front(front),  last(last), length(length) {}
    //Constructor de Copia
    Cola(const Cola<Element>& originalQueue) : front(NULL), last(NULL), length(0) {
        if(originalQueue.isEmpty()) return;
        Nodo<Element>* current = originalQueue.front;
        while(current != NULL){
            Element element = current->getInfo();
            Nodo<Element>* newNode = new Nodo<Element>(element);
            if(this->length <= 0 && this->front == NULL){
                newNode->setNext(NULL);
                this->front = newNode;
                this->last = newNode;
                length++;
                return;
            }
            this->setNext(newNode);
            this->last = newNode;
            this->length++;
        }
    }
    Nodo<Element>* getFront() const { return this->front; }
    Nodo<Element>* getLast() const { return this->last; }
    int getLength() const { return this->length; }
    Element getFirst() const { return this->front->getInfo(); }
    Element getEnd() const { return this->last->getInfo(); }
    bool isEmpty() { return length <= 0 && front == NULL; }
    void enqueue(Element element){
        Nodo<Element>* newNode = new Nodo<Element>(element);
        if(this->length <= 0 && this->front == NULL){
            newNode->setNext(NULL);
            this->front = newNode;
            this->last = newNode;
            length++;
            return;
        }
        this->last->setNext(newNode);
        this->last = newNode;
        this->length++;
    }
    void dequeue(){
        if(this->length <= 0 && this->front == NULL) return;
        Nodo<Element>* nodo = front;
        this->front = front->getNext();
        this->length--;
        delete nodo;
        if(this->length <= 0 && this->front == NULL){
            this->front = NULL;
            this->last = NULL;
            this->length = 0;
        }
    }
    void printQueue(){
        Nodo<Element>* current = this->front;
        cout << "NULL";
        while(current != NULL){
            cout << "<-[" << current->getInfo() << "]";
            current = current->getNext();
        }
    }
};
#endif