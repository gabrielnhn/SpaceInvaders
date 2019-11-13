#include <stdlib.h> 
#include <time.h>  

void manipula_tiros(J* jogo)
/-- refazer --/
/* move os tiros e faz os mesmos colidirem ENTRE SI */
{
	troca_ponteiros( &(jogo->TirosNovo), &(jogo->TirosAnterior) );
	zera_tabuleiro(jogo->TirosNovo);

	int i, j;
	for(i = 1; i <= NUM_LINHAS_TABULEIRO; i++)
		for (j = 1; j <= NUM_COLUNAS_TABULEIRO; j++)
		{
			/* TIRO DO ALIEN */
			if ( (jogo->TirosAnterior->posi[i][j] == tiro_alien) && dentro_da_matriz(i + 1, j) )
			{ 
				if (jogo->TirosAnterior->posi[i + 1][j] == tiro_canhao)
				/* o lugar em baixo do tiro alien eh um tiro do canhao (eles colidem) */
					jogo->TirosAnterior->posi[i + 1][j] = vazio;
			
				else 
				/* se o lugar em baixo do tiro do alien eh vazio */
					jogo->TirosNovo->posi[i + 1][j] = tiro_alien;
			}
			/* TIRO DO CANHAO */
			else if ( (jogo->TirosAnterior->posi[i][j] ==  tiro_canhao) && dentro_da_matriz(i - 1, j) )
			{
				if (jogo->TirosNovo->posi[i - 1][j] == tiro_alien)
				/* o lugar acima do tiro do canhao eh um tiro de alien*/
					jogo->TirosNovo->posi[i - 1][j] = vazio;
				else
					jogo->TirosNovo->posi[i - 1][j] = tiro_canhao;			
			}
		}
}

/--refazer--/
int coincide_tiro_e_alien(tabuleiro* Aliens, tabuleiro* Tiros, int i, int j)
{
	if (Aliens->posi[i][j] != vazio && Tiros->posi[i][j] == tiro_canhao)
		return 1;
	return 0;
}

/--refazer--/
void remove_do_vetor_aliens(J* jogo, alien array[], int i, int j)
{
	int k = 0;
	while( !(array[k].i == i && array[k].j == j) )
		k++;

	int l;
	for(l = k; l < jogo->quantidade_aliens - 1; l++)
	{
		array[l].i = array[l + 1].i;
		array[l].j = array[l + 1].j;
		array[l].tipo = array[l + 1].tipo;
	}
	jogo->quantidade_aliens = jogo->quantidade_aliens - 1;
}

/--refazer--/
void explode_possiveis_aliens(J* jogo)
{
	int i, j;
	for(i = 1; i <= NUM_LINHAS_TABULEIRO; i++)
		for(j = 1; j <= NUM_COLUNAS_TABULEIRO; j++)
		{
			if ( coincide_tiro_e_alien( &(jogo->Matriz_aliens), jogo->TirosNovo, i, j) )
			{
				remove_do_vetor_aliens(jogo, jogo->array_aliens, i, j);
				jogo->TirosNovo->posi[i][j] = vazio;
			}
		}

}
/--refazer--/
int coincide_tiro_ou_alien_e_barreira(tabuleiro* Canhao, tabuleiro* Tiros, tabuleiro* Aliens, int i, int j)
{
	if (Canhao->posi[i][j] == barreira && (Tiros->posi[i][j] != vazio || Aliens->posi[i][j] != vazio) )
		return 1;
	return 0;
}

/--refazer--/
int coincide_tiro_ou_alien_e_canhao(tabuleiro* Canhao, tabuleiro* Tiros, tabuleiro* Aliens, int i, int j)
{
	if (Canhao->posi[i][j] == desenho_canhao && (Tiros->posi[i][j] == tiro_alien || Aliens->posi[i][j] != vazio) ) 
		return 1;
	return 0;
}

/--refazer--/
void explode_barreira_ou_canhao(J* jogo)
{ 
	int i, j;
	for(i = 1; i <= NUM_LINHAS_TABULEIRO - 1; i++)
		for(j = 1; j <= NUM_COLUNAS_TABULEIRO; j++)
		{
			if ( coincide_tiro_ou_alien_e_barreira( &(jogo->Matriz_canhao), jogo->TirosNovo, &(jogo->Matriz_aliens), i, j ) )
			{
				jogo->Matriz_canhao.posi[i][j] = vazio;
				jogo->TirosNovo->posi[i][j] = vazio;
			}
		}

	for(j = 1; j <= NUM_COLUNAS_TABULEIRO; j++)
		if ( coincide_tiro_ou_alien_e_canhao (&(jogo->Matriz_canhao), jogo->TirosNovo, &(jogo->Matriz_aliens), NUM_LINHAS_TABULEIRO, j ) )
		{
			jogo->vivo = 0;
		}
}

int hora_de_verificar_hitboxes(J* jogo)
{
	if (jogo->contador_tempo % 7 == 0)
		return 1;
	else
		return 0;
}

/--refazer--/
void verifica_hitboxes(J* jogo)
{
	if ( hora_de_verificar_hitboxes(jogo) )
	{
		manipula_tiros(jogo);
		
		int i, j;
		for(i = 1; i <= NUM_LINHAS_TABULEIRO - 1; i++)
			for(j = 1; j <= NUM_COLUNAS_TABULEIRO; j++)
			{
				if ( coincide_tiro_e_alien( &(jogo->Matriz_aliens), jogo->TirosNovo, i, j) )
				{
					remove_do_vetor_aliens(jogo, jogo->array_aliens, i, j);
					jogo->TirosNovo->posi[i][j] = vazio;
				}
				else if ( coincide_tiro_ou_alien_e_barreira( &(jogo->Matriz_canhao), jogo->TirosNovo, &(jogo->Matriz_aliens), i, j ) )
				{
					jogo->Matriz_canhao.posi[i][j] = vazio;
					jogo->TirosNovo->posi[i][j] = vazio;
				}
			}

		for(j = 1; j <= NUM_COLUNAS_TABULEIRO; j++)
			if ( coincide_tiro_ou_alien_e_canhao (&(jogo->Matriz_canhao), jogo->TirosNovo, &(jogo->Matriz_aliens), NUM_LINHAS_TABULEIRO, j ) )
				jogo->vivo = 0;
	}
}
void verifica_hitboxesv1(J* jogo)
{
	if ( hora_de_verificar_hitboxes(jogo) )
	{
		manipula_tiros(jogo);
		explode_possiveis_aliens(jogo);
		explode_barreira_ou_canhao(jogo);	
	}
}
