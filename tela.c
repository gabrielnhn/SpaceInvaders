void inicializa_tela()
{
	initscr();              /* inicia a tela */
    noecho();               /* não mostra os caracteres digitados */
    curs_set(FALSE);        /* não mostra o cursor na tela */
}

int hora_de_mudar_estado_impressao(J* jogo)
{
	if (jogo->contador_tempo % 20 == 0)
		return 1;
	else
		return 0;
}

void mudar_estado_impressao(J* jogo)
{
	jogo->estado_impressao = !jogo->estado_impressao;
}

void imprime_lista(int estado, t_lista* L)
{
	inicializa_atual_inicio(L);
	int tam;
	tamanho_lista(&tam, L);

	elemento* e;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(&e, L);

		if (estado == 1)
		{
			if (e->tipo == alien1)
			{
				mvprintw(e->i, e->j, desenho_t1_line1_s1);
				mvprintw(e->i + 1, e->j, desenho_t1_line2_s1);
				mvprintw(e->i + 2, e->j, desenho_t1_line3_s1);
			}
			else if (e->tipo == alien2)
			{
				mvprintw(e->i, e->j, desenho_t2_line1_s1);
				mvprintw(e->i + 1, e->j, desenho_t2_line2_s1);
				mvprintw(e->i + 2, e->j, desenho_t2_line3_s1);
			}
			else if (e->tipo == alien3)
			{
				mvprintw(e->i, e->j, desenho_t3_line1_s1);
				mvprintw(e->i + 1, e->j, desenho_t3_line2_s1);
				mvprintw(e->i + 2, e->j, desenho_t3_line3_s1);
			}
		}
		else
		{
			if (e->tipo == alien1)
			{
				mvprintw(e->i, e->j, desenho_t1_line1_s2);
				mvprintw(e->i + 1, e->j, desenho_t1_line2_s2);
				mvprintw(e->i + 2, e->j, desenho_t1_line3_s2);
			}
			else if (e->tipo == alien2)
			{
				mvprintw(e->i, e->j, desenho_t2_line1_s2);
				mvprintw(e->i + 1, e->j, desenho_t2_line2_s2);
				mvprintw(e->i + 2, e->j, desenho_t2_line3_s2);
			}
			else if (e->tipo == alien3)
			{
				mvprintw(e->i, e->j, desenho_t3_line1_s2);
				mvprintw(e->i + 1, e->j, desenho_t3_line2_s2);
				mvprintw(e->i + 2, e->j, desenho_t3_line3_s2);
			}
		}
		
		if (e->tipo == alien_morrendo)
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
		
		else if (e->tipo == nave)
		{
			mvprintw(e->i, e->j, desenho_nave_line1);
			mvprintw(e->i + 1, e->j, desenho_nave_line2);
			mvprintw(e->i + 2, e->j, desenho_nave_line3);
		}

		incrementa_atual(L);
	}
}

void imprime_borda()
{
	int k; 
	for(k = 0; k <= NUM_COLUNAS_TABULEIRO + 1; k++)
	{
		mvprintw(0, k, ";");
		mvprintw(NUM_LINHAS_TABULEIRO + 1, k, ";");
	}

	for(k = 0; k <= NUM_LINHAS_TABULEIRO + 1; k++)
	{
		mvprintw(k, 0, ";");
		mvprintw(k, NUM_COLUNAS_TABULEIRO + 1, ";");
	}
}


void imprime_tela(J* jogo)
{
	erase();
	imprime_borda();
	imprime_lista( jogo->estado_impressao, &(jogo->lista) );
	refresh();
}

int terminal_valido()
{
	int nlin, ncol;
	getmaxyx(stdscr, nlin, ncol);
	if (nlin > NUM_LINHAS_TABULEIRO + 1 || ncol > NUM_COLUNAS_TABULEIRO + 1)
		return 0;
	else
		return 1;
}

void finaliza_tela()
{
	endwin();
}
