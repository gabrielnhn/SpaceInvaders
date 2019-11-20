
char tipo_do_alien(int linha_relativa)
{
	if (linha_relativa == 1)
		return alien3;
	else if (linha_relativa < NUM_LINHAS_ALIENS - 1)
		return alien2;
	else
		return alien1;
}

void cria_alien_na_coordenada(J* jogo, int linha_posicao, int coluna_posicao, int linha_relativa)
{
	elemento A;
	A.i = linha_posicao;
	A.j = coluna_posicao;
	A.tipo = ( tipo_do_alien(linha_relativa) );

	insere_inicio_lista(A, &(jogo->lista) );
}

void coloca_aliens(J* jogo)
{
	jogo->quantidade_aliens = NUM_ALIENS;
	
	int i_relativo, j_relativo;
	int i, j;
	i = 2;
	for(i_relativo = 1; i_relativo <= NUM_LINHAS_ALIENS; i_relativo++)
	{	
		j = 2;
		for(j_relativo = 1; j_relativo <= NUM_COLUNAS_ALIENS; j_relativo++)
		{
			cria_alien_na_coordenada(jogo, i , j , i_relativo);
			j = j + 2 * tamanho_alien_x - 1;
		}
	
		i = i + 2 * tamanho_alien_y - 1;
	}
}



void coloca_canhao_e_barreiras(J* jogo)
{
	elemento e_canhao;

	e_canhao.i = NUM_LINHAS_TABULEIRO - 1;
	e_canhao.j = (NUM_COLUNAS_TABULEIRO / 2);
	e_canhao.tipo = canhao;
	insere_inicio_lista( e_canhao, &(jogo->lista) );
	
	elemento e_barreira;
	e_barreira.tipo = barreira;

	int linha;
	int coluna;
	for(linha = NUM_LINHAS_TABULEIRO - 4; linha <= NUM_LINHAS_TABULEIRO - 2; linha++)
	{
		e_barreira.i = linha;
		for(coluna = 4; coluna <= NUM_COLUNAS_TABULEIRO; coluna++)
		{
			if ( (coluna <= 14) || ( (24 <= coluna) && (coluna <= 34) ) )
			{
				e_barreira.j = coluna;
				insere_inicio_lista( e_barreira, &(jogo->lista) );
			}
		}
	}
}

void inicia_jogo(J* jogo, int velocidade_inicial)
{
	jogo->vivo = 1;
	inicializa_lista( &(jogo->lista) );
	coloca_canhao_e_barreiras(jogo);
	coloca_aliens(jogo);
	jogo->velocidade = velocidade_inicial;
	jogo->sentido = sentido_direita;
	jogo->contador_tempo = 0;
	jogo->quantidade_aliens = NUM_ALIENS;
	jogo->paralisacao = 0;
}
