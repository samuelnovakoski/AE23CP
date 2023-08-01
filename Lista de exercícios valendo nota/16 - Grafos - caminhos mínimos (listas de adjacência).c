#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Cell Cell;

struct Cell {
    int key;
    int peso;
    Cell* next;
};

typedef struct FilaE FilaE;

struct FilaE {
    Cell* inicio;
    Cell* fim;
};

Cell* criar_celula(int key, int peso) {
    Cell* c = (Cell*)malloc(sizeof(Cell));
    c->key = key;
    c->peso = peso;
    c->next = NULL;
    return c;
}

FilaE* criar_filaE() {
    FilaE* f = (FilaE*)malloc(sizeof(FilaE));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int filaE_vazia(FilaE* f) {
    return (f == NULL) || (f->inicio == NULL);
}

void enfileirar(int key, FilaE* f) {
    Cell* aux;
    if (f == NULL)
        f = criar_filaE();
    aux = criar_celula(key, 0);
    if (f->inicio == NULL)
        f->inicio = f->fim = aux;
    else {
        f->fim->next = aux;
        f->fim = f->fim->next;
    }
}

int desenfileirar(FilaE* f) {
    Cell* aux;
    int key = INT_MIN;
    if (!filaE_vazia(f)) {
        aux = f->inicio;
        f->inicio = aux->next;
        key = aux->key;
        free(aux);
    }
    return key;
}

void imprimir_fila(FilaE* f) {
    Cell* aux;
    if (!filaE_vazia(f)) {
        aux = f->inicio;
        while (aux != NULL) {
            printf("%d ", aux->key);
            aux = aux->next;
        }
        printf("\n");
    }
}

int liberar_filaE(FilaE* f) {
    if (!filaE_vazia(f)) {
        while (f->inicio != NULL)
            desenfileirar(f);
        free(f);
        return 1;
    }
    return 0;
}

typedef struct Lista Lista;

struct Lista {
    Cell* head;
};

Lista* criar_lista() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->head = NULL;
    return l;
}

int lista_vazia(Lista* l) {
    return (l == NULL) || (l->head == NULL);
}

int procurar(int key, Lista* l) {
    Cell* aux = NULL;
    if (l != NULL) {
        aux = l->head;
        while ((aux != NULL) && (key < aux->key))
            aux = aux->next;
    }
    if ((aux != NULL) && (key == aux->key))
        return 1;
    else
        return 0;
}

void inserir_na_lista(int key, int peso, Lista* l) {
    Cell* auxA, * auxP;
    Cell* c;
    if (lista_vazia(l)) {
        if (l == NULL)
            l = criar_lista();
        l->head = criar_celula(key, peso);
    }
    else {
        c = criar_celula(key, peso);
        if (l->head->key >= key) {
            c->next = l->head;
            l->head = c;
        }
        else {
            auxA = l->head;
            auxP = auxA;
            while ((auxP != NULL) && (auxP->key < key)) {
                auxA = auxP;
                auxP = auxP->next;
            }
            auxA->next = c;
            c->next = auxP;
        }
    }
}

