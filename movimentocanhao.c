void move_esquerda_canhao(elemento* e_canhao)
{

	if ( dentro_da_matriz(e_canhao->i, e_canhao->j - 1) )
		e_canhao->j--;
}

void move_direita_canhao(elemento* e_canhao)
{
	if ( dentro_da_matriz(e_canhao->i, e_canhao->j + 1) )
		e_canhao->j++;
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

void atira_canhao(t_lista* L, elemento* e_canhao)
/* coloca um tiro na posicao acima do canhao no tabuleiro de tiros */
{
	elemento e_tiro_canhao;
	e_tiro_canhao.tipo = tiro_canhao;
	e_tiro_canhao.i = e_canhao->i - 1;
	e_tiro_canhao.j = e_canhao->j + 1;

	insere_inicio_lista(e_tiro_canhao, L);
}

void move_e_atira_canhao(t_lista* L, elemento* e_canhao, char input)
{
		if (input == input_tiro)
			atira_canhao(L, e_canhao);

		else if (input == input_esquerda)
			move_esquerda_canhao( e_canhao ); /* explicacao na pagina y */

		else if (input == input_direita)
			move_direita_canhao( e_canhao ); /* explicacao na pagina y */
}