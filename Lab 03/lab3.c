/**
 * Programa Lab3
 * Autor: Victor Augusto Reis Marques
 * Versão: 1.0 - 02/10/2022
*/

//Bibliotecas
#include<stdio.h>
#include<stdlib.h>

//Estruturas
struct produto{
    int id;
    int quant;
    float preco;
    int quantVenda; //Opitei por adicionar essa variável por ser o modo mais fácil de contabilizar a venda, outros jeitos que pensei tinham que 
};
typedef struct elemento* Lista; 
typedef struct produto produtoAuxiliar; //Usado no main para passar os valores para o método de inserção

struct elemento{
    struct produto dados;
    struct elemento *prox;
};
typedef struct elemento Elem; //Essa estrutura vai ser usado para a manipulação de todos os dados

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

int lista_vazia(Lista* li){
    if(li == NULL) return 1;
    if(*li == NULL) return 1;
    return 0;
}

int insere_lista_ordenada(Lista* li, struct produto pro){
    if(li == NULL) return 0; //Verifica se a lista é NULL
    Elem* no = (Elem*) malloc(sizeof(Elem)); //Aloca o espaço
    if(no == NULL) return 0; //Verifica se foi alocado
    no->dados = pro; //Passa os valores digitados para o no
    if(lista_vazia(li)){//Insere no início. *li é o ponteiro para a primeira posição
        no->prox=*li;
        *li=no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        while(atual != NULL && atual->dados.preco > pro.preco && atual->dados.id != pro.id){ //Passa pela lista inteira até a ultima posicao que aponta para NULL ou até um preço maior/igual ou até encontrar um id igual ao passado pelo usuário
            ant = atual;
            atual = atual->prox;
        }
        if(atual->dados.id == pro.id){ //Tentativa de cadastrar produto já cadastrado (atual->dados.id == pro.id)
            printf("ja existe\n");
            return 0;
        }
        if(atual == *li){ // Insere no inicio (atual == NULL)
            no->prox = (*li);
            *li = no;
            return 1;
        }
        else{ //Insere no meio ou no fim em ordem descrescente (atual->dados.preco < pro.preco)
            no->prox = ant->prox;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int chave){
    if(li == NULL) return 0;    
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.id != chave){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){//Não encontrado (lista vazia ou não existe)
        printf("nao existe\n");
        return 0; 
    } 
    if(no == *li) *li = no->prox; //Remove na primeira posicao
    else ant->prox = no->prox; //Remoção no meio ou fim

    free(no);
    return 1;
}

int altera_quantidade(Lista* li, int chave, int quantMais){ //Nomei como chave para não confudir com id
    if(li == NULL) return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.id != chave){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){
        printf("nao existe\n");
        return 0;
    } 
    else no->dados.quant = no->dados.quant + quantMais;
    return 1;
}

int compra_Produto(Lista* li, int chave){
    if(li == NULL) return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.id != chave){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){ //Produto não existe
        printf("nao existe\n");
        return 0;
    }
    if (no->dados.quant == 0){ //Quantidade do produto = 0
        printf("nao existe\n");
        return 0;
    }
    else{
        no->dados.quant--;
        no->dados.quantVenda++;
    } 
    return 1;
}

int imprime_Lucro(Lista* li){
    if(li == NULL) return 0;
    Elem *ant, *atual = *li;
    while(atual != NULL){
        printf("%d %f\n",atual->dados.id, atual->dados.preco*atual->dados.quantVenda); //Adicionar uma nova variável a estrutura foi o meio mais fácil e rápido de contabilizar a venda
        ant = atual;
        atual = atual->prox;
    }
    return 1;
}

int main(){
    li = cria_lista();
    int entradas, cont=0, opcao, aux; //Auxiliam nas entradas
    int chave, quantMais; // Auxiliam na alteração, remoção e compra
    produtoAuxiliar produto; //Para inserção

    scanf("%d",&entradas);
    while(cont != entradas){
        scanf("%d",&opcao);
        if(opcao == 1){ //Inserção
            scanf("%d %d %f",&produto.id, &produto.quant, &produto.preco);
            produto.quantVenda=0; // Inicio a quantVenda como zero
            insere_lista_ordenada(li, produto);
        }
        if(opcao == 2){ //Altera a quantidade
            scanf("%d %d",&chave, &quantMais);
            aux = altera_quantidade(li, chave, quantMais);
        }
        if(opcao == 3){ //Compra
            scanf("%d",&chave);
            aux = compra_Produto(li, chave);
        }
        if(opcao == 4){ //Remoção
            scanf("%d",&chave);
            aux = remove_lista(li, chave);
        }
        cont++;
    }
    imprime_Lucro(li);
    libera_lista(li);
    return 0;
}