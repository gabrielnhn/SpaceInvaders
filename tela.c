void inicializa_tela()
{
	initscr();              /* inicia a tela */
    noecho();               /* não mostra os caracteres digitados */
    curs_set(FALSE);        /* não mostra o cursor na tela */
}

void imprime_lista(int contador, t_lista* L)
{
	inicializa_atual_inicio(L);
	int tam;
	tamanho_lista(&tam, L);

	elemento* e;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(&e, L);

		if (e->tipo == alien1)
		{
			mvprintw(e->i, e->j, desenho_t1_line1);
			mvprintw(e->i + 1, e->j, desenho_t1_line2);
			mvprintw(e->i + 2, e->j, desenho_t1_line3);
		}
		else if (e->tipo == alien2)
		{
			mvprintw(e->i, e->j, desenho_t2_line1);
			mvprintw(e->i + 1, e->j, desenho_t2_line2);
			mvprintw(e->i + 2, e->j, desenho_t2_line3);
		}
		else if (e->tipo == alien3)
		{
			mvprintw(e->i, e->j, desenho_t3_line1);
			mvprintw(e->i + 1, e->j, desenho_t3_line2);
			mvprintw(e->i + 2, e->j, desenho_t3_line3);
		}
		
		else if (e->tipo == alien_morrendo)
		{
			mvprintw(e->i, e->j, desenho_tmorrendo_line1);
			mvprintw(e->i + 1, e->j, desenho_tmorrendo_line2);
			mvprintw(e->i + 2, e->j, desenho_tmorrendo_line3);
		}

		else if (e->tipo == canhao)
		{
			mvprintw(e->i, e->j, desenho_canhao_line1);
			mvprintw(e->i + 1, e->j, desenho_canhao_line2);
		}
		
		else if (e->tipo == tiro_canhao)
			mvprintw(e->i, e->j, desenho_tiro_canhao);
		
		else if (e->tipo == tiro_alien)
			mvprintw(e->i, e->j, desenho_tiro_alien);

		else if (e->tipo == barreira)
			mvprintw(e->i, e->j, desenho_barreira);

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

void apaga_tela()
{
	int i, j;
	for(i = 1; i <= NUM_LINHAS_TABULEIRO; i++)
		for(j = 1; j <= NUM_COLUNAS_TABULEIRO; j++)
		{
			mvprintw(i, j, " ");
		}
}

void imprime_tela(J* jogo)
{
	apaga_tela();
	imprime_lista( jogo->contador_tempo, &(jogo->lista) );
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
