#include<stdio.h>
#include<stdlib.h>

#define MAX 100
struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};
typedef struct fila Fila;

struct fila{
    int inicio, final, qtd;
    struct aluno dados[MAX];
};

Fila *fi;

Fila* cria_Fila(){
    Fila *fi = (Fila*) malloc(sizeof(struct fila));
    if(fi != NULL){
        fi->inicio = -1;
        fi->final = -1;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi){
    free(fi);
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL)
        return -1;
    return fi->qtd;
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
    if(fi->qtd == 0)
        return 1;
    else
        return 0;
}

//Inserção sempre no final
    //Verificar se a fila tá cheia
    //Final sempre aponta para a posição vaga
int insere_Fila(Fila* fi, struct aluno al){
    if(fi == NULL) return 0;
    if(Fila_cheia(fi)) return 0;
    fi->dados[fi->final] = al;
    fi->final = (fi->final+1) % MAX; //Criando uma circularidade para a fila
    fi->qtd++;
    return 1;
}

//Remoção sempre no início
int remove_Fila(Fila* fi){
    if(fi == NULL || Fila_vazia(fi)) return 0;
    fi->inicio = (fi->inicio+1) % MAX;
    //Mesma coisa q a estrutura abaixo
//    fi->inicio++;
//    if(fi->inicio == MAX)
//        fi->inicio = 0;
    fi->qtd--;
    return 1;
}

//Só pode consultar a primeira posição
int consulta_Fila(Fila* fi, struct aluno *al){
    if(fi == NULL || Fila_vazia(fi)) return 0;
    *al = fi->dados[fi->inicio];
    return 1;
}
