/*
 * Tarefa de laboratorio 10 - Expressão Lógica
 * 
 * 
 * GEX605 AB 2020/1
 *
 * Nome:      Karen Ruver Mentges
 * Matricula: 1921100003
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char Item;

typedef struct elemPilha {
 Item item;
 struct elemPilha *proximo;
} ElemPilha;

typedef struct {
 ElemPilha *topo;
} Pilha;


void inicializaPilha(Pilha *pilha) {
    
    pilha->topo = NULL;

}


int pilhaVazia(Pilha *pilha) {
    
    return (pilha->topo == NULL);

}


void inserePilha(Pilha *pilha, Item item) {
    
    ElemPilha *aux;
    
    // Cria um novo elemento da lista encadeada que representa a pilha e
    // armazena neste novo elemento o item a ser inserido na pilha
    aux = malloc(sizeof(ElemPilha));
    aux->item = item;
    
    // Insere o novo elemento no inicio da lista encadeada que representa a
    // pilha
    aux->proximo = pilha->topo;
    pilha->topo = aux;

}


Item removePilha(Pilha *pilha) {
    
    ElemPilha *aux;
    Item item;
    
    // Verificar se a pilha esta vazia!
    if (pilhaVazia(pilha) != 0) {
        printf("Erro na operacao removePilha: pilha vazia!\n");
        return 0;
    }
    
    // Armazena o item a ser removido da pilha
    item = pilha->topo->item; // ATENCAO: Depende da definicao do tipo do item
    
    // Armazena o primeiro elemento da lista encadeada que representa a pilha
    // e remove este primeiro elemento da lista
    aux = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    
    // Libera a memoria alocada para o elemento removido
    free(aux);

    return item;

}


void liberaPilha(Pilha *pilha) {
    
    ElemPilha *aux;
    
    while (pilha->topo != NULL) {
        // Armazena o primeiro elemento da lista encadeada que representa a
        // pilha e remove este primeiro elemento da lista
        aux = pilha->topo;
        pilha->topo = pilha->topo->proximo;
        
        // Libera a memoria alocada para o elemento removido
        free(aux);

 }
}


int main() {
    
    Pilha exp;
    Item C, R, comp1, comp2;
    int N=0, V=0, O=0;
    
    inicializaPilha(&exp);

    // Lê o numero de valores e operadores a serem inseridos 
    scanf("%d ", &N);
    
    for (int i = 0; i < N; i++) {
        // Lê o valor ou o operador
        scanf("%c ", &C);
        
        // Verifica se o que foi lido é um valor
        if(C=='v' || C=='f'){
            //Insere o valor na pilha (expresão)
            inserePilha(&exp, C);
            // Acrescenta no contador de valores
            V++;
        }
        // Verifica se o que foi lido é um operador
        if(C=='E' || C=='O' || C=='X' || C=='N'){
            // Acrescenta no contador de operadores
            O++;
            // Remove da pilha o ultimo valor inserido
            // E armazena na variavel para ser comparado posteriormente
            comp1 = removePilha(&exp);
            switch (C)
            {
            case 'E':
                // Para essa operação é necessário o valor anterior também
                comp2 = removePilha(&exp);
                // Em seguida é comparado as possibilidades que podemos ter
                if(comp2 == 'v'){
                    if(comp1 == 'v'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'v');
                    }
                    if(comp1 == 'f'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'f');
                    }
                }
                else if(comp2 == 'f'){
                    if(comp1 == 'v'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'f');
                    }
                    if(comp1 == 'f'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'f');
                    }
                }
                break;
            
            case 'O':
                // Para essa operação é necessário o valor anterior também
                comp2 = removePilha(&exp);
                // Em seguida é comparado as possibilidades que podemos ter
                if(comp2 == 'v'){
                    if(comp1 == 'v'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'v');
                    }
                    if(comp1 == 'f'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'v');
                    }
                }
                else if(comp2 == 'f'){
                    if(comp1 == 'v'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'v');
                    }
                    if(comp1 == 'f'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'f');
                    }
                }
                break;
            
            case 'X':
                // Para essa operação é necessário o valor anterior também
                comp2 = removePilha(&exp);
                // Em seguida é comparado as possibilidades que podemos ter
                if(comp2 == 'v'){
                    if(comp1 == 'v'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'f');
                    }
                    if(comp1 == 'f'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'v');
                    }
                }
                else if(comp2 == 'f'){
                    if(comp1 == 'v'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'v');
                    }
                    if(comp1 == 'f'){
                        // É inserido o resultado da operação na pilha
                        inserePilha(&exp, 'f');
                    }
                }
                break;
            
            case 'N':
                if(comp1 == 'v'){
                    // É inserido o resultado da operação na pilha
                    inserePilha(&exp, 'f');
                }
                if(comp1 == 'f'){
                    // É inserido o resultado da operação na pilha
                    inserePilha(&exp, 'v');
                }
                break;
            
            default:
                break;
            }
        }
        
    }

    // É removido da pilha o resultado e armazenado na variável que sera impressa
    R = removePilha(&exp);;

    // Impressão dos contadores e resultado
    printf("Valores: %d\n", V);
    printf("Operadores: %d\n", O);
    printf("Resultado: %c\n", R);
    
    liberaPilha(&exp); // Sem efeito se a pilha ja estiver vazia
    
    return 0;
    
}