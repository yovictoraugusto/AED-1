#include<stdio.h>
#include<stdlib.h>

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};
typedef struct elemento* Lista;//Um ponteiro do tipo elemento
//Ele vai ser usado para armazenar os dados em si

struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;//Uma estrutura auxiliar para as operações
//Ele vai ser uma "bengala" de apoio, será como uma struct para as operações

Lista *li;//Ponteiro para ponteiro

//Cria lista
Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

//Libera Lista
void libera_lista(Lista* li){
    if(li!=NULL){
        Elem* no;
        while((*li)!=NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

//tamanho da Lista
int tamanho_lista(Lista* li){
    if(li == NULL) return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL){
        cont++;
        no=no->prox;
    }
    return cont;
}

//lista vazia?
int lista_vazia(Lista* li){
    if(li == NULL) return 1;
    if(*li == NULL) return 1;
    return 0;
}

//Insere:
//4 tipos de inserção
    //-Início
    //-Meio
    //-Final
    //-NULL
int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL) return 0;//Confere se a lista é NULL
    Elem* no = (Elem*) malloc(sizeof(Elem));//Se não for ele aloca espaço para um novo elemento
    if(no == NULL) return 0;//Verifica se foi alocado
    no->dados = al;//Pega os dados inseridos e adiciona ao campo dados do novo no
    no->prox = (*li);//O prox do no recebe o inicio da lsita, nesse caso = NULL ou o antigo primeiro elemento
    *li = no;//O inicio da lista aponta para o no
    return 1;
}

int insere_lista_fim(Lista *li, struct aluno al){
    if(li == NULL) return 0;//Confere se a lista é NULL
    Elem* no = (Elem*) malloc(sizeof(Elem));//Se não for ele aloca espaço para um novo elemento
    if(no == NULL) return 0;//Verifica se foi alocado
    no->dados = al;//Pega os dados inseridos e adiciona ao campo dados do novo no
    no->prox = NULL;//Como é o último elemento, ele vai ta apontando para NULL
    if((*li)==NULL){//Verifica se é há algum primeiro elemento
        *li=no;//Se não existir, o no vai ser
    }else{//Caso haja elemento
        Elem* aux = *li;//Um aux recebe o primeiro da lista
        while(aux->prox!=NULL){//O while roda a lista toda usando o prox para nortear essa busca até o ponto igual a NULL, quando chegar a prox= NULL é porque é o último elemento
            aux=aux->prox;//Aux recebe o próximo dele
        }
        aux->prox=no;//O último elemento recebe o no como prox
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL) return 0;//Confere se a lista é NULL
    Elem* no = (Elem*) malloc(sizeof(Elem));//Se não for ele aloca espaço para um novo elemento
    if(no == NULL) return 0;//Verifica se foi alocado
    no->dados = al;//Pega os dados inseridos e adiciona ao campo dados do novo no
    if(lista_vazia(li)){//Insere o início seguindo a lógica do insere_lista_inicio
        no->prox=*li;
        *li=no;
        return 1;
    }else{//procura onde insere
        Elem *ant, *atual=*li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ant  = atual;
            atual = atual->prox;
        }
        if(atual == *li){//Insere no início
            no->prox = (*li);
            *li = no;
        }else{//Insere no meio ou no fim
            no->prox = ant->prox;
            ant->prox = no;
        }
        return 1;
    }
}

//Delete:
//3 tipos de deleção
    //-Início
    //-Meio
    //-Final
int remove_lista_inicio(Lista* li){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;
    
    //Nesse caso já abrange os dois casos possível uma lsita com mais de um elemento, sendo o prox do primeiro
    //...o novo elementou ou uma lista com apenas o primeiro elemento, já que o li agora aponta para o próximo 
    //...do primeiro que é NULL
    Elem *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;

    Elem *ant, *no = *li;
    while(no->prox != NULL){//Percorre até o último elemento
        ant = no;
        no = no->prox;
    }
    if(no == *li){//Se só tiver um elemento na lista
        *li = no->prox;//*li aponta para NULL
    }else{//Se tiver mais de um elemento
        ant->prox = no->prox;//O anterior aponta para NULL
    }
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat){
    if(li == NULL) return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == NULL) return 0;//Não encontrado, lista vazia ou não tem esse elemento na posição
    if(no == *li) *li = no->prox; //Remove na primeira posição
    else ant->prox = no->prox; //Remove no meio ou fim

    free(no);
    return 1;
}

//Consulta
    //Pela posição
int consulta_lista_posicao(Lista* li, int pos, struct aluno *al){//Essa struct vai ser usada para devolver o conteúdo para fora da lista
    if(li == NULL || pos <= 0) return 0; //Verifica se há algo na lista ou se a posição passada é válida
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){ //Percorre até o último elemento ou até i==pos
        no = no->prox;
        i++;
    }
    if (no == NULL) return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

    //Pelo conteúdo
int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL) return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL) return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

//funcao main
int main(){
    li = cria_lista();//chama cria_lista
    int x = tamanho_lista(li);
    int y = lista_vazia(li);


    libera_lista(li);//chama libera_lista
    return 0;
}