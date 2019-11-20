#include "lib_lista.h"
#include "configs.c"
#include "inicializacao.c"
#include "movimentoalien.c"
#include "movimentocanhao.c"
#include "colisoes.c"
#include "tela.c"
#include "processamento.c"


void inicializa_estruturas(J* jogo)
{
	inicializa_configuracoes();
	inicializa_tela(); 
}

int morto(J* jogo)
{
	if (jogo->vivo == 1)
		return 0;
	else
		return 1;
}

int ganhou(J* jogo)
{
	return (jogo->quantidade_aliens == 0);
}

int alien_chegou(J* jogo)
/* retorna 1 se, para qualquer alien vivo, seu 'i'(linha) e maior/igual que o numero de linhas do tabuleiro */
{
	t_lista* L;
	L = &(jogo->lista);

	inicializa_atual_inicio(L);
	int tam;
	tamanho_lista(&tam, L);

	elemento* e;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(&e, L);

		if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			if ( e->i + 2 >= NUM_LINHAS_TABULEIRO )
				return 1;
		}

		incrementa_atual(L);
	}	
	
	return 0;
}

int acabou(J* jogo)
{
	if ( morto(jogo) )
		printf("morto\n");
	else if ( alien_chegou(jogo) )
		printf("chegou\n");
	else if ( ganhou(jogo) )
		printf("ganhou\n");
	else 
		return 0;
	return 1;
}

int pediu_pra_sair(char input)
{
	if (input == safeword)
		return 1;
	return 0;
}

void space_invaders(J* jogo, int velocidade_inicial)
{
	inicia_jogo(jogo, velocidade_inicial);
	inicializa_configuracoes();
	imprime_borda();
	char input;
	do 
	{
		imprime_tela(jogo);
		input = ler_input();
		processa_lista( jogo, input );

		usleep(15 * milisec);
		jogo->contador_tempo = jogo->contador_tempo + 1;
	}
	while ( !acabou(jogo) && !pediu_pra_sair(input) );

	if ( pediu_pra_sair(input) )
		printf("pediu\n");

	destroi_lista(&(jogo->lista));

	if ( ganhou(jogo) && !pediu_pra_sair(input) )
		space_invaders(jogo, velocidade_inicial + 3);
	/* space invaders recursivo :O */
}

int main()
{
	if ( !terminal_valido() )
	{
		printf("Tamanho de Terminal Invalido\n");
		return -1;
	}
	J estrutura_jogo;
	J* jogo = &estrutura_jogo;
	inicializa_estruturas(jogo);

	space_invaders(jogo, 1);
	
	finaliza_tela();
	return 9;
}