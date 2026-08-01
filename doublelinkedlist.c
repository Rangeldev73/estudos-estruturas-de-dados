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

void inserir_inicio(NoDuplo **head, int valor) {
    NoDuplo *novo = (NoDuplo*) malloc(sizeof(NoDuplo));
    if (novo == NULL) return;
    
    novo->dado = valor;
    novo->proximo = *head;
    novo->anterior = NULL;

    if (*head != NULL) {
        (*head)->anterior = novo;
    }
    
    *head = novo;
}

void imprimir_lista(NoDuplo *head) {
    if (head == NULL) {
        printf("Lista Vazia!\n");
        return;
    }

    printf("Frente -> Trás: ");
    NoDuplo *ultimo = NULL;
    NoDuplo *atual = head;
    while (atual != NULL) {
        printf("[%d] <-> ", atual->dado);
        ultimo = atual;
        atual = atual->proximo;
    }
    printf("NULL\n");

    printf("Trás -> Frente: ");
    atual = ultimo;
    while (atual != NULL) {
        printf("[%d] <-> ", atual->dado);
        atual = atual->anterior;
    }
    printf("NULL\n");
}

int main() {
    NoDuplo *head = NULL;

    printf("====================================================\n");
    printf("   TESTE DE REMOCAO EM LISTA DUPLAMENTE ENCADEADA   \n");
    printf("====================================================\n\n");

    printf("--- 1. Inserindo elementos: 10, 20, 30, 40 ---\n");
    inserir_inicio(&head, 40);
    inserir_inicio(&head, 30);
    inserir_inicio(&head, 20);
    inserir_inicio(&head, 10);

    imprimir_lista(head);

    printf("\n--- 2. Removendo o primeiro elemento (10) ---\n");
    if (remover_elemento_duplo(&head, 10)) {
        printf(" -> Elemento 10 removido com sucesso!\n");
    }
    imprimir_lista(head);

    printf("\n--- 3. Removendo elemento do meio (30) ---\n");
    if (remover_elemento_duplo(&head, 30)) {
        printf(" -> Elemento 30 removido com sucesso!\n");
    }
    imprimir_lista(head);

    printf("\n--- 4. Tentando remover elemento inexistente (99) ---\n");
    if (!remover_elemento_duplo(&head, 99)) {
        printf(" -> Elemento 99 nao encontrado (comportamento correto!).\n");
    }

    printf("\n--- 5. Liberando memoria da lista ---\n");
    while (head != NULL) {
        remover_elemento_duplo(&head, head->dado);
    }
    printf(" -> Lista esvaziada e memoria liberada!\n");

    return 0;
}