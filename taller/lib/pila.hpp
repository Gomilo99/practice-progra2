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
            clear();
        }
        Pila(const Pila<Element>& original) : top(NULL), length(0) {
            if (original.IsEmpty()) return;

            Pila<Element> tempStack;
            Nodo<Element>* current = original.top;

            while (current != NULL) {
                tempStack.Push(current->getInfo());
                current = current->getNext();
            }

            while (!tempStack.IsEmpty()) {
                this->Push(tempStack.top->getInfo());
                tempStack.Pop();
            }
        }            
        

        int GetLength() const { return length;}
        void SetLength(int length) { this->length = length; }
        Nodo<Element>* GetTop(){ return this->top; }
        void SetTop(Nodo<Element> *newtop){ this->top = newtop;}
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
        Pila<Element> Clone() const{
            Pila<Element> newPila;
            Pila<Element> temp;
            Nodo<Element> *current = this->top;
            //Traspasa a una pila auxiliar
            while(current != NULL){
                temp.Push(current->getInfo());
                current = current->getNext();
            }
            //Revierte el traspaso
            while(!temp.IsEmpty()){
                newPila.Push(temp.GetTop());
                temp.Pop();
            }
            return newPila;
        }
        
        void Reverse(){
            if(IsEmpty() || length == 1) return;
            Nodo<Element>* prev = NULL;
            Nodo<Element>* current = this->top;
            Nodo<Element>* next = NULL;

            while(current != NULL){
                next = current->getNext();
                current->setNext(prev);
                prev = current;
                current = next;
            }
            this->top = prev;
        }            
            
};
#endif