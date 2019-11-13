

void processa_lista(J* jogo, char input)
{
	int mover, tocou, atirar;
	tocou = 0;
	atirar = hora_de_atirar_aliens(jogo);
	mover = hora_de_mover_aliens(jogo);
	if ( mover )
	{
		mover = 1;
		tocou = tocou_borda(jogo);
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
		{
			move_e_atira_alien(L, e, tocou, mover, atirar, jogo->sentido);
			PROCESSA_COLISAO;
		}

		else if (e->tipo == alien_morrendo)
			MATA_ALIEN;

		else if (e->tipo == tiro_canhao || e->tipo == tiro_alien)
			PROCESSA_COLISAO;

		else if (e->tipo == barreira)
			mvprintw(e->i, e->j, barreira);

		else if (e->tipo == canhao)
			move_e_atira_canhao(jogo, e, canhao);

		incrementa_atual(L);
	}	
}