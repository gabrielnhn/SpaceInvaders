

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
	copia_lista( &(jogo->lista), L );
	apaga_lista( &(jogo->lista) );
	inicializa_atual_inicio(L);
	int tam;
	tamanho_lista(&tam, L);

	elemento* e;
	int removeu;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(e, L);
		
		removeu = 0;

		if (e->tipo == tiro_canhao || e->tipo == tiro_alien)
		{
			move_tiro(L, e, i, &removeu);
			processa_colisao(L, e, i, &removeu);
		}

		else if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			move_e_atira_alien(L, e, tocou, mover, atirar, jogo->sentido);
			processa_colisao(L, e, i, &removeu);
		}

		if (e->tipo == barreira)
			processa_colisao(L, e, i, &removeu);

		else if (e->tipo == alien_morrendo)
			removeu = 1;

		else if (e->tipo == canhao)
		{
			move_e_atira_canhao(jogo, e, canhao);
			processa_colisao(L, e, i, &removeu);
			if (removeu)
				jogo->vivo = 0;
		}

		if (!removeu)
			insere_fim_lista(e, &(jogo->lista) )
		
		incrementa_atual(L);
	}

}