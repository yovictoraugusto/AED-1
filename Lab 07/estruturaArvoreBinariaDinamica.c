#include<stdio.h>
#include<stdlib.h>

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};
typedef struct NO* ArvBin;

ArvBin* raiz;

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof (ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

int estaVazia_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int altura_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz ==NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq);
//        return (alt_esq + 1);
    else
        return (alt_dir);
//        return (alt_dir + 1);
}

int totalNO_ArvBIN(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz ==NULL)
        return 0;
    int alt_esq = totalNO_ArvBIN(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBIN(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

//Pré-Ordem
//Visita a raiz, filho da esquerda e o filho da direita
void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n", (*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

//Em-Ordem
//Visita o filho da esquerda, raiz e o filho da direita
void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

//Pós-Ordem
//Visita o filho da esquerda, o filho da direita e a raiz
void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}

int insere_ArvBin(ArvBin* raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof (struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){ //navega até um nó folha
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0; //Elemento já existe
            }
            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    if(atual->esq == NULL){ //trata n folha e nó com 1 filho
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){ //Procura mais a direita da sub-árvore da esquerda
        no1 = no2;
        no2 = no2->dir;
    }
    if(no1 != atual){ //copia o filho mais a direita da sub-árvore a esquerda para o lugar a ser removido
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL) return 0;
    struct NO* atual = *raiz;
    struct NO* ant = NULL;
    while(atual != NULL){
        if(valor == atual->info){//Achou o nó a ser removido
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual; //Continua procurando o nó
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 1;
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info)
            return 1;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int main(){
    ArvBin* raiz = cria_ArvBin();


    libera_NO(raiz);
    return 0;
}