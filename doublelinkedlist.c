#include <stdio.h>
#include <stdlib.h>

typedef struct NoDuplo {
    int dado;
    struct NoDuplo *proximo;
    struct NoDuplo *anterior; 
} NoDuplo;

int remover_elemento_duplo(NoDuplo **head, int valor) {
    if((*head==NULL)) return 0;
    if ((*head)->dado == valor) {
        NoDuplo *aux = *head; 
        *head = (*head)->proximo; 
        if (*head != NULL) {
            (*head)->anterior = NULL; 
        }
        free(aux); 
        return 1;
    }
    NoDuplo *atual = (*head)->proximo;
    while (atual != NULL && atual->dado != valor) {
        atual = atual->proximo;
    }
    if (atual == NULL) return 0;
    atual->anterior->proximo = atual->proximo;
    if (atual->proximo != NULL) {
    atual->proximo->anterior = atual->anterior;
    }
    free(atual);
    return 1;
}