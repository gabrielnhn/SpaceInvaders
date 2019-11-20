#include <stdlib.h>
#include <stdio.h>
#include "lib_lista.h"

/*
struct t_nodo {
    elemento e;
    struct t_nodo *prox;
    struct t_nodo *prev;
};

typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *atual;
    t_nodo *fim;
    int tamanho;
};
typedef struct t_lista t_lista;
*/

int inicializa_lista(t_lista *l)
/*
    Cria uma lista vazia. Ela eh duplamente encadeada e tem sentinelas no
    inicio e no final. Tambem tem um apontador para um elemento qualquer.
*/
{
    t_nodo* comeco;
    t_nodo* final;

    comeco = (t_nodo*)malloc( sizeof(t_nodo) );
    final = (t_nodo*)malloc( sizeof(t_nodo) );
    if (comeco == NULL || final == NULL)
        return 0;

    l->ini = comeco;
    l->fim = final;

    l->ini->prox = l->fim;
    l->fim->prox = NULL;
    l->fim->prev = l->ini;
    l->ini->prev = NULL;

    l->tamanho = 0;
    return 1;
}


int lista_vazia(t_lista *l)
/*
    Retorna 1 se a lista está vazia e zero caso contrário.
*/
{
    if (l->tamanho == 0)
        return 1;
    return 0;
}

int insere_inicio_lista(elemento e, t_lista *l)
/*
    Insere o elemento item no início da lista.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
{
    t_nodo* novo;
    novo = (t_nodo*)malloc( sizeof(t_nodo) );
    if (novo == NULL)
        return 0;
    
    novo->e = e;
    novo->prox = l->ini->prox;
    novo->prev = l->ini;
    l->ini->prox->prev = novo;
    l->ini->prox = novo;


    l->tamanho++;
    return 1;
}


int tamanho_lista(int *tam, t_lista *l)
/*
    Retorna o tamanho da lista em *tam.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
{
    *tam = l->tamanho;
    return 1;
}

int insere_fim_lista(elemento e, t_lista *l)
/*
    Insere o elemento item no final da lista.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
{
    if ( lista_vazia(l) )
        return ( insere_inicio_lista(e, l) );

    t_nodo* novo;
    novo = (t_nodo*)malloc( sizeof(t_nodo) );
    if (novo == NULL)
        return 0;

    novo->e = e;
    
    l->fim->prev->prox = novo;
    novo->prox = l->fim;
    novo->prev = l->fim->prev;
    l->fim->prev = novo;

    l->tamanho++;
    return 1;
}
int insere_ordenado_lista(elemento e, t_lista *l)
/*
    Insere o elemento item na lista de maneira que ela fique em ordem
    crescente, do início para o final dela.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
{
    if ( lista_vazia(l) )
        return insere_inicio_lista(e, l);
    
    t_nodo* aux;
    aux = l->ini->prox;

    int i;
    for (i = 1; i < (l->tamanho) && (aux->e.tipo) < e.tipo ; i++)
        aux = aux->prox;
    
    /* casos especiais */
    if (i == 1 && (aux->e.tipo) >= e.tipo)
        return insere_inicio_lista(e, l);
      
    if (i >= l->tamanho && (aux->e.tipo) < e.tipo)
        return insere_fim_lista(e, l);
    
    /* caso geral */
    t_nodo* novo;
    novo = (t_nodo*)malloc( sizeof(t_nodo) );
    if (novo == NULL)
        return 0;  

    novo->e = e;
    aux->prev->prox = novo;
    novo->prev = aux->prev;
    novo->prox = aux;
    aux->prev = novo;

    l->tamanho++;
    return 1;
}

