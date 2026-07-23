#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct NoArvore {
    int dado;
    struct NoArvore *esquerda;
    struct NoArvore *direita;
} NoArvore;

NoArvore* criar_no(int valor) {
    NoArvore *novo = (NoArvore*) malloc(sizeof(NoArvore));
    if (novo != NULL) {
        novo->dado = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

NoArvore* inserir(NoArvore *raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor < raiz->dado) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->dado) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

void destruir_arvore(NoArvore *raiz) {
    if (raiz != NULL) {
        destruir_arvore(raiz->esquerda);
        destruir_arvore(raiz->direita);
        free(raiz);
    }
}

int buscar_maior(NoArvore *raiz) {
    if (raiz == NULL) {
        return INT_MIN; 
    }
    
    while (raiz->direita != NULL) {
        raiz = raiz->direita;
    }
    
    return raiz->dado; 
}

int altura(NoArvore *raiz) {
    if (raiz == NULL) {
        return -1;
    }

    int alt_esq = altura(raiz->esquerda);
    int alt_dir = altura(raiz->direita);

    if (alt_esq > alt_dir) {
        return alt_esq + 1;
    } else {
        return alt_dir + 1;
    }
}