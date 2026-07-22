#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 10

typedef struct Elemento {
    char *chave;
    int valor;
    struct Elemento *proximo;
} Elemento;

typedef struct {
    Elemento **buckets;
} TabelaHash;

unsigned int funcao_hash(const char *chave) {
    unsigned long hash = 5381;
    int c;
    while ((c = *chave++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TAMANHO_TABELA;
}

TabelaHash* criar_tabela() {
    TabelaHash *tabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    if (tabela == NULL) return NULL;
    tabela->buckets = (Elemento**) calloc(TAMANHO_TABELA, sizeof(Elemento*));
    if (tabela->buckets == NULL) {
        free(tabela);
        return NULL;
    }
    return tabela;
}

void inserir(TabelaHash *tabela, const char *chave, int valor) {
    unsigned int indice = funcao_hash(chave);
    Elemento *atual = tabela->buckets[indice];

    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            atual->valor = valor;
            return;
        }
        atual = atual->proximo;
    }

    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    if (novo == NULL) return;
    novo->chave = strdup(chave); 
    novo->valor = valor;
    novo->proximo = tabela->buckets[indice];
    tabela->buckets[indice] = novo;
}

int buscar(TabelaHash *tabela, const char *chave, int *valor_encontrado) {
    unsigned int indice = funcao_hash(chave);
    Elemento *atual = tabela->buckets[indice];

    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            *valor_encontrado = atual->valor;
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void destruir_tabela(TabelaHash *tabela) {
    if (tabela == NULL) return;
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Elemento *atual = tabela->buckets[i];
        while (atual != NULL) {
            Elemento *aux = atual;
            atual = atual->proximo;
            free(aux->chave);
            free(aux);
        }
    }
    free(tabela->buckets);
    free(tabela);
}
