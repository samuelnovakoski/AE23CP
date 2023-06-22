#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct GrafoLA GrafoLA;
typedef struct Cell Cell;
typedef struct Lista Lista;

struct GrafoLA{
   int V; 
   int A; 
   Lista **adj; 
};

struct Cell{
    int key;
    Cell *next;
};

struct Lista{
    Cell *head;
};

// ======================= LISTA =================

Lista* criar_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));

    l->head = NULL;

    return l;
}

Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;

    c->next = NULL;

    return c;
}

int lista_vazia(Lista *l){
    return (l == NULL) || (l->head == NULL);
}

int procurar(int key, Lista *l){
    Cell *aux = NULL;

    if (l != NULL){
        aux = l->head;

        while ((aux != NULL) && (key < aux->key))
            aux = aux->next;
    }

    if ((aux != NULL) && (key == aux->key))
        return 1;
    else
        return 0;
}

void inserir_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;
    Cell* c;

    if (lista_vazia(l)){
        if (l == NULL)
            l = criar_lista();

        l->head = criar_celula(key);
    }else{
        c = criar_celula(key);

        if (l->head->key >= key){
           c->next = l->head;

           l->head = c;
        }else{
            auxA = l->head;
            auxP = auxA;

            while ((auxP != NULL) && (auxP->key < key)){
                auxA = auxP;
                auxP = auxP->next;
            }

            auxA->next = c;
            c->next = auxP;
        }
    }
}

int remover_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;

    if (!lista_vazia(l)){
        auxA = l->head;

        if(auxA->key == key)
            l->head = l->head->next;
        else{
            auxP = auxA;

            while((auxA != NULL) && (key < auxA->key)){
                auxP = auxA;
                auxA = auxA->next;
            }

            if (auxA->key == key)
                auxP->next = auxA->next;
            else
                auxA = NULL;
        }

        if (auxA != NULL)
            free(auxA);

        return 1;
    }

        return 0;
}

void imprimir_lista(Lista *l){
    Cell *aux;

    if (!lista_vazia(l)){
        aux = l->head;

        while (aux != NULL){
            printf("%d ", aux->key);

            aux = aux->next;
        }


        printf("\n");
    }
}

int liberar_lista(Lista *l){
    Cell *aux;

    if ((l != NULL) && !lista_vazia(l)){

        while(l->head != NULL){
            aux = l->head;

            l->head = aux->next;

            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}

// ====================== GRAFOLA =====================

static Lista** iniciar_LA(int n){
    int i;
    Lista **adj = (Lista**) malloc(n * sizeof(Lista*));

    for (i = 0; i < n; i++)
        adj[i] = criar_lista();

    return adj;
}

GrafoLA* iniciar_grafoLA(int v){
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = 0;
    G->adj = iniciar_LA(G->V);

    return G;
}

int aresta_existeLA(GrafoLA* G, int v1, int v2){
    if (G!= NULL)
        return procurar(v2, G->adj[v1]);

    return 0;
}

void inserir_arestaLA(GrafoLA* G, int v1, int v2){
    if (!aresta_existeLA(G, v1, v2)){
        inserir_na_lista(v2, G->adj[v1]);
        inserir_na_lista(v1, G->adj[v2]);
        G->A++;
    }
}

void remover_arestaLA(GrafoLA* G, int v1, int v2){
    if (aresta_existeLA(G, v1, v2)){
        remover_na_lista(v2, G->adj[v1]);
        remover_na_lista(v1, G->adj[v2]);
        G->A--;

    }
}

void imprimir_arestasLA(GrafoLA* G){
    int i;

    if (G != NULL)
        for (i = 0; i < G->V; i++)
            imprimir_lista(G->adj[i]);
}

void liberarGLA(GrafoLA* G){
    int i;

    if (G != NULL){
        for (i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G);
    }
}


int grau(GrafoLA *G){
    int i, c, k = -1;
    Cell *aux = NULL;

    for(i = 0; i < G->V; i++){
        aux = G->adj[i];
        c = 0;

        while(aux != NULL){
            c++;
            aux = aux->next;
        }

        if(k == -1)
            k = c;
        else if(k != c)
            return 0;
    }

    return k;
}

int main() {
    int v, i, x, k;
    GrafoLA *G;

    scanf("%d", &v);

    G = iniciar_grafoLA(v);

    for(i = 0; i < v; i++){
        do{
            scanf("%d", &x);
            if(x != -1)
                inserir_arestaLA(G, i, x);
        }while(x != -1);
    }

    k = grau(G);

    if(k != 0)
        printf("grafo k-regular com k=%d", k);
    else
        printf("grafo nao k-regular";)

    liberarGLA(G);

    
    return 0;
}
