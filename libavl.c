#include "libavl.h"
#include <stdlib.h>
#include <stdio.h>


//Funções auxiliares
////////////////////////////////////////////////
// Cria novo nodo
 tree_Nodo *CriaNodo (int valor) {
    tree_Nodo *n;

    n = malloc (sizeof(tree_Nodo));
    n->key = valor;
    n->left = NULL;
    n->right = NULL;
   
    n->height = 0; 
    return n;
 }

 // Inicializa Nodo
tree_Nodo *InicializaNodo (int valor) {
    return CriaNodo (valor);
}


// Funcao que recalcula as alturas depois que todas as operacoes foram realizadas 
tree_Nodo *recal (tree_Nodo *nodo) {
    if (nodo == NULL)
        return NULL;
    if ((nodo->left ==NULL) && (nodo->right == NULL))
        return nodo;

    if ((nodo->left != NULL) && (nodo->right != NULL)) {
    nodo->left->height = nodo->height-1;
    nodo->right->height = nodo->height-1;
    nodo->left = recal (nodo->left);
    nodo->right = recal (nodo->right);
    }
    else
    {
         if((nodo->left == NULL) && (nodo->right != NULL)){
            nodo->right->height = nodo->height-1;
            nodo->right = recal (nodo->right);
            }
        else
        {
            nodo->left->height = nodo->height-1;
            nodo->left = recal (nodo->left);
        }
    }
    return nodo;
}
// Função que informa a altura do nodo
int Altura_Nodo (tree_Nodo *nodo)
{
    int ae,ad;
    if (nodo == NULL)
        return -1;
    
    ae = Altura_Nodo(nodo->left);
    ad = Altura_Nodo(nodo->right);

    if (ae > ad)
        return ae+1;
    else
    return ad+1;
}

// Função que retorna o mair valor entre duas váriaveis inteiras
int valorMax(int x, int y)
{
    if (x > y)
        return (x);
    return (y);

}


// Calcula o fator de balanceamento de um nodo
int FatorBalanceamento_Nodo (tree_Nodo *nodo) {
    if (nodo == NULL)
        return 0;        
    return (Altura_Nodo(nodo->left) - Altura_Nodo(nodo->right));
}

// Função que busca valor na árvore 
tree_Nodo *Busca (int valor, tree_Nodo *nodo) {
    if (nodo == NULL)
        return NULL;
    if (nodo->key == valor)
        return nodo;
    if (nodo->key > valor)
        return Busca(valor,nodo->left);
    else
        return Busca(valor,nodo->right);
}
    


tree_Nodo *maiornodo(tree_Nodo *nodo) {
    if (nodo->right == NULL)
        return nodo;
    else
        return maiornodo(nodo->right);
}

int Calculaaltura(tree_Nodo *nodo)
{

    return valorMax(Altura_Nodo(nodo->left),Altura_Nodo(nodo->right))+1;
}
    
// Função que realiza a Rotação Direita do nodo passado por parametro
tree_Nodo *rotDIR (tree_Nodo *nodo) {
    tree_Nodo *auxiliar1;
    tree_Nodo *auxiliar2;

    auxiliar1 = nodo->left;
    auxiliar2 = auxiliar1->right;

    auxiliar1->right = nodo;
    nodo->left = auxiliar2;

    nodo->height = Calculaaltura(nodo);
    auxiliar1->height = Calculaaltura(auxiliar1);
    
    return auxiliar1;

}

// Função que realiza a Rotação Esquerda
tree_Nodo *rotESQ (tree_Nodo *nodo) {
    tree_Nodo *auxiliar1;
    tree_Nodo *auxiliar2;

    auxiliar1 = nodo->right;
    auxiliar2 = auxiliar1 ->left;

    auxiliar1->left = nodo;
    nodo->right = auxiliar2;
   
    nodo->height = Calculaaltura(nodo);
    auxiliar1->height = Calculaaltura(auxiliar1);
    
    return auxiliar1;
}

