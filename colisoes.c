#include <stdlib.h> 
#include <time.h>  

void move_tiros(t_lista* L, elemento* e, int hora_de_mover_alien, int hora_de_mover_canhao, int* removeu)
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

int tem_algo_em(int i, int j, t_lista* aux, int* foi_tiro, elemento* tiro)
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

		else if (e->tipo == tiro_canhao)
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

		else if (e->tipo == tiro_alien)
		if (e->i == i /*- 1*/ && e->j == j)
			{
				*foi_tiro = 1;
				tiro->i = e->i;
				tiro->j = e->j;
				tiro->tipo = e->tipo;
				return 1;
			}
		incrementa_atual(aux);
	}	
	return 0;
}

int tem_tiro_canhao_na_area(int i_comeco, int j_comeco, t_lista* aux, elemento* tiro)
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

int tem_tiro_ou_alien_em(int i, int j, t_lista* aux)
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;

	int x, y, contador_lista;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(&e, aux);
		if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			for(y = e->i; y <= e->i + tamanho_alien_x - 1; y++)
				for(x = e->j; x <= e->j + tamanho_alien_y - 1; x++)
				{
					if (x == j && y == i)
						return 1;
				}
		}

		else if (e->tipo == tiro_alien || e->tipo == barreira)
		{
			if (e->i == i && e->j == j)
				return 1;
		}

		incrementa_atual(aux);
	}	
	return 0;
}

int tem_tiro_ou_alien_na_area_do_canhao(int i_comeco, int j_comeco, t_lista* aux) /* do canhao */
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
	inicializa_lista(&aux);
	copia_lista(L, &aux, contador_atual);	

	if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
	{
		elemento tiro;
		if( tem_tiro_canhao_na_area(e->i, e->j, &aux, &tiro) )
		{
			remove_item_especifico(tiro, L, contador_atual);
			remove_item_especifico(tiro, &(jogo->lista), contador_atual);
			e->tipo = alien_morrendo;
		}
	}

	else if (e->tipo == barreira)
	{
		int foi_tiro;
		elemento tiro;
		if( tem_algo_em(e->i, e->j, &aux, &foi_tiro, &tiro) )
		{
			if (foi_tiro)
			{
				if (tiro.tipo == tiro_canhao)
					remove_item_especifico(tiro, L, contador_atual);
				else
					remove_item_especifico(tiro, &(jogo->lista), contador_atual);
			}
			*removeu = 1;	
		}
	}

	else if (e->tipo == canhao)
	{
		if ( tem_tiro_ou_alien_na_area_do_canhao(e->i, e->j, &aux) )
			*removeu = 1;	
	}

	else if (e->tipo == nave)
	{
		elemento tiro;
		if ( tem_tiro_canhao_na_area(e->i, e->j, &aux, &tiro))		
		{
			remove_item_especifico(tiro, L, contador_atual);
			remove_item_especifico(tiro, &(jogo->lista), contador_atual);
			e->tipo = alien_morrendo;
			e->contador = 8;
		}
		else if ( e->j < 0 )
			*removeu = 1;
	}

	destroi_lista(&aux);

}
