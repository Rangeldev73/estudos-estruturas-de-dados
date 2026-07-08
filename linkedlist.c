#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;           
    struct No *proximo; 
} No;

int remover_elemento_lista(No **head, int valor) {
    if((*head==NULL)) return 0;
    if ((*head)->dado==valor){
        No *aux=*head;
        *head=(*head)->proximo;
        free(aux);
        return 1;
    }
    No *anterior=*head;       
    No *atual=(*head)->proximo;
    while(atual!=NULL&&atual->dado!=valor){
        anterior=atual;       
        atual=atual->proximo; 
    }
    if (atual!=NULL) { 
        anterior->proximo=atual->proximo; 
        free(atual); 
        return 1; 
    }
    return 0;
}