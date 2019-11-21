int hora_de_mover_tiro_canhao(J* jogo)
{
	if (jogo->contador_tempo % 3 == 0)
		return 1;
	else
		return 0;
}

int hora_de_mover_tiro_alien(J* jogo)
{
	if (jogo->contador_tempo % 4 == 0)
		return 1;
	else
		return 0;
}

void processa_lista(J* jogo, char input)
{
	
	int mover_alien, mover_tiro_alien, mover_tiro_canhao, tocou, atirar;
	tocou = 0;
	atirar = hora_de_atirar_aliens(jogo);
	mover_alien = hora_de_mover_aliens(jogo);
	mover_tiro_alien = hora_de_mover_tiro_alien(jogo);
	mover_tiro_canhao = hora_de_mover_tiro_canhao(jogo);
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
	inicializa_atual_inicio(&L);

	destroi_lista( &(jogo->lista) );
	inicializa_lista( &(jogo->lista) );

	int tam;
	tamanho_lista(&tam, &L);

	elemento* e;
	int removeu;
	int contador_atual;
	for(contador_atual = 1; contador_atual <= tam; contador_atual++)
	{
		consulta_item_atual(&e, &L);
		removeu = 0;

		if (e->tipo == tiro_canhao || e->tipo == tiro_alien)
		{
			move_tiros(&L, e, mover_tiro_alien, mover_tiro_canhao, &removeu);
		}

		else if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			move_e_atira_alien(&(jogo->lista), e, tocou, mover_alien, atirar, jogo->sentido);
			processa_colisao(jogo, &L, e, contador_atual, &removeu);
		}

		else if (e->tipo == barreira)
			processa_colisao(jogo, &L, e, contador_atual, &removeu);

		else if (e->tipo == alien_morrendo)
		{
			if (e->contador == 0)
				removeu = 1;
			else
				e->contador--;
			
		}
		else if (e->tipo == canhao)
		{
			move_e_atira_canhao( &L, e, input, contador_atual);
			processa_colisao(jogo, &L, e, contador_atual, &removeu);
			if (removeu)
				jogo->vivo = 0;
		}

		if (!removeu)
			insere_fim_lista(*e, &(jogo->lista) );
		
		tamanho_lista(&tam, &L);
		incrementa_atual(&L);
	}
	destroi_lista(&L);

}