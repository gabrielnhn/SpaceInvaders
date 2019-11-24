#ifndef CONFIGS

#define CONFIGS 1

#define _XOPEN_SOURCE 500 /* abilita o uso da biblioteca unistd sem reclamacoes do compilador */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "lib_lista.h"

/* defines normais */
#define milisec 1000
#define constante_inicial_tempo 12
#define VELOCIDADE_MAXIMA (constante_inicial_tempo - 1)
#define QUANTIDADE_TIROS_MAX 1
#define tamanho_alien_x 3
#define tamanho_alien_y 3
#define tamanho_nave_x 8
#define tamanho_nave_y 3
#define tamanho_canhao_x 3
#define tamanho_canhao_y 2

/* inputs e definicoes de esquerda e direita */
#define input_tiro ' '
#define input_esquerda 'a'
#define input_direita 'd'
#define safeword 'q'
#define vazio '0'
#define sentido_direita 1
#define sentido_esquerda 0

/* Tamanho do Tabuleiro */
#define NUM_LINHAS_TABULEIRO 28 
#define NUM_COLUNAS_TABULEIRO 90

/* Linhas e colunas de Aliens */
#define NUM_LINHAS_ALIENS 5
#define NUM_COLUNAS_ALIENS 11
#define NUM_ALIENS (NUM_LINHAS_ALIENS * NUM_COLUNAS_ALIENS) /* numero total de aliens no inicio do jogo */

/*definicao de quais chars representam qual elemento */
#define alien1 'a'
#define alien2 'b'
#define alien3 'c'
#define alien_morrendo 'x'
#define canhao 'd'
#define tiro_canhao '"'
#define tiro_alien '.'
#define barreira '+'
#define nave '9'

/* Desenhos */
/* t = tipo de alien */
#define desenho_t1_line1_s1 "$+$"
#define desenho_t1_line2_s1 "o$o" 
#define desenho_t1_line3_s1 "$+$" 
#define desenho_t1_line1_s2 "$+$"
#define desenho_t1_line2_s2 "@$@"
#define desenho_t1_line3_s2 "$+$"

#define desenho_t2_line1_s1 "#~#"
#define desenho_t2_line2_s1 "[#]" 
#define desenho_t2_line3_s1 "#~#" 
#define desenho_t2_line1_s2 "#~#"
#define desenho_t2_line2_s2 "]#["
#define desenho_t2_line3_s2 "#~#"

#define desenho_t3_line1_s1 "&!&" 
#define desenho_t3_line2_s1 "<&>" 
#define desenho_t3_line3_s1 "&!&" 
#define desenho_t3_line1_s2 "&!&"
#define desenho_t3_line2_s2 ">&<"
#define desenho_t3_line3_s2 "&!&"

#define desenho_tmorrendo_line1 "\\ /"
#define desenho_tmorrendo_line2 " x "
#define desenho_tmorrendo_line3 "/ \\"

#define desenho_canhao_line1 ".^."
#define desenho_canhao_line2 "/~\\"

#define desenho_tiro_canhao "\""
#define desenho_tiro_alien "*"
#define desenho_barreira "H"

#define desenho_nave_line1 "888"
#define desenho_nave_line2 "-Y-"
#define desenho_nave_line3 "\\V/"

/*
struct s_elemento
{
	int i, j;
	char tipo;
};
typedef struct s_elemento elemento;
*/

struct struct_jogo
{
	t_lista lista; /* lista de TUDO */

	int vivo; /* 1 somente se o jogador esta vivo */
	int sentido; /* 'sentido_direita'(1) se os aliens estao indo para direita, 'sentido_esquerda'(0) se para a esquerda */ 
	int quantidade_aliens; /* que estao vivos */
	unsigned long int score; /* pontuacao */
	int velocidade; /* aumenta a cada vez que os aliens tocam as bordas */
	int contador_tempo; /* incrementa a cada 15ms */
	int paralisacao; /* contador de paralisacao */
	int estado_impressao; /* para impressao dos elementos */
};
typedef struct struct_jogo J;


void inicializa_configuracoes();

char ler_input();
/* retorna o input somente se ele for valido, ou seja, utilizavel */ 

int dentro_da_matriz(int i, int j);
/* verifica se o par ordenado (i,j) esta dentro dos limites do tabuleiro */

#endif