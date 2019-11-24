#ifndef MOVIMENTOALIEN


#define MOVIMENTOALIEN 1
#include "configs.h"

void move_direita_alien(elemento* A);

void move_esquerda_alien(elemento* A);

void desce_alien(elemento* A);

int hora_de_mover_aliens(J* jogo);
/* tambem decrementa o contador de paralisacao */

int tocou_borda(J* jogo);
/* retorna 1 se qualquer alien toca alguma das bordas laterais */

void atira_alien(t_lista* L, elemento* A);
/* insere um tiro na lista de elementos */

int hora_de_atirar_aliens(J* jogo);

void move_e_atira_alien(t_lista* L, elemento* e_alien, int tocou, int mover, int atirar, int sentido);
/*  realiza todas as instrucoes que o alien deve fazer na rodada. 
 recebe tocou_borda(), hora_de_mover_aliens() e hora_de_atirar_aliens() como parametro, por motivos de otimizacao */

int hora_de_colocar_nave(J* jogo);

int hora_de_mover_nave(J* jogo);

void colocar_nave(J* jogo);
/* insere a nave mae na lista de elementos */

#endif