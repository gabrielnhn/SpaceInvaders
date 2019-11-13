#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* defines normais */
#define milisec 1000
#define constante_inicial_tempo 25
#define VELOCIDADE_MAXIMA (constante_inicial_tempo - 1)
#define QUANTIDADE_TIROS 4

/* inputs e definicoes de esquerda e direita */
#define input_tiro ' '
#define input_esquerda 'a'
#define input_direita 'd'
#define safeword 'q'
#define vazio '0'
#define sentido_direita 1
#define sentido_esquerda 0

/* Tamanho do Tabuleiro */
#define NUM_LINHAS_TABULEIRO 90 /* ? */
#define NUM_COLUNAS_TABULEIRO 50 /* ? */
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


/* Desenhos */
/* t = tipo de alien */
#define desenho_t1 "@@@\n@@@\n@@@ "
#define desenho_t2 "###\n###\n###"
#define desenho_t3 "&&&\n&&&\n&&&"
#define desenho_tmorrendo "x x\n x \nx x"
#define borda 'o'
#define desenho_canhao " ~ \n~~~"
#define desenho_tiro_canhao "\""
#define desenho_tiro_alien "."
#define desenho_barreira "+"


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