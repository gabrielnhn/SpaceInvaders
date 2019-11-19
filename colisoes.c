#include <stdlib.h> 
#include <time.h>  

void move_tiro(t_lista* L, elemento* e, int contador_atual, int* removeu)
{
	if (e->tipo == tiro_canhao)
	{
		if ( esta_na_matriz(e->i - 1, e->j) ) 
			e->i--;

		else
			*removeu = 1;
	}
	else /* tiro_alien */
	{
		if ( esta_na_matriz(e->i + 1, e->j) ) 
			e->i--;
		else
			*removeu = 1;
	}
	
}

int hora_de_verificar_hitboxes(J* jogo)
{
	if (jogo->contador_tempo % 7 == 0)
		return 1;
	else
		return 0;
}

int tem_algo_em(int i, int j, t_lista* aux)
/* verifica para todos os items da lista se algo ocupa a posicao i,j */
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;

	int x, y, contador_lista;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(e, L);
		if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			for(y = e->i; y <= i + tamanho_alien_y - 1; y++)
				for(x = e->j; x <= j + tamanho_alien_x - 1; x++)
				{
					if (x == j && y == i)
						return 1;
				}
		}

		else
		{
			if (e->i == i && e->j == j)
				return 1;
		}

		incrementa_atual(aux);
	}	
	return 0;
}

int tem_tiro_canhao_na_area(int i, int j, t_lista* aux)
/* verifica se ha algum tiro na regiao alien de ponta i, j */
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;
	int contador_lista, y, x;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(e, L);
		if (e->tipo == tiro_canhao)
		{
			for(y = i; y <= i + tamanho_alien_y - 1; y++)
			{
				for(x = j; x <= j + tamanho_alien_x - 1; x++)
				{
					if (e->i == y && e->j == x)
						return 1;
				}
			}
		}

		incrementa_atual(L);
	}	
	return 0;
}

int tem_tiro_ou_alien_em(int i, int j, t_lista* aux)
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;

	int x, y, contador_lista;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(e, L);
		if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			for(y = e->i; y <= i + tamanho_alien_y - 1; y++)
				for(x = e->j; x <= j + tamanho_alien_x - 1; x++)
				{
					if (x == j && y == i)
						return 1;
				}
		}

		else if (e->tipo == tiro_alien)
		{
			if (e->i == i && e->j == j)
				return 1;
		}

		incrementa_atual(aux);
	}	
	return 0;
}

int tem_tiro_ou_alien_na_area(int i_comeco, int j_comeco, t_lista* aux)
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;

	int x, y, i, j, contador_lista;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(e, L);
		
		for(i = i_comeco; i <= i_comeco + tamanho_canhao_y - 1; i++)
		for(j = j_comeco; j <= j_comeco + tamanho_canhao_x - 1; j++)
		{
			if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
			{
				for(y = e->i; y <= i + tamanho_alien_y - 1; y++)
					for(x = e->j; x <= j + tamanho_alien_x - 1; x++)
					{
						if (x == j && y == i)
							return 1;
					}
			}

			else if (e->tipo == tiro_alien)
			{
				if (e->i == i && e->j == j)
					return 1;
			}
		}
		incrementa_atual(aux);
	}	
	return 0;
}

int tem_barreira(int i, int j, t_lista* aux)
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;

	int contador_lista;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(e, L);
		
		if (e->tipo == barreira)
			if(e->i == i && e->j == j)
				return 1;

		incrementa_atual(aux);
	}	
	return 0;
	
}

void processa_colisao(t_lista* L, elemento* e, int contador_atual, int* removeu)
{
	t_lista aux;
	copia_lista(L, &aux, contador_atual);
	inicializa_atual_inicio(&aux);	

	if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
	{
		if( tem_tiro_canhao_na_area(e->i, e->j, &aux) )
			*removeu = 1;
	}

	else if (e->tipo == barreira)
	{
		if( tem_algo_em(e->i, e->j, &aux) )
		{
			*removeu = 1;	
		}
	}

	else if (e->tipo == canhao)
	{
		if ( tem_tiro_ou_alien_na_area(e->i, e->j, &aux) )
		{
			*removeu = 1;		
		}
	}

	else if (e->tipo == tiro_canhao && *removeu == 0)
	{
		if ( tem_tiro_ou_alien_em(e->i, e->j, &aux) )
			*removeu = 1;	
	}

	else if (e->tipo == tiro_alien && *removeu == 0)
	{
		if (tem_barreira(e->i, e->j, &aux))
			*removeu = 1;
	}

	destroi_lista(&aux);

}

/*
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
*/