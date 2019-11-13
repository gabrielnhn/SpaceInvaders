

void processa_lista(J* jogo, char input)
{
	int mover, tocou, atirar;
	mover = hora_de_mover_aliens(jogo);
	tocou = 0;
	if ( mover )
	{
		mover = 1;
		tocou = tocou_borda();
		if (tocou)
		{
			jogo->sentido = !(jogo->sentido);
			if ( (jogo->velocidade) < VELOCIDADE_MAXIMA)	
				jogo->velocidade++;
		}
	}

	t_lista* L;
	L = &(jogo->lista);

	inicializa_atual_inicio(L);
	int tam;
	tamanho_lista(&tam, L);

	elemento* e;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(e, L)

		if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
			PROCESSA ALIEN;
		
		else if (e->tipo == alien_morrendo)
			MATA_ALIEN;

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