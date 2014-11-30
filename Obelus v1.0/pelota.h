//+-----------------------------------------------------------------------------------
//| Funções Relacionadas ao Canhao do Jogador
//+-----------------------------------------------------------------------------------
void inicia_tiros(Pelota tiros[], int tamanho)// Inicializa valores dos tiros do jogador
{
   for (int i = 0; i < tamanho; i++)
   {
      tiros[i].velocidade = 15;
      tiros[i].ativo = false;
      tiros[i].bound_x = 11;
      tiros[i].bound_y = 11;
      tiros[i].municao = 15;

   }

   tiros[0].valor = 2;
   tiros[1].valor = 3;
   tiros[2].valor = 5;
   tiros[3].valor = 7;
   tiros[4].valor = 11;
}
void cria_tiro(Pelota tiros[], int posicao, Canhao jogador, ALLEGRO_SAMPLE *tiro)// Cria tiro do jogador
{
   al_play_sample(tiro, .75, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

   tiros[posicao].x = jogador.x;
   tiros[posicao].y = jogador.y + 7;
   tiros[posicao].ativo = true;
   tiros[posicao].velocidade_x = cos(jogador.angulo) * tiros[posicao].velocidade;
   tiros[posicao].velocidade_y = sin(jogador.angulo) * tiros[posicao].velocidade;
   tiros[posicao].municao--;
}
void atira(Pelota tiros[], int posicao, Canhao jogador, ALLEGRO_SAMPLE *tiro)// Atira o numero selecionado
{
   switch (posicao)
   {
      case Q:
         if (!tiros[Q].ativo && tiros[Q].municao > 0)
            cria_tiro(tiros, Q, jogador, tiro);
         break;
      case W:
         if (!tiros[W].ativo && tiros[W].municao > 0)
            cria_tiro(tiros, W, jogador, tiro);
         break;
      case E:
         if (!tiros[E].ativo && tiros[E].municao > 0)
            cria_tiro(tiros, E, jogador, tiro);
         break;
      case R:
         if (!tiros[R].ativo && tiros[R].municao > 0)
            cria_tiro(tiros, R, jogador, tiro);
         break;
      case T:
         if (!tiros[T].ativo && tiros[T].municao > 0)
            cria_tiro(tiros, T, jogador, tiro);
         break;
   }
}
void atualiza_tiros(Pelota tiros[], int tamanho)// Atualiza posição do tiro na tela
{
   for (int i = 0; i < tamanho; i++)
   {
      if (tiros[i].ativo)
      {
         tiros[i].x += tiros[i].velocidade_x;
         tiros[i].y += tiros[i].velocidade_y;

         if(tiros[i].x < 0 || tiros[i].x > LARG || tiros[i].y < 0)// Destroi tiro caso ele escape dos limites da tela
            tiros[i].ativo = false;
      }
   }
}
void desenha_tiros(Pelota tiros[], int tamanho, ALLEGRO_FONT *fonte, ALLEGRO_BITMAP *imagem_tiro)// Desenha tiros na tela
{
	for (int i = 0; i < tamanho; i++)
	{
		if (tiros[i].ativo)// verifica se tiro está ativo
		{
			al_draw_bitmap(imagem_tiro, tiros[i].x - (al_get_bitmap_width(imagem_tiro) / 2), tiros[i].y - (al_get_bitmap_height(imagem_tiro) / 2), 0);
			al_draw_textf(fonte, al_map_rgb(255, 174, 0), tiros[i].x, tiros[i].y - 9, ALLEGRO_ALIGN_CENTRE,
							"%i", tiros[i].valor);
			// al_draw_filled_rectangle(tiros[i].x - tiros[i].bound_x, tiros[i].y - tiros[i].bound_y, tiros[i].x + tiros[i].bound_x, tiros[i].y + tiros[i].bound_y, al_map_rgb(255, 255, 0));
		}
	}
}
void desenha_numeros_disponiveis(Pelota tiros[], int posicao, ALLEGRO_FONT *fonte01, ALLEGRO_FONT *fonte02, ALLEGRO_BITMAP *imagem_base, ALLEGRO_BITMAP *imagem_selecao)// Desenha base com os números disponíveis
{
   al_draw_bitmap(imagem_base, (LARG / 2) - (al_get_bitmap_width(imagem_base) / 2), ALT - al_get_bitmap_height(imagem_base), 0);

	switch (posicao)// desenha quadrado no numero selecionado
	{
		case Q:
			al_draw_bitmap(imagem_selecao, ((LARG / 2) - (al_get_bitmap_width(imagem_selecao) / 2)) - 2 * al_get_bitmap_width(imagem_selecao), ALT - al_get_bitmap_height(imagem_selecao), 0);
			break;
		case W:
			al_draw_bitmap(imagem_selecao, ((LARG / 2) - (al_get_bitmap_width(imagem_selecao) / 2)) - al_get_bitmap_width(imagem_selecao), ALT - al_get_bitmap_height(imagem_selecao), 0);
			break;
		case E:
			al_draw_bitmap(imagem_selecao, (LARG / 2) - (al_get_bitmap_width(imagem_selecao) / 2), ALT - al_get_bitmap_height(imagem_selecao), 0);
			break;
		case R:
			al_draw_bitmap(imagem_selecao, ((LARG / 2) - (al_get_bitmap_width(imagem_selecao) / 2)) + al_get_bitmap_width(imagem_selecao), ALT - al_get_bitmap_height(imagem_selecao), 0);
			break;
		case T:
			al_draw_bitmap(imagem_selecao, ((LARG / 2) - (al_get_bitmap_width(imagem_selecao) / 2)) + 2 * al_get_bitmap_width(imagem_selecao), ALT - al_get_bitmap_height(imagem_selecao), 0);
			break;
	}

   /*Desenha os valores dentro do retangulo*/
   al_draw_textf(fonte01, al_map_rgb(255, 3, 86), ((LARG / 2) + 22) - 2 * al_get_bitmap_width(imagem_selecao), ALT - 47, ALLEGRO_ALIGN_RIGHT,
               "%i", tiros[Q].valor);
   al_draw_textf(fonte01, al_map_rgb(255, 3, 86), ((LARG / 2) + 22) - al_get_bitmap_width(imagem_selecao), ALT - 47, ALLEGRO_ALIGN_RIGHT,
               "%i", tiros[W].valor);
   al_draw_textf(fonte01, al_map_rgb(255, 3, 86), (LARG / 2) + 22, ALT - 47, ALLEGRO_ALIGN_RIGHT,
               "%i", tiros[E].valor);
   al_draw_textf(fonte01, al_map_rgb(255, 3, 86), ((LARG / 2) + 22) + al_get_bitmap_width(imagem_selecao), ALT - 47, ALLEGRO_ALIGN_RIGHT,
               "%i", tiros[R].valor);
   al_draw_textf(fonte01, al_map_rgb(255, 3, 86), ((LARG / 2) + 22) + 2 * al_get_bitmap_width(imagem_selecao), ALT - 47, ALLEGRO_ALIGN_RIGHT,
               "%i", tiros[T].valor);

   // /*Desenha os teclas correspondentes*/
   al_draw_textf(fonte02, al_map_rgb(255, 3, 86), ((LARG / 2) - 21) - 2 * al_get_bitmap_width(imagem_selecao), ALT - 17, ALLEGRO_ALIGN_LEFT,
               "Q");
   al_draw_textf(fonte02, al_map_rgb(255, 3, 86), ((LARG / 2) - 21) - al_get_bitmap_width(imagem_selecao), ALT - 17, ALLEGRO_ALIGN_LEFT,
               "W");
   al_draw_textf(fonte02, al_map_rgb(255, 3, 86), (LARG / 2) - 21, ALT - 17, ALLEGRO_ALIGN_LEFT,
               "E");
   al_draw_textf(fonte02, al_map_rgb(255, 3, 86), ((LARG / 2) - 21) + al_get_bitmap_width(imagem_selecao), ALT - 17, ALLEGRO_ALIGN_LEFT,
               "R");
   al_draw_textf(fonte02, al_map_rgb(255, 3, 86), ((LARG / 2) - 21) + 2 * al_get_bitmap_width(imagem_selecao), ALT - 17, ALLEGRO_ALIGN_LEFT,
               "T");
}
void desenha_municao(Pelota tiros[], ALLEGRO_BITMAP *imagem_selecao)// Desenh amunição disponível na base
{
	float tam = 24 / 15.0 ;
	al_draw_filled_rectangle(((LARG / 2) - 22) - 2 * al_get_bitmap_width(imagem_selecao), ALT - (tiros[0].municao * tam + 20), ((LARG / 2) - 15) - 2 * al_get_bitmap_width(imagem_selecao), ALT - 20, al_map_rgb(2, 152, 115));
	al_draw_filled_rectangle(((LARG / 2) - 22) - al_get_bitmap_width(imagem_selecao), ALT - (tiros[1].municao * tam + 20), ((LARG / 2) - 15) - al_get_bitmap_width(imagem_selecao), ALT - 20, al_map_rgb(2, 152, 115));
	al_draw_filled_rectangle((LARG / 2) - 22, ALT - (tiros[2].municao * tam + 20), (LARG / 2) - 15, ALT - 20, al_map_rgb(2, 152, 115));
	al_draw_filled_rectangle(((LARG / 2) - 22) + al_get_bitmap_width(imagem_selecao), ALT - (tiros[3].municao * tam + 20), ((LARG / 2) - 15) + al_get_bitmap_width(imagem_selecao), ALT - 20, al_map_rgb(2, 152, 115));
	al_draw_filled_rectangle(((LARG / 2) - 22) + 2 * al_get_bitmap_width(imagem_selecao), ALT - (tiros[4].municao * tam + 20), ((LARG / 2) - 15) + 2 * al_get_bitmap_width(imagem_selecao), ALT - 20, al_map_rgb(2, 152, 115));
}