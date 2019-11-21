 void move_direita_alien(elemento* A)
{
	A->j++;
}

void move_esquerda_alien(elemento* A)
{
	A->j--;
}

void desce_alien(elemento* A)
{
	A->i++;
}

int hora_de_mover_aliens(J* jogo)
{
	if ( (jogo->contador_tempo % (constante_inicial_tempo - jogo->velocidade) == 0) && jogo->paralisacao == 0)
		return 1;
	else
	{
		if (jogo->paralisacao > 0)
			jogo->paralisacao--;
		
		return 0;
	}
}

int tocou_borda(J* jogo)
{
	t_lista* L;
	L = &(jogo->lista);

	inicializa_atual_inicio(L);
	int tam;
	tamanho_lista(&tam, L);

	elemento *e;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(&e, L);
		if(e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			if (e->j == 1 || e->j + 2 == NUM_COLUNAS_TABULEIRO)
				return 1;
		}
		incrementa_atual(L);
	}
	return 0;
}


void atira_alien(t_lista* L, elemento* A)
{
	elemento e_tiro_alien;
	e_tiro_alien.tipo = tiro_alien;

	e_tiro_alien.i = A->i - 3;
	e_tiro_alien.j = A->j + 1;

	insere_inicio_lista(e_tiro_alien, L );

}

int hora_de_atirar_aliens(J* jogo)
{
	if ( (jogo->contador_tempo % 13 == 0) && jogo->paralisacao == 0 )
		return 1;
	else 
		return 0;
}

void move_e_atira_alien(t_lista* L, elemento* e_alien, int tocou, int mover, int atirar, int sentido)
{
	if ( mover &&  tocou )
	{
		/* desce todos os aliens */			
		desce_alien(e_alien); /* explicacao na pagina x */
	
	}
	if (mover)
	{
			if (sentido == sentido_direita)
				move_direita_alien(e_alien); /* explicacao na pagina x */	
			else
				move_esquerda_alien(e_alien);
	}
	
	if ( atirar && ( (rand() % 200) < 1 ) )
	/* 0.5% de chance */
		atira_alien(L, e_alien);		
}

int hora_de_colocar_nave(J* jogo)
{
	if (jogo->contador_tempo % 700 == 0)
		return 1;
	else
		return 0;
}

int hora_de_mover_nave(J* jogo)
{
	if (jogo->contador_tempo % 3 == 0)
		return 1;
	else
		return 0;
}

void colocar_nave(J* jogo)
{
	elemento e_nave;
	e_nave.tipo = nave;
	e_nave.i = 1;
	e_nave.j = NUM_COLUNAS_TABULEIRO + 1;
	insere_fim_lista(e_nave, &(jogo->lista) );
}