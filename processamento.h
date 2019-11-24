#ifndef PROCESSAMENTO

#define PROCESSAMENTO 1

#include "configs.h"
#include "movimentoalien.h"
#include "movimentocanhao.h"
#include "tela.h"
#include "colisoes.h"

int hora_de_mover_tiro_canhao(J* jogo);

int hora_de_mover_tiro_alien(J* jogo);

void processa_lista(J* jogo, char input);
/* processa todos os elementos da lista de jogo */

#endif