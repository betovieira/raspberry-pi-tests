//+-----------------------------------------------------------------------------------
//| Funções Relacionadas ao Canhao do Jogador
//+-----------------------------------------------------------------------------------
void inicia_canhao(Canhao *jogador, ALLEGRO_BITMAP *imagem)// Inicializa valores do canhao jo jogador
{
	jogador->x = LARG / 2;
	jogador->y = ALT - 125;
	jogador->angulo = -PI / 2;
	jogador->vidas = 6;
	jogador->pontos = 0;
	jogador->corrente = 0;
	jogador->corrente_max = 0;

	jogador->imagem = imagem;
}
void atualiza_canhao(Canhao *jogador, float mouse_x, float mouse_y)// Atualiza posição do canhao na tela
{
	int dist_x = mouse_x - jogador->x;
	int dist_y = mouse_y - jogador->y;
	jogador->angulo = atan2(dist_y, dist_x);// Calcula ângulo do canhão

	// controla limite do ângulo do canhão
	if (jogador->angulo > 0 && jogador->angulo < PI / 2)
		jogador->angulo = 0;
	else if (jogador->angulo < -PI || jogador->angulo > PI / 2)
		jogador->angulo = -PI;
}
void desenha_canhao(Canhao jogador, ALLEGRO_BITMAP *canhao_base)// Desenha canhão na tela
{
	al_draw_rotated_bitmap(jogador.imagem, 23, al_get_bitmap_height(jogador.imagem) / 2, jogador.x, jogador.y + 7, jogador.angulo, 0);
	al_draw_bitmap(canhao_base, jogador.x - (al_get_bitmap_width(canhao_base) / 2), jogador.y, 0);
}
void desenha_alvo(int mouse_x, int mouse_y, ALLEGRO_BITMAP *imagem, Pelota tiros[], int posicao, ALLEGRO_FONT *fonte, int estado)// Desenha alvo na tela
{
	al_draw_filled_circle(mouse_x, mouse_y, 26, al_map_rgba(0, 0, 0, 90));
	al_draw_bitmap(imagem, mouse_x - 38, mouse_y - 36.5, 0);

	if (estado == tela_jogo)// Desenha munição no alvo caso esteja na tela de jogo
	{
		float fim;

		switch (posicao)
		{
			case Q:
				fim = ((PI / 2) / 15) * tiros[Q].municao;
				al_draw_textf(fonte, al_map_rgb(255, 3, 86), mouse_x - 3, mouse_y - 19, ALLEGRO_ALIGN_RIGHT,
						"%i", tiros[Q].valor);
				al_draw_arc(mouse_x, mouse_y, 35, PI, fim, al_map_rgb(255, 3, 86), 4);
				break;
			case W:
				fim = ((PI / 2) / 15) * tiros[W].municao;
				al_draw_textf(fonte, al_map_rgb(255, 3, 86), mouse_x - 3, mouse_y - 19, ALLEGRO_ALIGN_RIGHT,
						"%i", tiros[W].valor);
				al_draw_arc(mouse_x, mouse_y, 35, PI, fim, al_map_rgb(255, 3, 86), 4);
				break;
			case E:
				fim = ((PI / 2) / 15) * tiros[E].municao;
				al_draw_textf(fonte, al_map_rgb(255, 3, 86), mouse_x - 3, mouse_y - 19, ALLEGRO_ALIGN_RIGHT,
						"%i", tiros[E].valor);
				al_draw_arc(mouse_x, mouse_y, 35, PI, fim, al_map_rgb(255, 3, 86), 4);
				break;
			case R:
				fim = ((PI / 2) / 15) * tiros[R].municao;
				al_draw_textf(fonte, al_map_rgb(255, 3, 86), mouse_x - 3, mouse_y - 19, ALLEGRO_ALIGN_RIGHT,
						"%i", tiros[R].valor);
				al_draw_arc(mouse_x, mouse_y, 35, PI, fim, al_map_rgb(255, 3, 86), 4);
				break;
			case T:
				fim = ((PI / 2) / 15) * tiros[T].municao;
				al_draw_textf(fonte, al_map_rgb(255, 3, 86), mouse_x - 3, mouse_y - 19, ALLEGRO_ALIGN_RIGHT,
						"%i", tiros[T].valor);
				al_draw_arc(mouse_x, mouse_y, 35, PI, fim, al_map_rgb(255, 3, 86), 4);
				break;
		}
	}
}
