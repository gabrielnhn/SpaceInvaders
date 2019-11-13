void move_esquerda_canhao(elemento* canhao)
{

	if ( dentro_da_matriz(canhao->i, canhao->j - 1) )
		canhao->j--;
}

void move_direita_canhao(elemento* canhao)
{
	if ( dentro_da_matriz(canhao->i, canhao->j + 1) )
		canhao->j++;
}

/*
int pode_atirar_canhao(tabuleiro* Tiros)
nao pode ter mais de 3 tiros no tabuleiro */
/*
{
	int i, j;
	int contador = 0;
	for(i = NUM_LINHAS_TABULEIRO; 1 <= i; i--)
		for(j = NUM_COLUNAS_TABULEIRO; 1 <= j; j--)
		{
			if (Tiros->posi[i][j] == tiro_canhao)
				contador++;
			if (contador > (QUANTIDADE_TIROS - 1))
				return 0;
		}
	return 1;
}
*/
/--refazer--/
void atira_canhao(J* jogo, tipo_canhao canhao)
/* coloca um tiro na posicao acima do canhao no tabuleiro de tiros */
{
	if ( pode_atirar_canhao(jogo->TirosNovo) )
		jogo->TirosNovo->posi[NUM_LINHAS_TABULEIRO][canhao.j] = tiro_canhao; /* explicacao na pagina z */
}

void move_e_atira_canhao(J* jogo, char input)
{
		if (input == input_tiro)
			atira_canhao(jogo, jogo->canhao);

		else if (input == input_esquerda)
			move_esquerda_canhao( &(jogo->canhao) ); /* explicacao na pagina y */

		else if (input == input_direita)
			move_direita_canhao( &(jogo->canhao) ); /* explicacao na pagina y */
}