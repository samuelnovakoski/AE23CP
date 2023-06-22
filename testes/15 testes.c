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

int esta_na_fila(int key, FilaE* f) {
    Cell *aux;

    if (!filaE_vazia(f)) {
        aux = f->inicio;

        while (aux != NULL) {
            if (aux->key == key)
                return 1;

            aux = aux->next;
        }
    }

    return 0;
}

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
        inserir_na_lista(v1, peso, G->adj[v2]);
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


int extract_min(FilaE* f, GrafoLA* G) {
    int min = desenfileirar(f);
    int min_key = G->adj[min]->head->key;
    Cell* current = G->adj[min]->head->next;
    
    while (current != NULL) {
        int key = current->key;
        if (key < min_key && procurar(key, f->inicio) != 1) {
            min = key;
            min_key = G->adj[key]->head->key;
        }
        current = current->next;
    }
    
    return min;
}


void prim(GrafoLA* G) {
    int V = G->V; // Numero de vertices do grafo
    int parent[V]; // Array para armazenar os pais de cada vertice na arvore geradora minima
    int key[V]; // Array para armazenar as chaves (pesos) dos vertices
    int in_tree[V]; // Array para marcar os vertices incluidos na arvore geradora minima
    
    // Inicializacao dos arrays
    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        key[i] = INT_MAX;
        in_tree[i] = 0;
    }
    
    // O vertice de partida e o 0
    key[0] = 0;
    
    FilaE* fila = criar_filaE(); // Fila de prioridade para os vertices
    
    // Enfileira todos os vertices
    for (int i = 0; i < V; i++) {
        enfileirar(i, fila);
    }
    
    while (!filaE_vazia(fila)) {
        int u = extract_min(fila, G); // Extrai o vertice com a menor chave
        
        in_tree[u] = 1; // Marca o vertice como incluido na arvore geradora minima
        
        // Percorre os vertices adjacentes a u
        Cell* current = G->adj[u]->head->next;
        while (current != NULL) {
            int v = current->key;
            int peso = current->peso;
            
            // Verifica se v ainda nao foi incluido na arvore geradora minima e se o peso da aresta e menor que a chave atual de v
            if (in_tree[v] == 0 && peso < key[v]) {
                parent[v] = u; // Atualiza o pai de v
                key[v] = peso; // Atualiza a chave de v
            }
            
            current = current->next;
        }
    }
    
    // Imprime a arvore geradora minima
    printf("0: -\n");
    for (int i = 1; i < V; i++) {
        if (parent[i] > 0) {
            printf("%d: %d\n", i, parent[i]);
        } else {
            printf("%d: -\n", i);
        }
    }
    
    liberar_filaE(fila); // Libera a memoria alocada para a fila
}







int main() {
    int V, A;
    scanf("%d", &V); // Le o numero de vertices
    scanf("%d", &A); // Le o numero de arestas
    
    GrafoLA* G = iniciar_grafoLA(V, A); // Cria o grafo
    
    for (int i = 0; i < A; i++) {
        int v1, v2, peso;
        scanf("%d %d %d", &v1, &v2, &peso); // Le os vertices e o peso da aresta
        inserir_arestaLA(G, v1, v2, peso); // Insere a aresta no grafo
    }
    
    prim(G); // Chama o algoritmo de Prim
    
    liberar_grafoLA(G); // Libera a memoria alocada para o grafo
    
    return 0;
}

