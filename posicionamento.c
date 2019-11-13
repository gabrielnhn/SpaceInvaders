/*void posiciona_aliens(J* jogo)
posiciona os aliens no tabuleiro T a partir do array de aliens */
/*
{
	int k;
	alien* aux;
	for (k = 0; k < jogo->quantidade_aliens; k++)
	{
		aux = &array[k];
		T->posi[aux->i][aux->j] = aux->tipo;
	}
}

void zera_linha_do_tabuleiro_canhao(tipo_canhao canhao, tabuleiro* T)
{
	int k;
	for(k = 1; k <= NUM_COLUNAS_TABULEIRO; k++)
		T->posi[canhao.i][k] = '0';
}

void posiciona_canhao(tipo_canhao canhao, tabuleiro* T)
{
	T->posi[canhao.i][canhao.j] = desenho_canhao;
}
*/

/*
void organiza_tabuleiros(J* jogo)
{
	zera_tabuleiro( &(jogo->Matriz_aliens) );
	posiciona_aliens(jogo, jogo->array_aliens, &(jogo->Matriz_aliens));
	zera_linha_do_tabuleiro_canhao( jogo->canhao, &(jogo->Matriz_canhao) );
	posiciona_canhao(jogo->canhao, &(jogo->Matriz_canhao) );
}
*/