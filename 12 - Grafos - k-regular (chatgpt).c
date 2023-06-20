#include <stdio.h>
#include <stdlib.h>

typedef struct Cell {
    int key;
    struct Cell* next;
} Cell;

typedef struct Lista {
    Cell* head;
} Lista;

typedef struct GrafoLA {
    int V; // numero de vertices
    int A; // numero de arestas
    Lista** adj; // lista de adjacencias
} GrafoLA;

// Funcao para criar uma nova celula na lista de adjacencias
Cell* criarCelula(int v) {
    Cell* nova = (Cell*)malloc(sizeof(Cell));
    nova->key = v;
    nova->next = NULL;
    return nova;
}

// Funcao para criar uma nova lista
Lista* criarLista() {
    Lista* novaLista = (Lista*)malloc(sizeof(Lista));
    novaLista->head = NULL;
    return novaLista;
}

// Funcao para adicionar uma aresta entre os vertices v e w
void adicionarAresta(GrafoLA* grafo, int v, int w) {
    Cell* nova = criarCelula(w);
    nova->next = grafo->adj[v]->head;
    grafo->adj[v]->head = nova;
    grafo->A++;
}

// Funcao para criar um grafo com V vertices
GrafoLA* criarGrafo(int V) {
    GrafoLA* grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
    grafo->V = V;
    grafo->A = 0;
    grafo->adj = (Lista**)malloc(V * sizeof(Lista*));

    int i;
    for (i = 0; i < V; i++) {
        grafo->adj[i] = criarLista();
    }

    return grafo;
}

// Funcao para verificar se o grafo e k-regular
int verificarRegularidade(GrafoLA* grafo) {
    int i, k;
    k = -1;

    for (i = 0; i < grafo->V; i++) {
        Cell* atual = grafo->adj[i]->head;
        int count = 0;

        while (atual != NULL) {
            count++;
            atual = atual->next;
        }

        if (k == -1)
            k = count;
        else if (k != count)
            return 0;
    }

    return k;
}

// Funcao para liberar a memoria alocada pelo grafo
void liberarGrafo(GrafoLA* grafo) {
    int i;

    for (i = 0; i < grafo->V; i++) {
        Cell* atual = grafo->adj[i]->head;

        while (atual != NULL) {
            Cell* temp = atual;
            atual = atual->next;
            free(temp);
        }

        free(grafo->adj[i]);
    }

    free(grafo->adj);
    free(grafo);
}

int lista_vazia(Lista *l){
    return (l == NULL) || (l->head == NULL);
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

void imprimir_arestasLA(GrafoLA* G){
    int i;

    if (G != NULL)
        for (i = 0; i < G->V; i++)
            imprimir_lista(G->adj[i]);
}

int main() {
    int V, i, v;
    scanf("%d", &V);

    GrafoLA* grafo = criarGrafo(V);

    for (i = 0; i < V; i++) {
        while (1) {
            scanf("%d", &v);

            if (v == -1)
                break;

            adicionarAresta(grafo, i, v);
        }
    }

    int k = verificarRegularidade(grafo);

    if (k != 0)
        printf("grafo k-regular com k=%d\n", k);
    else
        printf("grafo nao k-regular\n");
    
    imprimir_arestasLA(grafo);

    liberarGrafo(grafo);

    return 0;
}
