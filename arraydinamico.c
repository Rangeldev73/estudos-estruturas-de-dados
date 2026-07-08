#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dados;        
    int quantidade;   
    int capacidade;   
} ArrayDinamico;


int remover_elemento(ArrayDinamico *v, int indice) {
    if(indice<0||indice>=v->quantidade) return 0;
    for(int i=indice;i<v->quantidade-1;i++){
        v->dados[i]=v->dados[i+1];
    }
    v->quantidade--;
    return 1;
}