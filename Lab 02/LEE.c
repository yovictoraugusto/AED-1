#include <stdio.h>

struct info{
    int valor;
    int prox;
};
typedef struct info tipoInfo;

struct listaEE{
    int tamanhoLista;
    int primeiro;
    int ultimo;
    int posLivre[5];
    tipoInfo elemento[5];
};
typedef struct listaEE tipoListaEE;

//Inicia a lista
void iniciaLista(tipoListaEE *listaAux){
    int i;
    //Iniciando parâmetros
    listaAux->tamanhoLista=0;
    listaAux->primeiro=-1;
    listaAux->ultimo=-1;
    for(i=0;i<5;i++){
        listaAux->elemento[i].valor=0;
        listaAux->elemento[i].prox=-1;
        listaAux->posLivre[i]=1;
    }
    printf("Lista iniciada com sucesso\n");
}

//Metodo para determinar o próximo espaço na memória
//1- Desocupado
//0- Ocupado
int proxPosLivre(tipoListaEE *listaAux){
    int i;
    for(i=0;i<5;i++){
        if(listaAux->posLivre[i]==1)
            return i;
    }
    return -1;
}

//Insere
void insereElemento(tipoListaEE *listaAux, int num,int pos){
    //Se a lista estiver vazia ele vai colocar o elemento na primeira posicao
    if(listaAux->tamanhoLista==0){
        listaAux->tamanhoLista++;
        listaAux->primeiro=0;
        listaAux->ultimo=0;
        listaAux->elemento[listaAux->ultimo].valor=num;
        listaAux->elemento[listaAux->ultimo].prox=1;
        listaAux->posLivre[listaAux->ultimo]=0;
        printf("Elemento inserido na primeira posicao com sucesso\n");
    }
    //Se nao estiver ele vai usar o pos que mostra onde esta a proxima posicao livre e vai adicionar nela
    else{
        listaAux->tamanhoLista++;
        listaAux->ultimo=pos;
        listaAux->elemento[listaAux->ultimo].valor=num;
        listaAux->posLivre[listaAux->ultimo]=0;
        printf("Elemento inserido com sucesso\n");
    }
}

//Exclue
void exclueElemento(tipoListaEE *listaAux, int num){
    for(int i=0;i<=listaAux->tamanhoLista;i++){
        if(num==listaAux->elemento[i].valor){
            listaAux->elemento[i].valor=0;
            listaAux->elemento[i].prox=-1;
            listaAux->tamanhoLista--;
            listaAux->ultimo=i;
            listaAux->posLivre[i]=1;
        }
    }
}

//Imprime a lista toda
void imprimeElemento(tipoListaEE *listaAux){
    for(int i=0;i<5;i++){
        if(listaAux->posLivre[i]==0){
            printf("i=%d: %d\n",i,listaAux->elemento[i].valor);
        }
    }
}

int main(){
    int num,pos,op=1;
    tipoListaEE minhaLista;
    iniciaLista(&minhaLista);

    //Chama insercao
    do{
        printf("Digite um numero: ");
        scanf("%d",&num);
        pos=proxPosLivre(&minhaLista);
        insereElemento(&minhaLista,num,pos);
        printf("Deseja adicionar mais um numero?1-Sim0-Nao\n");
        scanf("%d",&op);
    }while(op!=0);
    imprimeElemento(&minhaLista);

    //Chama exclusao
    do{
        printf("Digite o numero que voce quer retirar: ");
        scanf("%d",&num);
        exclueElemento(&minhaLista,num);
        printf("Deseja adicionar mais um numero?1-Sim0-Nao\n");
        scanf("%d",&op);
    }while(op!=0);
    imprimeElemento(&minhaLista);

    //Chama insercao
    do{
        printf("Digite um numero: ");
        scanf("%d",&num);
        pos=proxPosLivre(&minhaLista);
        insereElemento(&minhaLista,num,pos);
        printf("Deseja adicionar mais um numero?1-Sim0-Nao\n");
        scanf("%d",&op);
    }while(op!=0);
    imprimeElemento(&minhaLista);

    return 0;
}