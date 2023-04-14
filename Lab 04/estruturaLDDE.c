#include<stdio.h>
#include<stdlib.h>

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};
typedef struct elemento* Lista;

struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista *li;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(Lista* li){
    if(li == NULL) return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL) return 1;
    if(*li == NULL) return 1;
    return 0;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = al;
    no->ant = NULL;
    no->prox = NULL;
    if(*li != NULL) //caso a lista não esteja vazia
        (*li)->ant = no;
    *li = no;
    return 1;
}

int insere_lista_fim(Lista* li, struct aluno al){
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
    if(*li == NULL){
        no->ant = NULL;
        *li = no;
    }else{
        Elem *aux = *li;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_ordenado(Lista* li, struct aluno al){
    if(li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if(no==NULL) return 0;
    no->dados = al;
    if(lista_vazia(li)){
        no->ant = NULL;
        no->prox = NULL;
        (*li) = no;
        return 1;
    }else{
        Elem *ante, *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ante = atual;
            atual = atual->prox;
        }
        if(atual == *li){
            no->ant == NULL;
            no->prox = (*li);
            (*li)->ant = no;
            *li = no;
        }else{
            no->ant = ante;
            no->prox = ante->prox;
            ante->prox = no;
            if(atual != NULL)
                atual->ant = no;
        }
        return 1;
    }
}

int remove_inicio(Lista* li){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;
    
    Elem* no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;
    free(no);
    return 1;
}

int remove_final(Lista* li){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;
    Elem* no = *li;
    while(no->prox != NULL)
        no = no->prox;
    
    if(no->ant == NULL)
        *li = no->prox;
    else
        no->ant->prox = NULL;
    
    free(no);
    return 1;
}

int remove_ordenado(Lista* li, int mat){
    if(li == NULL) return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL)
        return 0;
    if(no->ant == NULL) //Remove no inico
        *li = no->prox;
    else // Remove no meio ou no final
        no->ant->prox = no->prox;
    if(no->prox != NULL) // Não está removendo no final
        no->prox->ant = no->ant;

    free(no);
    return 1;
}

int consulta_lista_posicao(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)  return 0;
    Elem* no = *li;
    int i = 1;
    while(no != NULL && i<pos){
        no = no->prox;
        i++;
    }
    if(no == NULL) return 0;
    else{
        *al= no->dados;
        return 1;
    }
}

int consulta_lista_dado(Lista* li, int mat, struct aluno *al){
    if(li == NULL) return 0;
    Elem* no = *li;
    while(no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if(no == NULL) return 0;
    else{
        *al = no->dados;
    }
}

int main(){
    li = cria_lista();
    
    libera_lista(li);
}