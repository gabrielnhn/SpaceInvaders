#include "configs.c"
#include "inicializacao.c"
#include "movimentoalien.c"
#include "movimentocanhao.c"
#include "colisoes.c"
#include "tela.c"
#include "posicionamento.c"


void inicializa_estruturas(J* jogo)
{
	inicializa_configuracoes();
	inicializa_tela(); 
}

int morto(J* jogo)
{
	return !(jogo->vivo);
}

int ganhou(J* jogo)
{
	return (jogo->quantidade_aliens == 0);
}

int alien_chegou(J* jogo)
/* retorna 1 se, para qualquer alien vivo, seu 'i'(linha) e maior/igual que o numero de linhas do tabuleiro */
{
	int k;
	/--refazerfor--
	for (k = 0; k < (jogo->quantidade_aliens); k++)
		if ( (jogo->array_aliens[k].i) >= NUM_LINHAS_TABULEIRO )
			return 1;
	return 0;
}

int acabou(J* jogo)
{
	if ( morto(jogo) || alien_chegou(jogo) || ganhou(jogo) )
		return 1;
	return 0;
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
	organiza_tabuleiros(jogo);
	/*imprime_borda();*/
	char input;

	do 
	{
		imprime_tela(jogo);
		input = ler_input();
		
		processa_lista( &(jogo->lista), input );

		usleep(15 * milisec);
		jogo->contador_tempo = jogo->contador_tempo + 1;

	}
	while ( !acabou(jogo) && !pediu_pra_sair(input) );


	destroi_lista(&(jogo->lista))

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
	return 0;
}