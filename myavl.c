#include <stdio.h>
#include <stdlib.h>
#include "libavl.h"


int main() {
    char ch;
    int x,i;
    tree_Nodo *raiz;

   raiz = NULL;


        while (scanf ("%c %d",&ch, &x) != EOF){
            if (ch == 'i')
            {   
                raiz = Inclui(raiz, x);
               
            }
        
            if (ch == 'r')
            {
                raiz = Remove(raiz, x);
                
            }
        }

        i = Altura_Nodo(raiz);
        raiz = recal(raiz);
        in_order (raiz,i);
        
        
    free (raiz);
    return 0;
}

