#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* defines normais */
#define milisec 1000
#define constante_inicial_tempo 15
#define VELOCIDADE_MAXIMA (constante_inicial_tempo - 1)
#define QUANTIDADE_TIROS 1
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
#define NUM_LINHAS_TABULEIRO 40 /* ? */
#define NUM_COLUNAS_TABULEIRO 80 /* ? */
#define COEFICIENTE_SEPARACAO 8 /* ? */

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

#define desenho_t1_line1 "@+@"
#define desenho_t1_line2 "+@+"
#define desenho_t1_line3 "@+@"
#define desenho_t2_line1 "###"
#define desenho_t2_line2 "[#]"
#define desenho_t2_line3 "###"
#define desenho_t3_line1 "&&&"
#define desenho_t3_line2 "<&>"
#define desenho_t3_line3 "&&&"
#define desenho_tmorrendo_line1 "x x"
#define desenho_tmorrendo_line2 " x "
#define desenho_tmorrendo_line3 "x x"
#define borda 'o'
#define desenho_canhao_line1 "~~~"
#define desenho_canhao_line2 "~~~"
#define desenho_tiro_canhao "\""
#define desenho_tiro_alien "."
#define desenho_barreira "+"
#define desenho_nave .

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
	int quantidade_aliens; /* vivos */

	int velocidade;
	int contador_tempo;
	int paralisacao;
};
typedef struct struct_jogo J;

void inicializa_configuracoes()
{
    cbreak();               /* desabilita o buffer de entrada */
	nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
}

char ler_input()
{
	cbreak(); 
	char x;
	x = getch();

	if (x == input_tiro)
		return x;

	else if (x == input_esquerda)
		return x;

	else if (x == input_direita)
		return x;

	else if (x == safeword)
		return x;
	else
		return vazio;	
}

int dentro_da_matriz(int i, int j)
{
	if ( (i <= NUM_LINHAS_TABULEIRO && i >= 1) && (j <= NUM_COLUNAS_TABULEIRO && j >= 1) )
		return 1;
	else 
		return 0;
}