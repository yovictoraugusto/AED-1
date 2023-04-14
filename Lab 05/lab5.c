/**
 * Programa: Lab5
 * Autor: Victor Augusto Reis Marques
 * Versão: 1.0 - 14/11/2022
 */

//Qtd operações L
//3 operações
    // 1 - inserção
        // Dois numeros um indicando a operação e outro o ID a ser inserido
    // 2 - Remoção
        // Um inteiro identificando a operação
    // 3 - Conclusão
        // Um inteiro identificando a operação

//Caso haja a tentativa de remoção ou conclusão e a fila estiver vazia deve imprimir "vazia"

//Bibliotecas
#include <stdio.h>
#include<stdlib.h>

//Constantes
#define MAX 100

//Estruturas
struct tarefa{
    int id;
};

struct fila{
    int inicio;
    int final;
    int qtd;
    struct tarefa dados[MAX];
};
typedef struct fila Fila;
// typedef struct tarefa aux;

//Métodos TAD Fila
Fila *fi;

Fila* cria_Fila(){
    Fila *fi = (Fila*) malloc(sizeof (struct fila));
    if(fi != NULL){
        fi->inicio = 0;
        fi->final = 0;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila *fi){
    free(fi);
}

int Fila_cheia(Fila* fi){
    if(fi == NULL) return -1;
    if(fi->qtd == MAX)
        return 1;
    else
        return 0;
}

int Fila_vazia(Fila* fi){
    if(fi == NULL) return -1;
    if(fi->qtd == 0) return 1;
    else return 0;
}

int insere_Fila(Fila* fi, int number){
    if(fi == NULL) return 0;
    if(Fila_cheia(fi)) return 0;
    fi->dados[fi->final].id = number;
    fi->final = (fi->final+1) % MAX; // Cria a circularidade da fila
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi){
    int aux = Fila_vazia(fi);
    if(aux == 1){
        printf("vazia\n");
        return 0;
    }
    fi->dados[fi->inicio].id = 0;
    fi->inicio = (fi->inicio+1) % MAX;
    fi->qtd--;
    return 1;
}

int conclui_Fila(Fila* fi){
    int aux = Fila_vazia(fi);
    if(aux == 1){
        printf("vazia\n");
        return 0;
    }
    int number = fi->dados[fi->inicio].id;// Pega o id da primeira posição
    fi->dados[fi->inicio].id = 0; //Zera a primeira posição
    insere_Fila(fi, number); //Insere o id no final da lista
    fi->qtd--;//Por chamar a função insere, há o acrescimo de 1 na quantidade, então essa linha tira esse acresimo
    fi->inicio = (fi->inicio+1) % MAX; //Muda a posição do inicio para o posterior
    return 1;
}

int consulta_Fila_inteira(Fila* fi){
    int aux = Fila_vazia(fi);
    if(aux == 1){
        printf("\n");
        return 0;
    }
    int i = fi->final-1;
    int j = 0;
    do{
        if(fi->dados[i].id != 0){
            printf("%d ",fi->dados[i].id);
            
        }
        i--;
        j++;
    }while(j <= fi->qtd && i>=0);
    return 1;
}

int main(){
    fi = cria_Fila();
    int l;//representa a quantidade de linhas de teste
    int op, number;

    scanf("%d",&l);
    for (int i = 0; i < l; i++){
        scanf("%d",&op);
        if(op == 1) {
            scanf("%d",&number);
            insere_Fila(fi, number);
        }
        else if(op == 2)
            remove_Fila(fi);
        else if(op == 3)
            conclui_Fila(fi);
        // consulta_Fila_inteira(fi);
        // printf("\n");
        // printf("\t\tQTD: %d",fi->qtd);
        // printf("\n");
    }

    consulta_Fila_inteira(fi);
    libera_Fila(fi);
    return 0;
}