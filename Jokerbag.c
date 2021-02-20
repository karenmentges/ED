/*
 * Tarefa de laboratorio 11 - JokerBag!
 *
 * GEX605 AB 2020/1
 *
 * Nome:      Karen Ruver Mentges
 * Matricula: 1921100003
 *
 */


#include <stdio.h>
#include <stdlib.h>

// Declarando as variaveis a serem utilizadas no programa
typedef int Item;

typedef struct elemFila {
 Item item;
 struct elemFila *anterior;
 struct elemFila *proximo;
} ElemFila;

typedef struct {
 ElemFila *primeiro;
 ElemFila *ultimo;
} Fila;



void inicializaFila(Fila *fila) {

    // Faz os aponteiramentos para NULL
    fila->primeiro = NULL;
    fila->ultimo = NULL;

}


int filaVazio(Fila *fila) {
    
    return (fila->primeiro == NULL);

}


void insereFimFila(Fila *fila, Item item) {
    
    ElemFila *aux;
    
    // Cria um novo elemento da lista encadeada (Fila)
    aux = malloc(sizeof(ElemFila));

    // Armazena o item a ser inserido no novo elemento 
    aux->item = item;

    // Faz os aponteiramentos para NULL
    aux->proximo = NULL;
    aux->anterior = NULL;
    
    // Insere o novo elemento no fim da lista encadeada (Fila)
    if (fila->primeiro == NULL) { // Se a fila esta vazia
        fila->primeiro = aux;
        fila->ultimo = aux;
    }

    else { // Se a fila nao esta vazia
        aux->anterior = fila->ultimo;
        fila->ultimo->proximo = aux;
        fila->ultimo = aux;
    }
    
}


void removeInicioFila(Fila *fila) {
    
    ElemFila *aux;
    
    // Verificar se a fila esta vazia
    if (fila->primeiro == NULL) {
        return;
    }

    else {
        // Armazena o primeiro elemento da lista encadeada (Fila)
        aux = fila->primeiro;
    
        // Remove este primeiro elemento da lista
        if (fila->primeiro == fila->ultimo) {
            fila->primeiro = NULL;
            fila->ultimo = NULL;
        }
        else {
            fila->primeiro = fila->primeiro->proximo;
            fila->primeiro->anterior = NULL;
        }   

        // Libera a memoria alocada para o elemento removido
        free(aux);
    }

}


void removeFimFila(Fila *fila) {
    
    ElemFila *aux;
    
    // Verificar se a fila esta vazia
    if (fila->primeiro == NULL) {
        return;
    }

    else {
        // Armazena o ultimo elemento da lista encadeada (Fila)
        aux = fila->ultimo;
    
        // Remove este ultimo elemento da lista
        if (fila->ultimo == fila->primeiro) {
            fila->primeiro = NULL;
            fila->ultimo = NULL;
        }
        else {
            fila->ultimo = fila->ultimo->anterior;
            fila->ultimo->proximo = NULL;
        }   

        // Libera a memoria alocada para o elemento removido
        free(aux);
    }

}


void removeItem(Fila *fila, Item item){

    ElemFila *aux, *anterior;

    for (aux = fila->primeiro; aux != NULL; aux = aux->proximo){
        if (aux->item == item){
            anterior = aux->anterior;
            anterior->proximo = aux->proximo;
            aux->proximo->anterior = anterior;
        }        
    }
    free(aux); 
}


void liberaFila(Fila *fila) {
    
    ElemFila *aux;
    
    while (fila->primeiro != NULL) {
        
        // Armazena o primeiro elemento da lista encadeada (Fila)
        aux = fila->primeiro;
        // Faz o aponteiramento para o proximo elemento
        fila->primeiro = fila->primeiro->proximo;
        
        // Libera a memoria alocada para o elemento removido
        free(aux);

    }

    // Aponta o final da fila para NULL
    fila->ultimo = NULL;

}


