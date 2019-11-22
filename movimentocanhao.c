void move_esquerda_canhao(elemento* e_canhao)
{
	if ( dentro_da_matriz(e_canhao->i, e_canhao->j - tamanho_canhao_x) )
		e_canhao->j--;
}

void move_direita_canhao(elemento* e_canhao)
{
	if ( dentro_da_matriz(e_canhao->i, e_canhao->j + tamanho_canhao_x) )
		e_canhao->j++;
}

int pode_atirar_canhao(t_lista* L, int contador_atual)
{
	int tam;
    tamanho_lista(&tam, L);

    inicializa_atual_inicio(L);
	elemento* e;
    int i, contador_tiros;
	contador_tiros = 0;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(&e, L);

		if (e->tipo == tiro_canhao)
			contador_tiros++;
        
		incrementa_atual(L);
	}

    /* recupera atual */
    inicializa_atual_inicio(L);
    for(i = 2; i <= contador_atual; i++)
		incrementa_atual(L);

	if (contador_tiros <= QUANTIDADE_TIROS)
		return 1;
	else
		return 0;
	
}

void atira_canhao(t_lista* L, elemento* e_canhao, int contador_atual)
/* coloca um tiro na posicao acima do canhao na lista L */
{
	if ( pode_atirar_canhao(L, contador_atual) )
	{
		elemento e_tiro_canhao;
		e_tiro_canhao.tipo = tiro_canhao;
		e_tiro_canhao.i = e_canhao->i - 1;
		e_tiro_canhao.j = e_canhao->j + 1;

		insere_fim_lista(e_tiro_canhao, L);
	}
}

void move_e_atira_canhao(t_lista* L, elemento* e_canhao, char input, int contador_atual)
{
		if (input == input_tiro)
			atira_canhao(L, e_canhao, contador_atual);

		else if (input == input_esquerda)
			move_esquerda_canhao( e_canhao ); /* explicacao na pagina y */

		else if (input == input_direita)
			move_direita_canhao( e_canhao ); /* explicacao na pagina y */
}