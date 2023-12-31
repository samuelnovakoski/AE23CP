#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node Node;

struct Node{
    int item;
    struct Node *left;
    struct Node *right;
};

Node* criar(int item){
    Node * tree = (Node *) malloc(sizeof(Node));
    
    tree->item = item;
    tree->left = NULL;
    tree->right = NULL;
        
    return tree;
}

Node* pesquisar(int item, Node* tree){
    if (tree != NULL){
        if (item == tree->item)
            return tree;
        else if (item < tree->item)
            return pesquisar(item, tree->left);
        else
            return pesquisar(item, tree->right);
    }else
        return NULL;
}

int min(Node* tree){
    Node* aux = tree;
    
    if (aux != NULL){
        while (aux->left != NULL)
            aux = aux->left;
        
        return aux->item;
    }
    
    return INT_MIN;
}

int max(Node* tree){
    Node* aux = tree;
    
    if (aux != NULL){
        while (aux->right != NULL)
            aux = aux->right;
        
        return aux->item;
    }
    
    return INT_MAX;
}

Node* inserir(int item, Node* tree){
    if (tree == NULL)
        tree = criar(item);
    else if (item < tree->item)
        tree->left = inserir(item, tree->left);
    else if (item > tree->item)
        tree->right = inserir(item, tree->right);
        
    return tree;
}

void imprimirInfix(Node* tree){
    if (tree != NULL){
        imprimirInfix(tree->left);
        printf("\n%i", tree->item);
        imprimirInfix(tree->right);
    }
}

void imprimirPrefix(Node* tree){
    if (tree != NULL){
        printf("%i ", tree->item);
        imprimirPrefix(tree->left);
        imprimirPrefix(tree->right);
    }
}

void imprimirPosfix(Node* tree){
    if (tree != NULL){
        imprimirPosfix(tree->left);
        imprimirPosfix(tree->right);
        printf("\n%i", tree->item);
    }
}

void liberar_arvore(Node* tree){
    if (tree != NULL){
        liberar_arvore(tree->left);
        liberar_arvore(tree->right);
        free(tree);
    }
}

Node* remover(int item, Node* tree){
    Node *aux, *auxP, *auxF;
    int x;

    if(tree == NULL)
        return 0;

    if(item < tree->item)
        tree->left = remover(item, tree->left);
    else if(item > tree->item)
        tree->right = remover(item, tree->right);
    else{
         if(tree->left == NULL){
            aux = tree->right;
            return aux;
        } else if(tree->right == NULL){
            aux = tree->left;
            return aux;
        } else {
            auxF = tree->right;
            auxP = tree;
            x = 1;

            while(auxF->left!= NULL){
                auxP = auxF;
                auxF = auxF->left;
                x = 0;
            }
            auxP->item = auxF->item;

            if(x == 0)
                auxP->left = auxF->right;
            else
                auxP->right = auxF->right;

            free(auxF);
        }
    }
    return tree;
}

Node* remover_impares(Node *tree){
    while((tree != NULL) && (tree->item % 2 != 0))
        tree = remover(tree->item, tree);
    
    if(tree != NULL){
        tree->left = remover_impares(tree->left);
        tree->right = remover_impares(tree->right);
    }
    return tree;
}

int main(){
    int n, item;
    Node *tree = NULL;

    scanf("%d", &n);

    while(n > 0){
        scanf("%d", &item);

        tree = inserir(item, tree);

        n--;
    }

    tree = remover_impares(tree);

    imprimirPrefix(tree);

    liberar_arvore(tree);

    return 0;
}