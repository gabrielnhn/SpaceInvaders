 vvoid move_direita_alien(elemento* A)
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
	if ( (jogo->contador_tempo % 20 == 0) && jogo->paralisacao == 0 )
		return 1;
	else 
		return 0;
}

void move_e_atira_alien(elemento* e_alien, int tocou, int mover, int atirar, int sentido)
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
	
	if ( atirar && ( (random() % 200) < 1 ) )
	/* 0.5% de chance */
		atira_alien(jogo, e_alien);		
}
