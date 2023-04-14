/*
 * Programa: lab07
 * Autor: Victor Augusto Reis Marques
 * Versão: 1.0 - 09/12/2022
 */

//Bibliotecas externas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Definição da árvore (TAD)
struct info{
    char nome[30];
    char sexo[1];
    int nascimento;
    char filiacao[30];
};

struct NO{
    struct info dados;
    struct NO *esq;
    struct NO *dir;
};
typedef struct NO* ArvBin;
typedef struct info infoAux;

//Funções da Árvore (TAD)

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

//Busca a árvore que possua o nome em questão
ArvBin* b2(struct NO* noh, char nome[]) {
    if (noh == NULL)
        return NULL;
    if (strcmp(nome, noh->dados.nome) == 0)
        return noh;
    struct NO* aux = b2(noh->dir, nome);
    if (aux != NULL)
        return aux;
    return b2(noh->esq, nome);
}

//Busca a árvore e retorna o pai da árvore buscada
ArvBin* b3(struct NO *noh, struct NO* filho) {
    if (noh == NULL)
        return NULL;
    if (noh->dir == filho || noh->esq == filho)
        return noh;
    struct NO* aux = b3(noh->dir, filho);
    if (aux != NULL)
        return aux;
    return b3(noh->esq, filho);
}

int insere_Normal(ArvBin* raiz, struct NO* pai, struct NO* novo){
    if (pai->dir->dados.nascimento > novo->dados.nascimento) {
        pai->esq = pai->dir;
        pai->dir = novo;
        return 1;
    } else {
        pai->esq = novo;
        return 1;
    }
}

//Usado para o caso de mulheres com nascimento antes de 2011
int insere_Caso_Especial(ArvBin* raiz, struct NO* pai, struct NO* novo){
    pai->esq = pai->dir;
    pai->dir = novo;
    return 1;
}

int insere_ArvBin(ArvBin* raiz, struct info dadoInsercao){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->dados = dadoInsercao;
    novo->dir = NULL;
    novo->esq = NULL;
    if(*raiz == NULL) //Não foi criada
        *raiz = novo;
    else{
        struct NO* pai = b2(*raiz, novo->dados.filiacao);
        if(pai->dir == NULL){
            pai->dir = novo;
            return 1;
        }
        int sexoDir = strcmp(pai->dir->dados.sexo,"M");
        int sexoNovo = strcmp(novo->dados.sexo,"M");
        if((sexoDir == 0) && (sexoNovo == 0)){
            insere_Normal(raiz, pai, novo);
        }else{
            if(sexoDir<0){
                if(pai->dir->dados.nascimento >= 2011){
                    insere_Normal(raiz, pai, novo);
                }
                else{
                    insere_Caso_Especial(raiz, pai, novo);
                }
            }else if(sexoNovo<0){
                if(novo->dados.nascimento >= 2011){
                    insere_Normal(raiz, pai, novo);
                }
                else{
                    pai->esq = novo;
                }
            }
        }
    }
    return 1;
}

int exclue_ArvBin(ArvBin *raiz, struct NO* posExcluir){
    if(raiz == NULL)
        return 0;
    if(posExcluir != NULL){
        struct NO* pai = b3(*raiz, posExcluir);
        if(pai->dir == posExcluir){
            pai->dir = pai->esq;
        }
        pai->esq = NULL;
        free(posExcluir);
    }
    return 1;
}

//Usado para intermediar a exclusão da árvore
int inter_Exclue_ArvBin(ArvBin *raiz, struct info dadoExclui){
    if(raiz == NULL)
        return 0;
    exclue_ArvBin(raiz, b2(*raiz, dadoExclui.nome));
    return 1;
}

void ordem_ArvBin(ArvBin *raiz){
    if (raiz == NULL) {
        return;
    }
    if (*raiz != NULL) {
        printf("%s\n", (*raiz)->dados.nome);
        ordem_ArvBin(&((*raiz)->dir));
        ordem_ArvBin(&((*raiz)->esq));
    }
}

int main(){
    ArvBin* raiz = cria_ArvBin();
    infoAux aux;
    int l, op;
    scanf("%s %c %d", aux.nome, aux.sexo, &aux.nascimento);
    insere_ArvBin(raiz, aux);
    scanf("%d",&l);
    for(int i = 0; i < l; i++){
        scanf("%d",&op);
        if(op == 1){
            scanf("%s %c %d %s", aux.nome, aux.sexo, &aux.nascimento, aux.filiacao);
            insere_ArvBin(raiz, aux);
        }
        if(op == 2){
            scanf("%s", aux.nome);
            inter_Exclue_ArvBin(raiz, aux);
        }
    }

    ordem_ArvBin(raiz);
    return 0;
}