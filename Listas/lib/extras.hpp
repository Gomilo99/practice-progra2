#include "lista.hpp"
#include "pila.hpp"
#include "cola.hpp"

Lista<Lista<int>> compacta(Lista<int> list){
    Lista<Lista<int>> compact;
    Lista<int> sub;
    int cont = 0, num = 0;
    
    if(list.getLength() > 1){
        while(!list.isEmpty()){
            num = list.search(0);
            cont++;
            list.removeToStart();
            if(list.isEmpty()){
                sub.addToStart(num);
                sub.addAtPosition(1, cont);
                compact.addAtPosition(compact.getLength(), sub);
            }else{
                if(num != list.search(0)){
                    sub.addToStart(num);
                    sub.addAtPosition(1, cont);
                    compact.addAtPosition(compact.getLength(), sub);
                    sub.clear();
                    cont = 0;
                }
            }
        }
    }else{
        if(list.getLength() == 1){
            sub.addToStart(list.search(0));
            sub.addAtPosition(1,1);
            compact.addToEnd(sub);
        }
    }
    
    return compact;
}


