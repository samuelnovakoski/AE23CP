#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

typedef struct Cell Cell;
struct Cell {
    int item;
    Cell* next;
};

typedef struct FilaE FilaE;
struct FilaE {
    Cell* inicio;
    Cell* fim;
};

Cell* criar_celula(int key) {
    Cell* c = (Cell*)malloc(sizeof(Cell));
    c->item = key;
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

void enfileirar(int key, FilaE** f) {
    Cell* aux;
    if (*f == NULL)
        *f = criar_filaE();
    aux = criar_celula(key);
    if ((*f)->inicio == NULL)
        (*f)->inicio = (*f)->fim = aux;
    else {
        (*f)->fim->next = aux;
        (*f)->fim = (*f)->fim->next;
    }
}

int desenfileirar(FilaE* f) {
    Cell* aux;
    int item = INT_MIN;
    if (!filaE_vazia(f)) {
        aux = f->inicio;
        f->inicio = aux->next;
        item = aux->item;
        free(aux);
    }
    return item;
}

void imprimir_fila(FilaE* f) {
    Cell* aux;
    if (!filaE_vazia(f)) {
        aux = f->inicio;
        while (aux != NULL) {
            printf("%d ", aux->item);
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
        while ((aux != NULL) && (key < aux->item))
            aux = aux->next;
    }
    if ((aux != NULL) && (key == aux->item))
        return 1;
    else
        return 0;
}

void inserir_na_lista(int key, Lista** l) {
    Cell* auxA, * auxP;
    Cell* c;
    if (lista_vazia(*l)) {
        if (*l == NULL)
            *l = criar_lista();
        (*l)->head = criar_celula(key);
    }
    else {
        c = criar_celula(key);
        if ((*l)->head->item >= key) {
            c->next = (*l)->head;
            (*l)->head = c;
        }
        else {
            auxA = (*l)->head;
            auxP = auxA;
            while ((auxP != NULL) && (auxP->item < key)) {
                auxA = auxP;
                auxP = auxP->next;
            }
            auxA->next = c;
            c->next = auxP;
        }
    }
}

int remover_na_lista(int key, Lista** l) {
    Cell* auxA, * auxP;
    if (!lista_vazia(*l)) {
        auxA = (*l)->head;
        if (auxA->item == key)
            (*l)->head = (*l)->head->next;
        else {
            auxP = auxA;
            while ((auxA != NULL) && (key < auxA->item)) {
                auxP = auxA;
                auxA = auxA->next;
            }
            if (auxA->item == key)
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
            printf("%d", aux->item);
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
    int* pi, * cor, * d, * f;
    Lista** adj;
};

static Lista** iniciar_LA(int n) {
    int i;
    Lista** adj = (Lista**)malloc(n * sizeof(Lista*));
    for (i = 0; i < n; i++)
        adj[i] = criar_lista();
    return adj;
}

static int valida_vertice(GrafoLA* G, int v) {
    return (v >= 0) && (v < G->V);
}

GrafoLA* iniciar_grafoLA(int v) {
    GrafoLA* G = (GrafoLA*)malloc(sizeof(GrafoLA));
    G->V = v;
    G->A = 0;
    G->pi = (int*)malloc(v * sizeof(int));
    G->cor = (int*)malloc(v * sizeof(int));
    G->d = (int*)malloc(v * sizeof(int));
    G->f = (int*)malloc(v * sizeof(int));
    G->adj = iniciar_LA(v);
    return G;
}

int aresta_existeLA(GrafoLA* G, int v1, int v2) {
    if (G != NULL && valida_vertice(G, v1) && valida_vertice(G, v2)) {
        return procurar(v2, G->adj[v1]);
    }
    return 0;
}

void inserir_arestaLA(GrafoLA* G, int v1, int v2) {
    if (G != NULL && valida_vertice(G, v1) && valida_vertice(G, v2) && !aresta_existeLA(G, v1, v2)) {
        inserir_na_lista(v2, &(G->adj[v1]));
        G->A++;
    }
}

void busca_profundidade(GrafoLA* G, int u) {
    Cell* aux;
    int v;
    G->cor[u] = 1;
    aux = G->adj[u]->head;
    while (aux != NULL) {
        v = aux->item;
        if (G->cor[v] == 0) {
            G->pi[v] = u;
            busca_profundidade(G, v);
        }
        aux = aux->next;
    }
    G->cor[u] = 2;
}

void dfs(GrafoLA* G) {
    int i;
    for (i = 0; i < G->V; i++) {
        G->cor[i] = 0;
        G->pi[i] = -1;
    }
    for (i = 0; i < G->V; i++) {
        if (G->cor[i] == 0)
            busca_profundidade(G, i);
    }
}

void imprimir(GrafoLA *G){
    int v;

    printf("v d f p\n");

    for(v = 0; v < G->V; v++){
        printf("%d %d %d ", v, G->d[v], G->f[v]);

        if(G->pi[v] >= 0)
            printf("%d\n", G->pi[v]);
        else
            printf("-\n");
    }
}

void liberarGLA(GrafoLA* G){
    int i;

    if (G != NULL){
        for (i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G);
    }
}

int main(){
    int i, v, x;
    GrafoLA *G;

    scanf("%d",&v);

    G = iniciar_grafoLA(v);

    for(i = 0; i < v; i++){
        do{
            scanf("%d", &x);
            if(x != -1)
                inserir_arestaLA(G, i, x);
        }while(x != -1);
    }

    dfs(G);

    imprimir(G);

    liberarGLA(G);

    return 0;
}