int main() {
    
    // Declarando as variaveis para o main
    Fila lista;
    Item X=0;
    int N=0, cont1=0, cont2=0, i=0;
    char C;
 

    while(i <= 10000){

        inicializaFila(&lista);

        scanf("%d%*c", &N);

        // Se N=0 finalizamos o laço
        if(N == 0){
            break;
        }

        // Inicializamos os contadores com 0 para cada analise
        cont1 = 0;
        cont2 = 0;
        
        // Laço para obter as operações e valores
        for(int i=0; i<N; i++){
            scanf("%c %d%*c", &C, &X);

            // Se a operação for "I", sera realizada a função de inserir
            // o valor no fim da fila
            if(C == 'I'){
                insereFimFila(&lista, X);
            }  
            
            // Se a operação for "R", sera realizada a função de remover
            else if(C == 'R'){
                // Se for a primeira remoção o programa analisa todas as opções
                if(cont1 == 0 && cont2 == 0){             
                    // Se o primeiro e o ultimo forem iguais
                    // Assume que pode ser tanto pilha quanto fila
                    if(lista.primeiro->item == lista.ultimo->item){
                        if (lista.primeiro->item == X){
                            removeInicioFila(&lista);
                            cont1++;
                            cont2++;
                        }
                    }
                    // Se estiver sendo removido o primeiro valor
                    // o contador de fila é acrescentado
                    else if(lista.primeiro->item == X){
                        removeInicioFila(&lista);
                        cont2++;
                    }
                    // Se estiver sendo removido o ultimo valor
                    // o contador de pilha é acrescentado
                    else if(lista.ultimo->item == X){
                        removeFimFila(&lista);
                        cont1++;
                    }
                    // Se o numero inserido for diferente do primeiro e do ultimo
                    else if(lista.primeiro->item != X && lista.ultimo->item != X){
                        removeItem(&lista, X);
                        cont1 = -1;
                        cont2 = -1;
                    }
                }

                else if(cont1 > 0 && cont2 > 0){     
                    // Se o primeiro e o ultimo forem iguais
                    // Assume que pode ser tanto pilha quanto fila         
                    if(lista.primeiro->item == lista.ultimo->item){
                        removeInicioFila(&lista);
                        cont1++;
                        cont2++;
                    }
                    // Se estiver sendo removido o primeiro valor
                    // o contador de fila é acrescentado
                    else if(lista.primeiro->item == X){
                        removeInicioFila(&lista);
                        cont2++;
                        cont1 = 0;
                    }
                    // Se estiver sendo removido o ultimo valor
                    // o contador de pilha é acrescentado
                    else if(lista.ultimo->item == X){
                        removeFimFila(&lista);
                        cont1++;
                        cont2 = 0;
                    }
                    else {
                        removeItem(&lista, X);
                        cont1 = -1;
                        cont2 = -1;
                    }
                }

                // Se já foi removido anteriormente é analisado os contadores

                // Se foi removido o ultimo, é analisado se será removido 
                // o ultimo novamente, se não é jokerbag
                else if(cont1 > 0 && cont2 == 0){
                    if(lista.ultimo->item == X){
                        removeFimFila(&lista);
                        cont1++;
                    }   
                    else if(lista.primeiro->item == X) {
                        removeInicioFila(&lista);
                        cont1 = -1;
                        cont2 = -1;
                    }         
                    else {
                        removeItem(&lista, X);
                        cont1 = -1;
                        cont2 = -1;
                    }
                }
                // Se foi removido o primeiro, é analisado se será removido 
                // o primeiro novamente, se não é jokerbag
                else if(cont1 == 0 && cont2 > 0){
                    if(lista.primeiro->item == X){
                        removeInicioFila(&lista);
                        cont2++;
                    }
                    else if (lista.ultimo->item == X){
                        removeFimFila(&lista);
                        cont1 = -1;
                        cont2 = -1;
                    }
                    else {
                        removeItem(&lista, X);
                        cont1 = -1;
                        cont2 = -1;
                    }
                }
            }     
        }

        // Liberar a fila para não pegar resto de outras analises
        liberaFila(&lista);
           

        // Comparando se tivemos remoções do ultimo elemento
        if(cont1>0 && cont2<=0){
            printf("pilha!\n");
        }
        // Comparando se tivemos remoções do primeiro elemento
        else if(cont1<=0 && cont2>0){
            printf("fila!\n");
        }
        // Comparando se tivemos remoções do prinmeiro e do ultimo elemento
        else if(cont1>0 && cont2>0){
            printf("nem Turing sabe!\n");
        }
        else{
            printf("jokerBag!\n");
        }

        // Aumentando o contador do while
        i++;

    }

    // Liberar a fila
    liberaFila(&lista);  
    
    return 0;

}