#include "colisoes.h"

void move_tiros(t_lista* L, elemento* e, int hora_de_mover_alien, int hora_de_mover_canhao, int* removeu)
/* tenta mover os tiros para suas respectivas posicoes, e se nao puder, os marca para serem removidos */
{
	
	if (e->tipo == tiro_canhao && hora_de_mover_canhao)
	{
		if ( dentro_da_matriz(e->i - 1, e->j) ) 
			e->i--;

		else
			*removeu = 1;
	}
	else if (e->tipo == tiro_alien && hora_de_mover_alien)
	{
		if ( dentro_da_matriz(e->i + 1, e->j) ) 
			e->i++;
		else
			*removeu = 1;
	}
}

int algo_colidiu_na_barreira(int i, int j, t_lista* aux, int* foi_tiro, elemento* tiro)
/* verifica para quase todos os items da lista se algo ocupa a posicao i,j */
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;

	*foi_tiro = 0;
	int x, y, contador_lista;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(&e, aux);
		if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			for(y = e->i; y <= e->i + tamanho_alien_y - 1; y++)
				for(x = e->j; x <= e->j + tamanho_alien_x - 1; x++)
				{
					if (x == j && y == i)
						return 1;
				}
		}

		else if (e->tipo == tiro_canhao || e->tipo == tiro_alien)
		{
			if (e->i == i && e->j == j)
			{
				*foi_tiro = 1;
				tiro->i = i;
				tiro->j = j;
				tiro->tipo = e->tipo;
				return 1;
			}
		}
		incrementa_atual(aux);
	}	
	return 0;
}

int tiro_colidiu_no_alien(int i_comeco, int j_comeco, t_lista* aux, elemento* tiro)
/* verifica se ha algum tiro na regiao alien de ponta i, j */

{
	int tam;
    tamanho_lista(&tam, aux);
    inicializa_atual_inicio(aux);

	elemento* e;
	int contador_lista, i, j;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(&e, aux);
		
		if (e->tipo == tiro_canhao)
		{
			for(i = i_comeco; i <= i_comeco + tamanho_alien_y - 1; i++)
				for(j = j_comeco; j <= j_comeco + tamanho_alien_x - 1; j++)
				{
					if(e->i == i && e->j == j)
					{
						*tiro = *e;
						return 1;
					}
				}
		}

		incrementa_atual(aux);
	}	
	return 0;
}

int algo_colidiu_no_canhao(int i_comeco, int j_comeco, t_lista* aux) 
/* verifica se algo esta na area do canhao */
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;

	int x, y, i, j, contador_lista;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(&e, aux);
		
		for(i = i_comeco; i <= i_comeco + tamanho_canhao_y - 1; i++)
			for(j = j_comeco; j <= j_comeco + tamanho_canhao_x - 1; j++)
			{
				if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
				{
					for(y = e->i; y <= e->i + tamanho_alien_y - 1; y++)
						for(x = e->j; x <= e->j + tamanho_alien_x - 1; x++)
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

void processa_colisao(J* jogo, t_lista* L, elemento* e, int contador_atual, int* removeu)
{
	t_lista aux;
	inicializa_lista(&aux); /* usamos uma lista auxiliar para podermos examinar dois elementos da lista ao mesmo tempo */
	copia_lista(L, &aux, contador_atual);	

	if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
	{
		elemento tiro; 
		if( tiro_colidiu_no_alien(e->i, e->j, &aux, &tiro) )
		/* se um tiro colide no alien, removemos o tiro e marcamos o alien para morrer depois */
		{
			remove_item_especifico(tiro, L, contador_atual);
			e->tipo = alien_morrendo;
		}
	}

	else if (e->tipo == barreira)
	{
		int foi_tiro;
		elemento tiro;
		if( algo_colidiu_na_barreira(e->i, e->j, &aux, &foi_tiro, &tiro) )
		{
			if (foi_tiro)
			/* se um tiro colide na barreira, removemos o tiro e marcamos a barreira para ser removida depois */
				remove_item_especifico(tiro, L, contador_atual);
			
			*removeu = 1;	
		}
	}

	else if (e->tipo == canhao)
	{
		if ( algo_colidiu_no_canhao(e->i, e->j, &aux) )
			*removeu = 1;	
	}

	else if (e->tipo == nave)
	/* fazemos um tratamento especial para a nave pois soh iremos dar o bonus para o jogador se a nave foi atingida,
	 e nao se ela eh simplesmente removida. */
	{
		elemento tiro;
		if ( tiro_colidiu_no_alien(e->i, e->j, &aux, &tiro))
		/* o jogador recebe o bonus e a nave morre */		
		{
			remove_item_especifico(tiro, L, contador_atual);
			
			e->tipo = alien_morrendo;
			e->contador = 8;
		}
		else if ( e->j < 0 )
		/* se a nave passa pela tela sem ser atingida */
			*removeu = 1;
	}

	destroi_lista(&aux);

}
