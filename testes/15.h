typedef struct Cell Cell;
typedef struct FilaE FilaE;

Cell* criar_celula(int key, int peso);

FilaE* criar_filaE();

int filaE_vazia(FilaE* f);

void enfileirar(int key, FilaE* f);

int desenfileirar(FilaE* f);

void imprimir_fila(FilaE* f);

int liberar_filaE(FilaE* f);

typedef struct Lista Lista;

Lista* criar_lista();

int lista_vazia(Lista* l);

int procurar(int key, Lista* l);

void inserir_na_lista(int key, int peso, Lista* l);

int remover_na_lista(int key, Lista* l);

void imprimir_lista(Lista* l);

int liberar_lista(Lista* l);

typedef struct GrafoLA GrafoLA;

static Lista** iniciar_LA(int n);

static int valida_vertice(GrafoLA* G, int v);

GrafoLA* iniciar_grafoLA(int v, int a);

int aresta_existeLA(GrafoLA* G, int v1, int v2);

void inserir_arestaLA(GrafoLA* G, int v1, int v2, int peso);

void remover_arestaLA(GrafoLA* G, int v1, int v2);

void imprimir_grafoLA(GrafoLA* G);

void liberar_grafoLA(GrafoLA* G);