int remover_na_lista(int key, Lista* l) {
    Cell* auxA, * auxP;
    if (!lista_vazia(l)) {
        auxA = l->head;
        if (auxA->key == key)
            l->head = l->head->next;
        else {
            auxP = auxA;
            while ((auxA != NULL) && (key < auxA->key)) {
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

void imprimir_lista(Lista* l) {
    Cell* aux;
    if (!lista_vazia(l)) {
        aux = l->head;
        while (aux != NULL) {
            printf("%d", aux->key);
            aux = aux->next;
        }
        printf("\n");
    }
}

int liberar_lista(Lista* l) {
    Cell* aux;
    if ((l != NULL) && !lista_vazia(l)) {
        while (l->head != NULL) {
            aux = l->head;
            l->head = aux->next;
            free(aux);
        }
        free(l);
        return 1;
    }
    return 0;
}

typedef struct GrafoLA GrafoLA;

struct GrafoLA {
    int V, A;
    Lista** adj;
    int* nafila;
    int* pai;
    int* key;
};

static Lista** iniciar_LA(int n) {
    int i;
    Lista** adj = (Lista**)malloc(n * sizeof(Lista*));
    for (i = 0; i < n; i++)
        adj[i] = criar_lista();
    return adj;
}

GrafoLA* iniciar_grafoLA(int v, int a) {
    GrafoLA* G = (GrafoLA*)malloc(sizeof(GrafoLA));
    G->V = v;
    G->A = a;
    G->adj = iniciar_LA(G->V);
    G->nafila = (int*)malloc(sizeof(int) * v);
    G->pai = (int*)malloc(sizeof(int) * v);
    G->key = (int*)malloc(sizeof(int) * v);
    return G;
}

int aresta_existeLA(GrafoLA* G, int v1, int v2) {
    if (G != NULL)
        return procurar(v2, G->adj[v1]);
    return 0;
}

void inserir_arestaLA(GrafoLA* G, int v1, int v2, int peso) {
    if (!aresta_existeLA(G, v1, v2)) {
        inserir_na_lista(v2, peso, G->adj[v1]);
        G->A++;
    }
}

void remover_arestaLA(GrafoLA* G, int v1, int v2) {
    if (aresta_existeLA(G, v1, v2)) {
        remover_na_lista(v2, G->adj[v1]);
        G->A--;
    }
}

void imprimir_grafoLA(GrafoLA* G) {
    int i;
    for (i = 0; i < G->V; i++) {
        printf("%d:", i);
        imprimir_lista(G->adj[i]);
    }
}

void liberar_grafoLA(GrafoLA* G) {
    int i;
    for (i = 0; i < G->V; i++)
        liberar_lista(G->adj[i]);
    free(G->adj);
    free(G->nafila);
    free(G->pai);
    free(G->key);
    free(G);
}


int extract_min(FilaE *f, GrafoLA *G){
    int vM;
    Cell *aux, *auxM;

    auxM = f->inicio;
    aux = auxM->next;

    while(aux != NULL){
        if(G->key[aux->key] < G->key[auxM->key])
            auxM = aux;
        
        aux = aux->next;
    }

    if(auxM != f->inicio){
        vM = f->inicio->key;
        f->inicio->key = auxM->key;
        auxM->key = vM;
    }

    return desenfileirar(f);
}

void Dijksra(GrafoLA *G){
    int i, v, u, peso;
    Cell *aux;
    FilaE *f = criar_filaE();

    for(i = 0; i < G->V; i ++){
        G->pai[i] = -1;
        G->key[i] = INT_MAX;
        G->nafila[i] = 0;
        enfileirar(i, f);
    }

    G->key[0] = 0;

    while(!filaE_vazia(f)){
        u = extract_min(f, G);

        G->nafila[u] = 1;

        aux = G->adj[u]->head;
        
        while(aux != NULL){
            v = aux->key;
            peso = aux->peso;

            if((G->nafila[v] == 0) && (peso + G->key[u] < G->key[v])){
                G->pai[v] = u;
                G->key[v] = peso + G->key[u];
            }

            aux = aux->next;
        }
    }

    liberar_filaE(f);

    for(v = 0; v < G->V; v++){
        printf("%d: ", v);

        if(G->pai[v] < 0)
            printf("-\n");
        else
            printf("%d\n", G->pai[v]);
    }
}

int main() {
    int i, V, A, v1, v2, peso;
    GrafoLA *G;

    scanf("%d %d", &V, &A); 

    
    G = iniciar_grafoLA(V, A); 
    
    for (i = 0; i < A; i++) {
        scanf("%d %d %d", &v1, &v2, &peso); 
        inserir_arestaLA(G, v1, v2, peso); 
    }
    
    Dijksra(G); 
    
    liberar_grafoLA(G);
    
    return 0;
}