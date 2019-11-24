#include "configs.h"

void inicializa_configuracoes()
{
    cbreak();               /* desabilita o buffer de entrada */
	nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
}

char ler_input()
{
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