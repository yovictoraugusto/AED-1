//Mensagem quando reserva for solicitada
//Mensagem quando livro for retirado
//Limite de reserva com mensagem se estiver cheia
//Se reserva concluida, imprimir quantas reservas foi realizadas
//Quando retirar livro, imprimir quantos livros já foram retirados
//Inclusão de novas reservas no final da lista
// 1- Reservar; 2- Retirar

/* Programa: Laboratorio
   Autor: Victor Augusto Reis Marques
   Versao: 1.0 - 06/10/2022
*/

//Bibliotecas
#include<stdio.h>
#include<stdlib.h>

//Constantes e variaveis globais
#define N 10
int qtdentra=0, qtdsaida=0;


//Estrutura da lista (TAD)
struct lista{
    int tamanhoLista;
    int listaLivro[N];
};
typedef struct lista reservaLista;

// Funcoes TAD
void inicializa(reservaLista *listaAux){
    int i;
    listaAux->tamanhoLista=0;
    for(i=0;i<N;i++){
        listaAux->listaLivro[i]=0;}
}

int insereLivro(reservaLista *listaAux, int livroAux){
    if(listaAux->tamanhoLista<10){
        listaAux->tamanhoLista++;
        listaAux->listaLivro[listaAux->tamanhoLista-1]=livroAux;
        printf("Sua reserva foi realizada\n");
        qtdentra++;
    }else{
        printf("Lista de reserva cheia\n");
    }
    return 0;
}

int retiraLivro(reservaLista *listaAux, int livroAux){
    int k,i,x=0;
    if(listaAux==NULL){
        printf("Voce nao possui reserva desse livro\n");
        x=1;
        return 1;
    }
    if(listaAux->tamanhoLista==0){
        printf("Voce nao possui reserva desse livro\n");
        x=1;
        return 1;
    }

    for(i=0;i<=listaAux->tamanhoLista;i++){
        if(livroAux==listaAux->listaLivro[i]){
            for(k=i;k<listaAux->tamanhoLista-1;k++){
                listaAux->listaLivro[k]=listaAux->listaLivro[k+1];
            }if(x==0){
                listaAux->tamanhoLista--;
                printf("O livro foi retirado com sucesso\n");
                qtdsaida++;
                return 0;
            }
        }
    }

    if(i>listaAux->tamanhoLista){
        printf("Voce nao possui reserva desse livro\n");
        return 1;
    }   
}

//Funcao principal
int main(){
    reservaLista reserva;
    int entr, opcao, livro;

    inicializa(&reserva);
    scanf("%d",&entr);
    for(int i=0;i<entr;i++){
        scanf("%d %d",&opcao,&livro);
        if(opcao==1){
            insereLivro(&reserva,livro);
        }else if(opcao==2){
            retiraLivro(&reserva,livro);
        }
    }
    printf("Voce realizou %d reservas e %d retiradas\n", qtdentra, qtdsaida);
    return 0;
}
