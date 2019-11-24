#ifndef INICIALIZACAO

#define INICIALIZACAO 1

#include "configs.h"

char tipo_do_alien(int linha_relativa);
/* retorna qual sera o tipo do alien de acordo com sua linha relativa */

void cria_alien_na_coordenada(J* jogo, int linha_posicao, int coluna_posicao, int linha_relativa);
/* insere um alien na lista de elementos */

void coloca_aliens(J* jogo);
/* coloca todos os aliens da rodada na lista de elementos */

void coloca_canhao_e_barreiras(J* jogo);
/* na estrutura de jogo */

void inicia_jogo(J* jogo, int velocidade_inicial);
/* usa todas as funcoes inicializa todas as variaveis necessarias para a inicializacao do jogo */

#endif