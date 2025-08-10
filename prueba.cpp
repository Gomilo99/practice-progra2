#include "lib/lista.hpp"
#include <iostream>

int main(){
    Lista<int> lista;
    int sum = 0;

    for(int i=1; i <= 10; i++){
        sum=sum+i;
        lista.addToStart(sum);
        lista.printList();
        lista.addAtPosition((sum*50)%i, sum+1);
    }
    lista.printList();
    return 0;
}