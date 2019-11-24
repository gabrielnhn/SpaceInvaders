#include "processamento.h"

int hora_de_mover_tiro_canhao(J* jogo)
{
	if (jogo->contador_tempo % 2 == 0)
		return 1;
	else
		return 0;
}

int hora_de_mover_tiro_alien(J* jogo)
{
	if (jogo->contador_tempo % 6 == 0)
		return 1;
	else
		return 0;
}

void processa_lista(J* jogo, char input)
/* processa todos os elementos da lista de jogo */
{
	/* recebe os parametros a partir do estado do jogo */
	int mover_alien, mover_tiro_alien, mover_tiro_canhao, tocou, atirar;
	tocou = 0;
	atirar = hora_de_atirar_aliens(jogo);
	mover_alien = hora_de_mover_aliens(jogo);
	mover_tiro_alien = hora_de_mover_tiro_alien(jogo);
	mover_tiro_canhao = hora_de_mover_tiro_canhao(jogo);
	if ( mover_alien )
	{
		mudar_estado_impressao(jogo);
		tocou = tocou_borda(jogo);
		if (tocou)
		{
			jogo->sentido = !(jogo->sentido);
			if ( (jogo->velocidade) < VELOCIDADE_MAXIMA)	
				jogo->velocidade++;
		}
	}

	/* lista usada por comodidade */
	t_lista *L;
	L = &(jogo->lista);
	inicializa_atual_inicio(L);


	int tam;
	tamanho_lista(&tam, L);

	elemento* e;
	int removeu;
	int contador_atual;
	for(contador_atual = 1; contador_atual <= tam; contador_atual++)
	/* processa cada elemento da lista de acordo com seu tipo */
	{
		consulta_item_atual(&e, L);
		removeu = 0;

		if (e->tipo == tiro_canhao || e->tipo == tiro_alien)
			move_tiros(L, e, mover_tiro_alien, mover_tiro_canhao, &removeu);
		/* so retiramos os tiros diretamente da lista se eles colidem com as 
		  bordas do tabuleiro. eh mais comodo remove-los, quando colidem, ao mesmo 
		  tempo que removemos o elemento a qual eles colidiram. */

		else if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			move_e_atira_alien(L, e, tocou, mover_alien, atirar, jogo->sentido);
			processa_colisao(jogo, L, e, contador_atual, &removeu);
			
			if (e->tipo == alien_morrendo) 
			/* quando um alien colide, nao o retiramos
			 nos o transformamos no tipo "alien morrendo",
			 que tem um contador que diz quanto tempo este fica nesse estado
			 antes de ser removido da lista */
			{
				jogo->quantidade_aliens--;
				e->contador = 8;
				jogo->score = jogo->score + 100;
			}
		}

		else if (e->tipo == barreira)
			processa_colisao(jogo, L, e, contador_atual, &removeu);

		else if (e->tipo == alien_morrendo)
		{
			if (e->contador == 0)
			/* quando o contador chega a 0, retiramos o elemento da lista */
				removeu = 1;
			else
				e->contador--;	
		}

		else if (e->tipo == canhao)
		{
			move_e_atira_canhao(L, e, input, contador_atual);
			processa_colisao(jogo, L, e, contador_atual, &removeu);
			if (removeu)
				jogo->vivo = 0;
		}

		else if (e->tipo == nave)
		{
			if ( hora_de_mover_nave(jogo) )
				move_esquerda_alien(e);

			processa_colisao(jogo, L, e, contador_atual, &removeu);
			if (e->tipo == alien_morrendo)
			{
				jogo->paralisacao = 250;
				jogo->score = jogo->score + 1000;
			}
		}
		
		if (removeu)
		/* se eh necessario remover o elemento que estamos processando: */
		{
			elemento lixo;
			remove_item_atual(&lixo, L); /* coloco o elemento no lixo */
			tamanho_lista(&tam, L); /* atualizo o tamanho da lista, ja que acabamos de tirar um elemento */
			contador_atual--; /* volta-se um elemento na lista, para processarmos todos os elementos. */
		}
		else
			incrementa_atual(L);	
	}

}