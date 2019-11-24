
#include "inicializacao.h"

char tipo_do_alien(int linha_relativa)
/* retorna qual sera o tipo do alien de acordo com sua linha relativa */
{
	if (linha_relativa == 1)
		return alien3;
	else if (linha_relativa < NUM_LINHAS_ALIENS - 1)
		return alien2;
	else
		return alien1;
}

void cria_alien_na_coordenada(J* jogo, int linha_posicao, int coluna_posicao, int linha_relativa)
/* insere um alien na lista de elementos */
{
	elemento A;
	A.i = linha_posicao;
	A.j = coluna_posicao;
	A.tipo = ( tipo_do_alien(linha_relativa) );

	insere_inicio_lista(A, &(jogo->lista) );
}

void coloca_aliens(J* jogo)
/* coloca todos os aliens da rodada na lista de elementos */
{
	jogo->quantidade_aliens = NUM_ALIENS;
	
	int i_relativo, j_relativo;
	int i, j;
	i = 3;
	for(i_relativo = 1; i_relativo <= NUM_LINHAS_ALIENS; i_relativo++)
	{	
		j = 2;
		for(j_relativo = 1; j_relativo <= NUM_COLUNAS_ALIENS; j_relativo++)
		{
			cria_alien_na_coordenada(jogo, i , j , i_relativo);
			j = j + 2 * tamanho_alien_x - 1;
		}
	
		i = i + 2 * tamanho_alien_y - 2;
	}
}

void coloca_canhao_e_barreiras(J* jogo)
{
	/* insere um canhao na lista de elementos */
	elemento e_canhao;
	e_canhao.i = NUM_LINHAS_TABULEIRO - 1;
	e_canhao.j = (NUM_COLUNAS_TABULEIRO / 2);
	e_canhao.tipo = canhao;
	insere_inicio_lista( e_canhao, &(jogo->lista) );
	

	/* insere varias barreiras na lista de elementos*/
	elemento e_barreira;
	e_barreira.tipo = barreira;

	int linha;
	int coluna;
	int k;
	for(linha = NUM_LINHAS_TABULEIRO - 3; linha <= NUM_LINHAS_TABULEIRO - 2; linha++)
	{
		e_barreira.i = linha;
		for(coluna = 3; coluna <= NUM_COLUNAS_TABULEIRO; coluna+=20)
		{
			for(k = coluna; k <= coluna + 5 && dentro_da_matriz(linha, k); k++)
			{
				e_barreira.j = k;
				insere_inicio_lista( e_barreira, &(jogo->lista) );
			}
		}
	}
}

void inicia_jogo(J* jogo, int velocidade_inicial)
{
	jogo->vivo = 1; /* o canhao esta vivo */
	inicializa_lista( &(jogo->lista) ); /* inicializamos a estrutura a ser usada */
	coloca_canhao_e_barreiras(jogo); 
	coloca_aliens(jogo);
	jogo->velocidade = velocidade_inicial; /* a partir de uma velocidade_inicial dada como parametro */
	jogo->sentido = sentido_direita; /* os aliens comecam indo pra direita */
	jogo->contador_tempo = 0; /* o tempo comeca */
	jogo->quantidade_aliens = NUM_ALIENS; /* todos os aliens estao vivos */ 
	jogo->paralisacao = 0; /* o jogo nao esta paralisado */
	jogo->estado_impressao = 1; /* o jogo comeca no estado de impressao 1 */
}
