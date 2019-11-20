void move_esquerda_canhao(elemento* e_canhao)
{
	if ( dentro_da_matriz(e_canhao->i, e_canhao->j - 1) )
		e_canhao->j--;
}

void move_direita_canhao(elemento* e_canhao)
{
	if ( dentro_da_matriz(e_canhao->i, e_canhao->j + 1) )
		e_canhao->j++;
}

void atira_canhao(t_lista* L, elemento* e_canhao)
/* coloca um tiro na posicao acima do canhao na lista L */
{
	elemento e_tiro_canhao;
	e_tiro_canhao.tipo = tiro_canhao;
	e_tiro_canhao.i = e_canhao->i - 1;
	e_tiro_canhao.j = e_canhao->j + 1;

	insere_fim_lista(e_tiro_canhao, L);
}

void move_e_atira_canhao(t_lista* L, elemento* e_canhao, char input)
{
		if (input == input_tiro)
			atira_canhao(L, e_canhao);

		else if (input == input_esquerda)
			move_esquerda_canhao( e_canhao ); /* explicacao na pagina y */

		else if (input == input_direita)
			move_direita_canhao( e_canhao ); /* explicacao na pagina y */
}