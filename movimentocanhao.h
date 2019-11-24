#ifndef MOVIMENTOCANHAO

#define MOVIMENTOCANHAO 1

#include "configs.h"

void move_direita_canhao(elemento* e_canhao);

void move_esquerda_canhao(elemento* e_canhao);

int pode_atirar_canhao(t_lista* L, int contador_atual);
/* verifica se a quantidade de tiros na lista eh menor que QUANTIDADE_TIROS_MAX, e se sim, retorna 1 */
/* isso tudo sem perder o ponteiro atual */

void atira_canhao(t_lista* L, elemento* e_canhao, int contador_atual);
/* insere um tiro na lista de elementos */

void move_e_atira_canhao(t_lista* L, elemento* e_canhao, char input, int contador_atual);
/* realiza as instrucoes que o canhao deve fazer na rodada */

#endif