int remove_inicio_lista(elemento *e, t_lista *l)
/*
    Remove o primeiro elemento da lista e o retorna em *e.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
{
    if ( lista_vazia(l) )
        return 0;

    t_nodo* auxiliar;
    *e = l->ini->prox->e;
    
    auxiliar = l->ini->prox->prox;
    auxiliar->prev = l->ini;
    free(l->ini->prox);
    l->ini->prox = auxiliar;

    l->tamanho--;
    return 1;
}

int remove_fim_lista(elemento *e, t_lista *l)
/*
    Remove o último elemento da lista e o retorna em *e.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
{
    if ( lista_vazia(l) )
        return 0;
    else if ( l->tamanho == 1 )
        return remove_inicio_lista(e, l);

    *e = l->fim->prev->e;
    t_nodo* auxiliar;

    auxiliar = l->fim->prev->prev;
    free(l->fim->prev);
    l->fim->prev = auxiliar;
    l->fim->prev->prox = l->fim;

    l->tamanho--;
    return 1;
}
/* int remove_item_lista(elemento e, elemento *e_aux, t_lista *l)*/
/*
    Se o elemento chave existir na lista, o retorna em *item.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário
    (elemento não encontrado também retorna zero).
*/
/*
{
    if ( lista_vazia(l) )
        return 0;

    t_nodo* auxiliar;
    auxiliar = l->ini->prox;

    int i;
    for(i = 1; i < (l->tamanho) && auxiliar->e != e; i++)
        auxiliar = auxiliar->prox;

    if ( auxiliar->e != e )
        return 0;

    if (i == l->tamanho)
        return remove_fim_lista(e_aux, l);


    e_aux = auxiliar->e;
    auxiliar->prev->prox = auxiliar->prox;
    auxiliar->prox->prev = auxiliar->prev;
    free(auxiliar);

    l->tamanho--;
    return 1;
}
*/
/* int pertence_lista(elemento e, t_lista *l) */
/*
    Retorna 1 se o elemento contendo a chave e existe na lista,
    caso contrário retorna zero.
*/
/*
{
    if ( lista_vazia(l) )
        return 0;

    t_nodo* auxiliar;
    auxiliar = l->ini->prox;

    int i;
    for(i = 1; i < (l->tamanho) && auxiliar->e != e; i++)
        auxiliar = auxiliar->prox;

    if ( auxiliar->e == e )
        return 1;
    else
        return 0;
}
*/
int inicializa_atual_inicio(t_lista *l)
/* 
    Inicializa o ponteiro atual para o primeiro elemento da lista.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
{
    if ( lista_vazia(l) )
        return 0;
    else
    {
        l->atual = l->ini->prox;
        return 1;
    }
}

int inicializa_atual_fim(t_lista *l)
/* 
    Inicializa o ponteiro atual para o ultimo elemento da lista.
    Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
{
    if ( lista_vazia(l) )
        return 0;
    else
    {
        l->atual = l->fim->prev;
        return 1;
    }
}
void incrementa_atual(t_lista *l)
/*
    Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
    este ponteiro. Se atual estiver apontando para o último, isto é, não 
    tem próximo, retorna NULL.
*/
{
    if (l->atual != NULL)
    { 
        if (l->atual->prox == l->fim)
            l->atual = NULL;
        else
            l->atual = l->atual->prox;
    }
}
void decrementa_atual(t_lista *l)
/*
    Faz o ponteiro atual apontar para o nodo anterior da lista l e retorna 
    este ponteiro. Se atual estiver apontando para o primeiro, isto é, não 
    tem anterior, retorna NULL.
*/
{
    if (l->atual->prev == l->ini)
        l->atual = NULL;
    else
        l->atual = l->atual->prev;
}
int consulta_item_atual(elemento **e, t_lista *l)
/*
    retorna em e o endereco do elemento atual 
    Se atual não for válido a função retorna zero senão retorna 1.
*/
{
    if ( l->atual == NULL )
        return 0;
    else
    {
        *e = &(l->atual->e);
        return 1;
    }
}
int remove_item_atual(elemento *e, t_lista *l)
/*
    Remove o elemento apontado por atual da lista l e o retorna em *e.
    Faz o atual apontar para o sucessor do nodo removido.
    Retorna 1 se houve sucesso e zero caso contrário.
*/
{
    if ( lista_vazia(l) || l->atual == NULL) 
        return 0;
    
    if (l->atual->prox == l->fim)
    {
        l->atual = l->atual->prox;
        return remove_fim_lista(e, l);
    }
    
    if (l->atual->prev == l->ini)
    {
        l->atual = l->atual->prox;
        return remove_inicio_lista(e, l);
    }

    *e = l->atual->e;

    l->atual->prev->prox = l->atual->prox;
    l->atual->prox->prev = l->atual->prev;
    free(l->atual);

    l->tamanho--;
    return 1;

}

void copia_lista(t_lista* A, t_lista* B, int contador_atual_A)
/* nao altera atual */
{
    int tamA;
    tamanho_lista(&tamA, A);


    inicializa_atual_inicio(A);
	elemento* e;
	int i;
	for(i = 1; i <= tamA; i++)
	{
		consulta_item_atual(&e, A);

        insere_fim_lista(*e, B);

		incrementa_atual(A);
	}

    /* recupera atual */
    inicializa_atual_inicio(A);
    for(i = 2; i <= contador_atual_A; i++)
		incrementa_atual(A);
    
}

void apaga_lista(t_lista* l)
{
    elemento auxiliar;
    while ( !lista_vazia(l) )
        remove_inicio_lista(&auxiliar, l);

}

void destroi_lista(t_lista *l)
/*
    Remove todos os elementos da lista e faz com que ela aponte para NULL.
*/
{
    elemento auxiliar;
    while ( !lista_vazia(l) )
        remove_inicio_lista(&auxiliar, l);

    free(l->ini);
    free(l->fim);
    l->ini = NULL;
    l->fim = NULL;
}