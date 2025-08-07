#ifndef PILA_H
#define PILA_H
#include <iostream>
#include "nodo.hpp"
using namespace std;
template <typename Element>
class Pila{
    private:
        Nodo<Element> *top;
        int length;
    public:
        Pila() : top(NULL), length(0){}
        ~Pila(){
            Clear();
        }
        bool IsEmpty() const{
            return this->length == 0 && this->top == NULL;
        }
        void clear(){
            Nodo<Element> *node;
            //Pop a todo
            while(!(this->length == 0 && this->top == NULL)){
                node = this->top;
                this->top = top->getNext();
                this->length--;
                delete node;
            }
            this->top = NULL;
            this->length = 0;
        }
        void Push(Element element){
            Nodo<Element> *newNode = new Nodo<Element>(element);
            if(this->length == 0 && top == NULL){
                this->top = newNode;
                this->length++;
                return;
            }
            newNode->setNext(top);
            this->length++;
            this->top = newNode;
        }
        void Pop(){
            if(this->length <= 0 && this->top == NULL) return;
            Nodo<Element> *nodo = this->top;
            this->top = top->getNext();
            delete nodo;
            this->length--;
            if(this->length < 0) this->length = 0;
            
        }
        void PrintStack(){
            Nodo<Element> *current;
            current = this->top;
            while(current != NULL){
                cout << " [" << current->getInfo() << "]->";
                current = current->getNext();
            }
            cout << " NULL";

        }
};
#endif