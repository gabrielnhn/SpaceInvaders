#ifndef TELA

#define TELA 1

#include "configs.h"

void inicializa_tela();

int hora_de_mudar_estado_impressao(J* jogo);

void mudar_estado_impressao(J* jogo);
/* os aliens devem alternar entre seus desenhos. o estado de seu desenho eh chamado
 de "estado de impressao" */

void imprime_lista(int estado, t_lista* L);

void imprime_borda();

void imprime_tela(J* jogo);
 
int terminal_valido();

void finaliza_tela();

#endif