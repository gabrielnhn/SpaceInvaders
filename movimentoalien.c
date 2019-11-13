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

int tocou_borda_direita(elemento* A)
{
	if ( (A->j) >= NUM_COLUNAS_TABULEIRO)
		return 1;
	else 
		return 0;
}

int tocou_borda_esquerda(elemento* A)
{
	if ( (A->j) <= 1)
		return 1;
	else
		return 0;
}

int hora_de_mover_aliens(J* jogo)
{
	if ( (jogo->contador_tempo % (constante_inicial_tempo - jogo->velocidade) == 0) && jogo->paralisacao == 0)
		return 1;

	else
		return 0;
}

/--refazer--?/
int tocou_borda(J* jogo, alien array[])
{
	int k;
	for(k = 0; k < jogo->quantidade_aliens; k++)
	{
		if (array[k].j == 1 || array[k].j == NUM_COLUNAS_TABULEIRO)
			return 1;
	}
	return 0;
}

/--refazer--/
void atira_alien(J* jogo, alien A)
{
	jogo->TirosNovo->posi[A.i][A.j] = tiro_alien;
}

int hora_de_atirar_aliens(J* jogo)
{
	if (jogo->contador_tempo % 20 == 0)
		return 1;
	else 
		return 0;
}

void aliens_atiram(J* jogo)
/* aleatoriamente */
{
	int k;
	if ( hora_de_atirar_aliens(jogo) )
	{
		/--refazerfor--/
		for(k = 0; k < jogo->quantidade_aliens; k++)
		{
			if ( (random() % 200) < 1 ) /* 0.5% de chance */
				atira_alien(jogo, jogo->array_aliens[k]);
		}

	}
}

void move_e_atira_aliens(J* jogo)
{
	int k;
	int mover = hora_de_mover_aliens(jogo);
	
	if ( mover &&  tocou_borda(jogo, jogo->array_aliens) )
	{
		/* desce todos os aliens */			
		/--refazerfor--/
		for (k = 0; k < jogo->quantidade_aliens; k++)
			desce_alien( jogo, &(jogo->array_aliens[k]) ); /* explicacao na pagina x */
		
		jogo->sentido = !(jogo->sentido);
		if (jogo->velocidade < VELOCIDADE_MAXIMA)	
			jogo->velocidade++;
	
	}
		/--refazerfor--/
		for(k = 0; k < (jogo->quantidade_aliens); k++)
		{
			if (mover)
			{
				if (jogo->sentido == sentido_direita)
					move_direita_alien(jogo, &(jogo->array_aliens[k]) ); /* explicacao na pagina x */	
				else
					move_esquerda_alien(jogo, &(jogo->array_aliens[k]) );
			}
		
			if ( hora_de_atirar_aliens(jogo) && ( (random() % 200) < 1 ) )
			/* 0.5% de chance */
				atira_alien(jogo, jogo->array_aliens[k]);		
		}

}
