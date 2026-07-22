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