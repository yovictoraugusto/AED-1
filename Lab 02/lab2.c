/*
 * Programa: lab2
 * Autor: Victor Augusto Reis Marques
 * Versão; 1.0 - 08/10/2022
 */

//Bibliotecas
#include<stdio.h>
#include<stdlib.h>

//Constantes
#define MAX 10

//Variavel Global
int cont[8];

//Estrutura Auxiliar TAD

struct aluno{
    int ra;
};
typedef struct aluno tipoAluno;

//Estrutura da List (TAD)
struct lista{
    int qtd;
    struct aluno dados[MAX];
    //  Por ser uma estrutura parecida com vetor não há necessidade que haja uma variável dizendo qual é o próximo
    //  O início será em dados[0] e o fim em dados[qtd-1]
};
typedef struct lista tipoLista;

tipoLista *li;

void inicializaLista(tipoLista* li){
    int i;
    li->qtd=0;
    for(i=0;i<MAX;i++) {
        li->dados[i].ra = 0;
    }
}

//TAD insere
int insere_lista_ordenada(tipoLista* li, struct aluno al){ //Já atende os 3 casos de inserção
    if(li->qtd == MAX) {
        printf("lista cheia\n");
        return 0;
    }
    int k, i = 0;
    while(i < li->qtd && li->dados[i].ra < al.ra){// Vai até o final da lista procurando até achar um valor maior que o digitado, inserindo ordenado
        i++;
    }
    for(k = li->qtd-1; k>= i; k--)
        li->dados[k+1] = li->dados[k];
    li->dados[i].ra = al.ra;
    li->qtd++;
    return 1;
}

//TAD exclue
int remove_lista(tipoLista* li, int mat){ //Já atende os 3 casos da exclusão
    if(li->qtd == 0){
        printf("nao existe\n");
        return 0;
    }
    int k, i = 0;
    while(i<li->qtd && li->dados[i].ra != mat) //Vai até o final da lista até achar um o valor digitado
        i++;
    if(i == li->qtd){ //Se for até o final e não achar é porque não tem o valor
        printf("nao existe\n");
        return 0;
    }
    for(k=i; k<li->qtd-1; k++)
        li->dados[k] = li->dados[k+1]; //Se for o caso do primeiro valor a ser retirado, então, o primeiro recebe o valor do segundo, o segundo do terceiro e assim por adiante
    li->dados[li->qtd-1].ra = 0; // O último valor é zerado, pois pela lógica anterior, o ultimo valor e o penultimo receberiam o mesmo valor
    li->qtd--;
    return 1;
}

//TAD imprime
void imprimeElemento(tipoLista *li){
    if(li->qtd == 0){
        printf("\n");
        return;
    }
    for(int i = 0;i<=li->qtd-1;i++){
        if(li->dados[i].ra != 0){
            printf("%d ",li->dados[i].ra);
        }
    }
    printf("\n");
}

//Cont ano
/*Pega os dois primeiros digitos e compara com os casos do case, se os digitos forem iguais a algum dos digitos do ano em questao, o contador recebe +1
*/
void contAno(int raEntra, int controle){
    int aux = raEntra/1000;
    if(controle==1){
        switch(aux){
            case 66:
                cont[0]++;
                break;
            case 76:
                cont[1]++;
                break;
            case 86:
                cont[2]++;
                break;
            case 96:
                cont[3]++;
                break;
            case 106:
                cont[4]++;
                break;
            case 116:
                cont[5]++;
                break;
            case 126:
                cont[6]++;
                break;
            case 136:
                cont[7]++;
                break;
        }
    }
}

//Funcao Main
int main(){
    tipoLista listaLab;
    tipoAluno aluno;
    int entr, op, ra, ret;

    inicializaLista(&listaLab);
    scanf("%d", &entr);
    for(int i = 0;i<entr; i++){ //Inserir
        scanf("%d %d", &op, &aluno.ra);
        //imprimeElemento(&listaLab);
        if(op==1){
            ret = insere_lista_ordenada(&listaLab, aluno);
            imprimeElemento(&listaLab);
            contAno(aluno.ra, ret);
        }
        else if(op==2){ //Remover
            remove_lista(&listaLab, aluno.ra);
            imprimeElemento(&listaLab);
        }
    }

    for(int i=0;i<8;i++){
        printf("201%d: %d\n",i+1, cont[i]);
    }
    return 0;
}