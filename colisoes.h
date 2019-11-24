#ifndef COLISOES

#define COLISOES 1

#include "lib_lista.h"
#include "configs.h"

void move_tiros(t_lista* L, elemento* e, int hora_de_mover_alien, int hora_de_mover_canhao, int* removeu);
/* tenta mover os tiros para suas respectivas posicoes, e se nao puder, os marca para serem removidos */

int algo_colidiu_na_barreira(int i, int j, t_lista* aux, int* foi_tiro, elemento* tiro);
/* verifica para quase todos os items da lista se algo ocupa a posicao i,j */

int tiro_colidiu_no_alien(int i_comeco, int j_comeco, t_lista* aux, elemento* tiro);
/* verifica se ha algum tiro na regiao alien de ponta i, j */

int algo_colidiu_no_canhao(int i_comeco, int j_comeco, t_lista* aux);
/* verifica se algo esta na area do canhao */

void processa_colisao(J* jogo, t_lista* L, elemento* e, int contador_atual, int* removeu);
/* processa a colisao do elemento, ou seja, diz se o mesmo deve ser removido ou nao. */

#endif