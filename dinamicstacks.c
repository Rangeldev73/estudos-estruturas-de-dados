#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo; 
} Pilha;

Pilha* criar_pilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = NULL;
    }
    return p;
}

void push(Pilha *p, int valor){
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL){
        printf("Erro de alocação: Heap cheia!\n");
        return;
    }
    novo->dado = valor;
    novo->proximo = p->topo;
    p->topo = novo;
}

int esta_vazia(Pilha *p){
    return (p->topo == NULL);
}

int pop(Pilha *p){
    if (esta_vazia(p)){
        printf("Pilha Vazia! Underflow detectado.\n");
        return INT_MIN;
    }
    No *aux = p->topo;        
    int valor = aux->dado;   
    p->topo = aux->proximo;    
    free(aux);                  
    return valor;
}

void destruir_pilha(Pilha *p){
    if (p != NULL) {
        while (!esta_vazia(p)){
            pop(p); 
        }
        free(p); 
    }
}

int esta_balanceado(const char *expressao){
    Pilha *p = criar_pilha();
    for (int i = 0; expressao[i] != '\0'; i++){
        char atual = expressao[i];
        if(atual=='{'||atual=='('||atual=='['){
            push(p,atual);
        }
        else if (atual == '}' || atual == ')' || atual == ']'){
            if (esta_vazia(p)) {
                destruir_pilha(p); 
                return 0;
            }
            char desempilhado = pop(p);
            if ((atual == ')' && desempilhado != '(') ||
                (atual == ']' && desempilhado != '[') ||
                (atual == '}' && desempilhado != '{')) {
                destruir_pilha(p);
                return 0;
            }
        }
    }
    int balanceado = esta_vazia(p);
    destruir_pilha(p);
    return balanceado;
}

int main() {
    printf("====================================================\n");
    printf("  VALIDADOR DE EXPRESSOES MATEMATICAS (PILHA)     \n");
    printf("====================================================\n\n");

    const char *expressoes[] = {
        "{[()]}",              
        "(1 + 2) * [3 / {4}]",  
        "((())",               
        "({[}]",               
        "}",                   
        "{[()()]}"             
    };

    int total_testes = sizeof(expressoes) / sizeof(expressoes[0]);

    for (int i = 0; i < total_testes; i++) {
        printf("Expressao %d: %-25s -> ", i + 1, expressoes[i]);
        if (esta_balanceado(expressoes[i])) {
            printf("[BALANCEADA]\n");
        } else {
            printf("[DESBALANCEADA]\n");
        }
    }

    printf("\n====================================================\n");
    printf("               TESTES FINALIZADOS!                  \n");
    printf("====================================================\n");

    return 0;
}