// Função que realiza a inclusão na árvore AVL
tree_Nodo *Inclui (tree_Nodo *nodo, int valor){

    int FatordeBalanceamento;
    
    if (nodo == NULL)
        return (InicializaNodo(valor));

    
    if (valor < nodo->key)
        nodo->left = Inclui(nodo->left, valor);
    else if (valor > nodo->key)
        nodo->right = Inclui (nodo->right, valor);
    else
        return nodo;

    nodo->height = Calculaaltura(nodo);

    FatordeBalanceamento = FatorBalanceamento_Nodo(nodo);

    // Se o nodo está desbalanceado temos 4 casos de balanceamento 

    // Caso Esq-Esq
    if ((FatordeBalanceamento > 1) && (valor < nodo->left->key))
        return rotDIR(nodo);

    // Caso Dir-Dir
    if ((FatordeBalanceamento < -1) && (valor > nodo->right->key))
        return rotESQ(nodo);

    // Caso Dir-Esq
    if ((FatordeBalanceamento <-1) && (valor < nodo->right->key))
        {
            nodo->right = rotDIR (nodo->right);
            return rotESQ(nodo);
        }
    // Caso Esq-Dir
    if ((FatordeBalanceamento > 1) && (valor > nodo->left->key))
    {
        nodo ->left = rotESQ(nodo->left);
        return rotDIR(nodo);
    }

    return nodo;
}


// Função que realiza a remoção na árvore AVL
tree_Nodo *Remove (tree_Nodo *nodo, int valor){
int FatordeBalanceamento=0;

    if (nodo == NULL )
        return nodo;

    if (valor < nodo->key) 
        nodo->left = Remove(nodo->left,valor);
    
    else if (valor > nodo->key)
        nodo->right = Remove (nodo->right,valor);
        

    else
    // Caso o valor seja igual a chave do nodo, então este é o nodo que tem que ser deletado
    {

        // Caso o nodo tenha dois filhos
        if ((nodo->left ) && (nodo->right))
        {
            tree_Nodo *auxiliar;

            auxiliar = maiornodo(nodo->left);

            nodo->key = auxiliar->key;
            nodo->left = Remove(nodo->left,auxiliar->key);

        
        }
        else
        {
            tree_Nodo *auxiliar;

            if ((nodo->left == NULL) && (nodo->right == NULL))
            {
                auxiliar = nodo;
                nodo = NULL;
            }
            else 
            {
                
                if (nodo->left != NULL)
                {

                    auxiliar = nodo->left;
                    *nodo = *auxiliar;
                }
                else
                {
                    auxiliar = nodo-> right;
                    *nodo = *auxiliar;
                }
            
            }
            
            free(auxiliar);
        }

    }

    if (nodo == NULL)
        return nodo;
    
    nodo->height= Calculaaltura(nodo);

    FatordeBalanceamento = FatorBalanceamento_Nodo(nodo);

    // Se o nodo está desbalanceado temos 4 casos

     // Caso Esq Esq
    if ((FatordeBalanceamento > 1) && (FatorBalanceamento_Nodo(nodo->left) >= 0))
        return rotDIR(nodo);
 
    // Caso Esq Dir
    if ((FatordeBalanceamento > 1) && (FatorBalanceamento_Nodo(nodo->left) < 0))
    {
        nodo->left =  rotESQ(nodo->left);
        return rotDIR(nodo);
    }
 
    // Caso Dir Dir
    if ((FatordeBalanceamento < -1) && (FatorBalanceamento_Nodo(nodo->right) <= 0))
        return rotESQ(nodo);
 
    // Caso Dir Esq
    if ((FatordeBalanceamento < -1) && (FatorBalanceamento_Nodo(nodo->right) > 0))
    {
        nodo->right = rotDIR(nodo->right);
        return rotESQ(nodo);
    }

    return nodo;
 }

 void in_order (tree_Nodo *nodo, int height) {
    if(nodo != NULL) {
        in_order (nodo->left,height);
        printf("%d,%d\n",nodo->key,height - nodo->height);
        in_order (nodo->right,height);
        }

}
 