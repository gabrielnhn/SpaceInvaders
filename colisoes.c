#include <stdlib.h> 
#include <time.h>  

void move_tiros(t_lista* L, elemento* e, int contador_atual, int hora_de_mover, int* removeu)
{
	if (hora_de_mover)
	{
		if (e->tipo == tiro_canhao)
		{
			if ( dentro_da_matriz(e->i - 1, e->j) ) 
				e->i--;

			else
				*removeu = 1;
		}
		else /* tiro_alien */
		{
			if ( dentro_da_matriz(e->i + 1, e->j) ) 
				e->i++;
			else
				*removeu = 1;
		}
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

		else if (e->tipo != barreira)
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
		consulta_item_atual(&e, aux);
		
		if (e->tipo == tiro_canhao)
		{
			for(y = i; y <= i + tamanho_alien_y - 1; y++)
				for(x = j; x <= j + tamanho_alien_x - 1; x++)
				{
					if (e->i == y && e->j == x)
						return 1;
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

int tem_tiro_ou_alien_na_area(int i_comeco, int j_comeco, t_lista* aux) /* do canhao */
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

int tem_barreira(int i, int j, t_lista* aux)
{
	int tam;
    tamanho_lista(&tam, aux);
    
    inicializa_atual_inicio(aux);
	elemento* e;

	int contador_lista;
	for(contador_lista = 1; contador_lista <= tam; contador_lista++)
	{
		consulta_item_atual(&e, aux);
		
		if (e->tipo == barreira)
			if(e->i == i && e->j == j)
				return 1;

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
		if( tem_tiro_canhao_na_area(e->i, e->j, &aux) )
		{
			jogo->quantidade_aliens--;
			e->tipo = alien_morrendo;
		}
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
		if ( tem_tiro_ou_alien_na_area(e->i, e->j, &aux) ) /* do canhao */
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
