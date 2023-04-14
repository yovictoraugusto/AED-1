#include <stdio.h>
#include <stdlib.h>

struct sequencia {
  int numero;
};

struct elemento {
  struct elemento *ant;
  struct sequencia dados;
  struct elemento *prox;
};
typedef struct elemento Elem;
typedef struct elemento *Lista;
typedef struct sequencia sequenciaAuxiliar;

Lista *li;

Lista *cria_lista() {
  Lista *li = (Lista *)malloc(sizeof(Lista));
  if (li != NULL)
    *li = NULL;
  return li;
}

void libera_lista(Lista *li) {
  if (li != NULL) {
    Elem *no;
    while ((*li) != NULL) {
      no = *li;
      *li = (*li)->prox;
      free(no);
    }
    free(li);
  }
}

int tamanho_lista(Lista *li) {
  if (li == NULL)
    return 0;
  int cont = 0;
  Elem *no = *li;
  while (no != NULL) {
    cont++;
    no = no->prox;
  }
  return cont;
}

int insere_lista_inicial(int vetor[10]) {
  for (int i = 0; i < 10; i++) {
    if (li == NULL)
      return 0;
    Elem *no = (Elem *)malloc(sizeof(Elem));
    if (no == NULL)
      return 0;
    no->dados.numero = vetor[i];
    no->prox = NULL;
    if (*li == NULL) { // Insere na primeira posicao
      no->ant = NULL;
      *li = no;
    } else {
      Elem *aux = *li;
      while (aux->prox != NULL)
        aux = aux->prox;
      aux->prox = no;
      no->ant = aux;
    }
  }
  return 1;
}

int insere_lista_posicao(Lista *li, int number, int pos) {
  if (li == NULL)
    return 0;
  Elem *no = (Elem *)malloc(sizeof(Elem));
  if (no == NULL)
    return 0;
  no->dados.numero = number;
  no->prox = NULL;
  no->ant = NULL;
  Elem *ante, *atual = *li;
  int i = 0;
  while (atual != NULL && i < pos) {
    ante = atual;
    atual = atual->prox;
    i++;
  }
  if (atual == *li) {
    no->ant = NULL;
    no->prox = (*li);
    (*li)->ant = no;
    *li = no;
  } else {
    no->ant = ante;
    no->prox = ante->prox;
    ante->prox = no;
    if (atual != NULL)
      atual->ant = no;
  }
  return 1;
}

int imprimeLista(Lista *li) {
  if (li == NULL)
    return 0;
  if ((*li) == NULL)
    return 0;
  Elem *no = *li;
  while (no != NULL) {
    printf("%d ", no->dados.numero);
    no = no->prox;
  }
  printf("\n");
  return 1;
}

int remove_caso_especial(Lista *li) {
  Elem *atual = *li, *proximo;
  proximo = atual->prox;
  while (proximo->prox != NULL) {
    proximo = proximo->prox;
  }
  int soma =
      atual->dados.numero + proximo->ant->dados.numero + proximo->dados.numero;//primeiro+antepenultimo+ultimo
  if (soma == 10) {
    (*li) = atual->prox;
    (*li)->ant = NULL;
    free(atual);
    proximo->ant->ant->prox = NULL;
    free(proximo->ant);
    free(proximo);
    return 1;
  }
  soma =
      atual->dados.numero + atual->prox->dados.numero + proximo->dados.numero;//primeiro+segundo+ultimo
  if (soma == 10) {
    (*li) = atual->prox->prox;
    (*li)->ant = NULL;
    free(atual->prox);
    free(atual);
    proximo->ant->prox = NULL;
    free(proximo);
    return 1;
  }
}

int remove_ordenado(Lista *li) {
  if (li == NULL)
    return 0;
  Elem *atual = *li, *ante, *proximo;
  proximo = atual->prox;
  int tamanhoLista = tamanho_lista(li);
  int soma = 0;
  
  while (soma != 10 && proximo->prox != NULL) {
    atual = atual->prox;
    ante = atual->ant;
    proximo = atual->prox;
    soma = atual->dados.numero + ante->dados.numero + proximo->dados.numero;
  }
  if (proximo->prox == NULL && soma != 10) {
    remove_caso_especial(li);
    return 0;
  }
  if(tamanhoLista == 3 && soma == 10){
    (*li) = NULL;
    return 1;
  }
  if (ante->ant == NULL)
    *li = proximo->prox;
  else
    ante->ant->prox = proximo->prox;
  if (proximo->prox != NULL)
    proximo->prox->ant = ante->ant;
  free(atual);
  free(ante);
  free(proximo);
  remove_caso_especial(li);
  return 1;
}

int main() {
  li = cria_lista();
  int i, vetor[10], number, pos;
  for (i = 0; i < 10; i++)
    scanf("%d", &vetor[i]);

  insere_lista_inicial(vetor);
  imprimeLista(li);

  for (i = 0; i < 5; i++) {
    scanf("%d %d", &number, &pos);
    insere_lista_posicao(li, number, pos);
    //imprimeLista(li);
    remove_ordenado(li);
    imprimeLista(li);
  }

  if ((*li) == NULL)
    printf("ganhou");
  else
    printf("perdeu");

  libera_lista(li);
  return 0;
}