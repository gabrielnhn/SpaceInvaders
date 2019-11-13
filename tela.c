void inicializa_tela()
{
	initscr();              /* inicia a tela */
    noecho();               /* não mostra os caracteres digitados */
    curs_set(FALSE);        /* não mostra o cursor na tela */
}

void imprime_tabuleiros(tabuleiro* A, tabuleiro* B, tabuleiro* C)
/* imprime tabuleiro C por cima de B e B por cima de A */
{
	int i, j;
	for (i = 1; i <= NUM_LINHAS_TABULEIRO; i++)
		for(j = 1; j <= NUM_COLUNAS_TABULEIRO; j++)
		{
			if (C->posi[i][j] != vazio)
				mvprintw(i, j, "%c", C->posi[i][j]);

			else if (B->posi[i][j] != vazio)
				mvprintw(i, j, "%c", B->posi[i][j]);

			else if (A->posi[i][j] != vazio)
				mvprintw(i, j, "%c", A->posi[i][j]);
			
			else
				mvprintw(i, j, " ");
		}
}

void imprime_lista(t_lista* L)
{
	inicializa_atual_inicio(L);
	int tam;
	tamanho_lista(&tam, L);

	elemento* e;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(e, L)

		if (e->tipo == alien1)
			mvprintw(e->i, e->j, desenho_t1);
		
		else if (e->tipo == alien2)
			mvprintw(e->i, e->j, desenho_t2);
		
		else if (e->tipo == alien3)
			mvprintw(e->i, e->j, desenho_t3);
		
		else if (e->tipo == alien_morrendo)
			mvprintw(e->i, e->j, desenho_tmorrendo);

		else if (e->tipo == canhao)
			mvprintw(e->i, e->j, desenho_canhao);
		
		else if (e->tipo == tiro_canhao)
			mvprintw(e->i, e->j, tiro_canhao);
		
		else if (e->tipo == tiro_alien)
			mvprintw(e->i, e->j, tiro_alien);

		else if (e->tipo == barreira)
			mvprintw(e->i, e->j, barreira);

		incrementa_atual(L);
	}
}

void imprime_borda()
{
	int k; 
	for(k = 0; k <= NUM_COLUNAS_TABULEIRO + 1; k++)
	{
		mvprintw(0, k, "%c", borda);
		mvprintw(NUM_LINHAS_TABULEIRO + 1, k, "%c", borda);
	}

	for(k = 0; k <= NUM_LINHAS_TABULEIRO + 1; k++)
	{
		mvprintw(k, 0, "%c", borda);
		mvprintw(k, NUM_COLUNAS_TABULEIRO + 1, "%c", borda);
	}
}

void imprime_tela(J* jogo)
{
	
	imprime_tabuleiros( &(jogo->Matriz_canhao), jogo->TirosNovo, &(jogo->Matriz_aliens) );
	refresh();
}

int terminal_valido()
{
	return 1;
}

void finaliza_tela()
{
	endwin();
}

void finaliza_estruturas()
{
	return;
}
