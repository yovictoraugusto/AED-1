#include<stdio.h>
#include<stdlib.h>

#define N 10

struct lista{
    int ultimo;
    int tamanhoLista;
    int listaNumero[N];
};
typedef struct lista tipoLista;

void inicializa(tipoLista *listaAux){
    int i;
    listaAux->tamanhoLista=0;
    for(i=0;i<N;i++){
        listaAux->listaNumero[i]=0;}
    listaAux->ultimo=0;
}

void insereElemento(tipoLista *listaAux){
    printf("\nDigite o numero %d da lista: ",listaAux->tamanhoLista);
    scanf("%d",&listaAux->listaNumero[listaAux->tamanhoLista]);
    listaAux->ultimo=listaAux->tamanhoLista;
    listaAux->tamanhoLista++;
}

void impressao(tipoLista *listaAux){
    int i;
    for(i=0;i<listaAux->tamanhoLista;i++){
        printf("%d\n",listaAux->listaNumero[i]);
    }
}

void exclusao(tipoLista *listaAux){
    int posicao,i;
    printf("Digite a posicao que voce deseja apagar: ");
    scanf("%d",&posicao);
    listaAux->tamanhoLista--;
    for(i=posicao+1;i<=listaAux->tamanhoLista;i++){
        listaAux->listaNumero[posicao]=listaAux->listaNumero[i];
        posicao++;
    }
    if(i+1==listaAux->tamanhoLista){
            listaAux->ultimo=i;
    }
    listaAux->listaNumero[listaAux->ultimo]=0;
}

int main(){
    tipoLista minhaLista;
    inicializa(&minhaLista);
    impressao(&minhaLista);
    for(int i=0;i<N;i++){
        insereElemento(&minhaLista);}
    impressao(&minhaLista);
    exclusao(&minhaLista);
    impressao(&minhaLista);
    return 0;
}