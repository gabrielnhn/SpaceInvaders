int hora_de_mover_tiro(J* jogo)
{
	if (jogo->contador_tempo % 5 == 0)
		return 1;
	else
		return 0;
}

void processa_lista(J* jogo, char input)
{
	
	int mover_alien, mover_tiro, tocou, atirar;
	tocou = 0;
	atirar = hora_de_atirar_aliens(jogo);
	mover_alien = hora_de_mover_aliens(jogo);
	mover_tiro = hora_de_mover_tiro(jogo);
	if ( mover_alien )
	{
		tocou = tocou_borda(jogo);
		if (tocou)
		{
			jogo->sentido = !(jogo->sentido);
			if ( (jogo->velocidade) < VELOCIDADE_MAXIMA)	
				jogo->velocidade++;
		}
	}

	t_lista L;
	inicializa_lista(&L);

	copia_lista( &(jogo->lista), &L, 1 );
	destroi_lista( &(jogo->lista));
	
	inicializa_lista( &(jogo->lista) );
	inicializa_atual_inicio(&L);

	int tam;
	tamanho_lista(&tam, &L);

	elemento* e;
	int removeu;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(&e, &L);
		
		removeu = 0;

		if (e->tipo == tiro_canhao || e->tipo == tiro_alien)
		{
			move_tiros(&L, e, mover_tiro, &removeu);
			processa_colisao(jogo, &L, e, i, &removeu);
		}

		else if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			move_e_atira_alien(&(jogo->lista), e, tocou, mover_alien, atirar, jogo->sentido);
			processa_colisao(jogo, &L, e, i, &removeu);
		}

		else if (e->tipo == barreira)
			processa_colisao(jogo, &L, e, i, &removeu);

		else if (e->tipo == alien_morrendo)
			removeu = 1;

		else if (e->tipo == canhao)
		{
			move_e_atira_canhao( &(jogo->lista), e, input);
			processa_colisao(jogo, &L, e, i, &removeu);

			if (removeu)
				jogo->vivo = 0;
		}

		if (!removeu)
			insere_fim_lista(*e, &(jogo->lista) );
		
		incrementa_atual(&L);
	}
	destroi_lista(&L);

}