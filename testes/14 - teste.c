dfs(G)
    para cada u em V[G] faça
        cor[u] = branco
        pai[u] = NIL
    tempo = 0
    
    para cada u em V[G] faça
        se cor[u] == branco
            então DFS-visit(u)

DFS-visit(u)
    cor[u] = cinza
    tempo = tempo + 1
    d[u] = tempo

    para cada v em Adj[u] faça
        se cor[v] == braco
            então pai[v] = u
            DFS-visit(v)
    
    cor[u] = preto
    f[u] = tempo = tempo + 1




void DFS_visit(GrafoLA* G, int u) {
    G->cor[u] = 1; // marca o vértice como cinza
    G->tempo++;
    G->d[u] = G->tempo;

    Cell *vCell = G->adj[u]->head;

    while (vCell != NULL) {
        int v = vCell->key;

        if (G->cor[v] == 0) {
            G->pi[v] = u;
            DFS_visit(G, v);
        }

        vCell = vCell->next;
    }

    G->cor[u] = 2; // marca o vértice como preto
    G->tempo++;
    G->f[u] = G->tempo;
}

void dfs(GrafoLA* G) {
    for (int i = 0; i < G->V; i++) {
        G->cor[i] = 0; // todos os vértices são brancos no início
        G->pi[i] = -1; // todos os pais são nulos no início
    }
    G->tempo = 0; // reinicia o contador de tempo

    for (int i = 0; i < G->V; i++) {
        if (G->cor[i] == 0) {
            DFS_visit(G, i);
        }
    }
}
