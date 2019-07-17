#ifndef __LIBAVL__
#define __LIBAVL__


typedef struct tree_Nodo {
    int key;
    struct tree_Nodo *left;
    struct tree_Nodo *right;
    int height;
}  tree_Nodo ;

int Altura_Nodo (tree_Nodo *v);

tree_Nodo *recal (tree_Nodo *v);

int FatorBalanceamento_Nodo (tree_Nodo *v);

tree_Nodo *CriaNodo (int x);

tree_Nodo *InicializaNodo (int x);

int valorMax(int x, int y);

tree_Nodo *Busca (int x, tree_Nodo *v);

tree_Nodo *maiornodo(tree_Nodo *v);

int Calculaaltura(tree_Nodo *v);

tree_Nodo *rotDIR (tree_Nodo *v);

tree_Nodo *rotESQ (tree_Nodo *v);

tree_Nodo *Inclui (tree_Nodo *v, int x);

tree_Nodo *Remove (tree_Nodo *v, int x);

void in_order (tree_Nodo *v, int x);

#endif
