#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

typedef struct {
    No *inicio; 
    No *fim;    
} Fila;

Fila* criar_fila() {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
    }
    return f;
}

int esta_vazia(Fila *f) {
    return (f->inicio == NULL);
}

void enqueue(Fila *f, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocação: Heap cheia!\n");
        return;
    }
    
    novo->dado = valor;
    novo->proximo = NULL; 
    
    if (esta_vazia(f)) {
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }
    
    f->fim = novo;
}

int dequeue(Fila *f) {
    if (esta_vazia(f)) {
        printf("Fila Vazia! Underflow detectado.\n");
        return INT_MIN;
    }
    
    No *aux = f->inicio;       
    int valor = aux->dado;     
    
    f->inicio = aux->proximo;  
    
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(aux); 
    return valor;
}

int peek(Fila *f) {
    if (esta_vazia(f)) {
        return INT_MIN;
    }
    return f->inicio->dado;
}

void destruir_fila(Fila *f) {
    if (f != NULL) {
        while (!esta_vazia(f)) {
            dequeue(f); 
        }
        free(f); 
    }
}

void simular_atendimento(Fila *preferencial, Fila *convencional){
    int cont_preferencial=0; 

    while (!esta_vazia(preferencial) || !esta_vazia(convencional)) {
        if (!esta_vazia(preferencial) && (cont_preferencial < 2 || esta_vazia(convencional))) {
            int cliente = dequeue(preferencial);
            printf("Atendimento Preferencial: %d\n", cliente);
            cont_preferencial++;
        } else {
            int cliente = dequeue(convencional);
            printf("Atendimento Convencional: %d\n", cliente);
            cont_preferencial = 0;
        }
    }

    destruir_fila(preferencial);
    destruir_fila(convencional);
}

void imprimir_fila(Fila *f, const char *nome_fila) {
    printf("%s: ", nome_fila);
    if (esta_vazia(f)) {
        printf("[VAZIA]\n");
        return;
    }
    
    No *atual = f->inicio;
    while (atual != NULL) {
        printf("[%d]", atual->dado);
        if (atual->proximo != NULL) printf(" -> ");
        atual = atual->proximo;
    }
    printf("\n");
}

int main() {
    Fila *preferencial = criar_fila();
    Fila *convencional = criar_fila();

    printf("====================================================\n");
    printf("     SISTEMA DE GERENCIAMENTO DE FILAS DE BANCO     \n");
    printf("====================================================\n\n");

    printf("--- 1. Chegada de clientes nas filas ---\n");
    
    enqueue(preferencial, 101);
    enqueue(preferencial, 102);
    enqueue(preferencial, 103);
    enqueue(preferencial, 104);
    
    enqueue(convencional, 201);
    enqueue(convencional, 202);
    enqueue(convencional, 203);

    imprimir_fila(preferencial, "Fila Preferencial");
    imprimir_fila(convencional, "Fila Convencional");

    printf("\n--- 2. Verificando proximos da fila (peek) ---\n");
    printf("Proximo Preferencial: %d\n", peek(preferencial));
    printf("Proximo Convencional: %d\n", peek(convencional));

    printf("\n--- 3. Iniciando Atendimento (Regra: 2 Prefs : 1 Conv) ---\n");
    simular_atendimento(preferencial, convencional);

    printf("\n====================================================\n");
    printf("       TODOS OS CLIENTES FORAM ATENDIDOS!           \n");
    printf("====================================================\n");

    return 0;
}