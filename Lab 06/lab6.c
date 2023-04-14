/*
 * Programa: lab6
 * Autor: Victor Augusto Reis Marques
 * Versão: 1.0 - 27/11/2022
 */


//Bibliotecas Externas
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Definição da Pilha (TAD)
#define MAX 20

struct number{
    int num;
};
typedef struct pilha Pilha;

struct pilha{
    int qtd;
    struct number dados[MAX];
};

Pilha *pi;

//Funções da Pilha (TAD)
Pilha* cria_Pilha(){
    Pilha *pi;
    pi = (Pilha*) malloc(sizeof(struct pilha));
    if(pi != NULL)
        pi->qtd = 0;
    for(int i = 0; i < MAX; i++){
        pi->dados[i].num = 0;
    }
    return pi;
}

void libera_Pilha(Pilha* pi){
    free(pi);
}

int insere_Pilha(Pilha* pi, int n){
    pi->dados[pi->qtd].num = n;
    pi->qtd++;
    return 1;
}

int consulta_Pilha(Pilha* pi, int pos){
    if(pi == NULL || pi->qtd == 0)
        return 0;
    for(int i = pos;i < pi->qtd; i++){
        printf("%d", pi->dados[i].num);
    }
    return 1;
}

// Funções e Procedimentos do Programa
// Quando há a conversão de decimal para binário, aparece 1 zero ou mais a frente do número
// como no caso do 5, quando convertido aparecia 0101, essa função retorna a posição que começa
// o número, no caso [1].
int retornaPosicao(Pilha* pi){
    for(int i = 0; i < 50;i++){
        if(pi->dados[i].num == 1){
            return i;
        }   
    }
    return 1;
}

// Função recursiva para a conversão de decimal para binário, enquanto o resultado (n) for
// diferente de 0, chama a si própria, passando como valor n/2 e insere na pilha n%2
int conversaoDecParaBin(Pilha* pi, int n){
    if(n == 0)
        insere_Pilha(pi, n);
    else{
        conversaoDecParaBin(pi, (n/2));
        insere_Pilha(pi, (n % 2));
    }
    return 1;
}

// Inverte o valor binário através da negação
int invertePilha(Pilha* pi, int pos){
    int x = 0;
    printf(" ");
    for(int i = pos;i < pi->qtd; i++)
        printf("%d", !pi->dados[i].num);
    return 1;
}

// Converte de binário para decimal, iniciando a contagem do primeiro valor válido e elevando
// ao quadrado quando o valor for 1
// Por exemplo: 5, convertido é 101, invertendo fica 010, nesse caso, ele pega a posição [1] e
// ao quadrado
int converteBinParaDec(Pilha* pi, int pos){
    int Ndec = 0, j = 0;
    for(int i = (pi->qtd-1); i >= pos; i--){
        if((!pi->dados[i].num) == 1){
            if(j == 0)
                Ndec = Ndec + 1;
            else {
                Ndec = Ndec + (pow(2,j));
            }
        }
        j++;
    }
    return Ndec;
}

// Zera a fila permitindo que ela seja reutilizada até o final do caso
int zeraPilha(Pilha* pi){
    for(int i = 0; i < MAX; i++){
        pi->dados[i].num = 0;
    }
    pi->qtd = 0;
    return 1;
}

// Imprime o resultado através da chamada de outras funções
int imprimeResultado(int n){
    int pos = retornaPosicao(pi);
    printf("%d ",n);    
    consulta_Pilha(pi, pos);
    invertePilha(pi, pos);
    printf(" %d",converteBinParaDec(pi, pos));
    printf("\n");
    zeraPilha(pi);
    return 1;
}

int main(){
    pi = cria_Pilha();
    int l, n;
    scanf("%d", &l);
    for(int i = 0; i < l; i++){
        scanf("%d", &n);
        conversaoDecParaBin(pi, n);
        imprimeResultado(n);
    }

    free(pi);
    return 0;
}