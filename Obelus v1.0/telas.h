//+-----------------------------------------------------------------------------------
//| Funções Relacionadas ao desenho de telas
//+-----------------------------------------------------------------------------------
void desenha_pausa(ALLEGRO_FONT *fonte)// Desenha tela de pausa
{
   al_draw_textf(fonte, al_map_rgb(255, 3, 86), LARG / 2, (ALT / 2) - 230, ALLEGRO_ALIGN_CENTRE,
          "Pausa");
   al_draw_filled_rectangle(0, 0, LARG, ALT, al_map_rgba(0, 0, 0, 127));
   al_draw_textf(fonte, al_map_rgb(190, 190, 190), LARG / 2, (ALT / 2) - 140, ALLEGRO_ALIGN_CENTRE,
          "Menu Inicial");
   al_draw_textf(fonte, al_map_rgb(190, 190, 190), LARG / 2, (ALT / 2) - 50, ALLEGRO_ALIGN_CENTRE,
          "Reiniciar");
   al_draw_textf(fonte, al_map_rgb(190, 190, 190), LARG / 2, (ALT / 2) + 40, ALLEGRO_ALIGN_CENTRE,
          "Sair do Jogo");
}
void desenha_icone(int pos_x, int pos_y, ALLEGRO_COLOR cor)// Desenha icone de divisao
{
   al_draw_line(pos_x, pos_y, pos_x + 30, pos_y, cor, 5);
   al_draw_filled_circle(pos_x + 15, pos_y - 12, 5, cor);
   al_draw_filled_circle(pos_x + 15, pos_y + 10, 5, cor);
}
void desenha_creditos(ALLEGRO_FONT *fonte01, ALLEGRO_FONT *fonte02, ALLEGRO_FONT *fonte03, ALLEGRO_COLOR cor)// desenha tela de créditos
{
   al_draw_filled_rectangle(10, 10, LARG - 10, ALT - 10, al_map_rgba(0, 0, 0, 220));
   al_draw_textf(fonte01, cor, LARG / 2, (ALT / 2) - 300, ALLEGRO_ALIGN_CENTRE,
                        "Obelus");

   al_draw_textf(fonte02, cor, LARG / 2, (ALT / 2) - 200, ALLEGRO_ALIGN_CENTRE,
                        "Projeto Integrador II - Jogo Educacional em 2D");
   al_draw_textf(fonte02, cor, LARG / 2, (ALT / 2) - 170, ALLEGRO_ALIGN_CENTRE,
                        "Bacharelado em Ciência da Computação - Centro Universitário Senac");
   al_draw_textf(fonte02, cor, LARG / 2, (ALT / 2) - 130, ALLEGRO_ALIGN_CENTRE,
                        "Professor Orientador: Thiago Claro");
   al_draw_textf(fonte02, cor, LARG / 2, (ALT / 2) - 100, ALLEGRO_ALIGN_CENTRE,
                        "-----------------------------------------------------------------------------------------------------------------");

   al_draw_textf(fonte03, cor, LARG / 2, (ALT / 2) - 70, ALLEGRO_ALIGN_CENTRE,
                        "Grupo");
   al_draw_textf(fonte02, cor, LARG / 2, (ALT / 2) - 20, ALLEGRO_ALIGN_CENTRE,
                        "Gabriel de Sousa Borges");
   al_draw_textf(fonte02, cor, LARG / 2, (ALT / 2) + 10, ALLEGRO_ALIGN_CENTRE,
                        "Humberto Vieira de Castro");
   al_draw_textf(fonte02, cor, LARG / 2, (ALT / 2) + 40, ALLEGRO_ALIGN_CENTRE,
                        "Mario Roberto Suruagy de Castro");

   al_draw_textf(fonte02, cor, LARG / 2, (ALT / 2) + 120, ALLEGRO_ALIGN_CENTRE,
                        "Design por Junior Magalhães");
}
void desenha_tutorial(ALLEGRO_BITMAP *imagem, ALLEGRO_FONT *fonte, ALLEGRO_COLOR cor)// desenha tela do tutorial
{
	al_draw_filled_rectangle(10, 10, LARG - 10, ALT - 10, al_map_rgba(0, 0, 0, 220));
	al_draw_bitmap(imagem, 50, 35, 0);

	al_draw_filled_rectangle(50, 80, 205, 135, al_map_rgba(0, 0, 0, 220));
	al_draw_textf(fonte, cor, 55, 80, ALLEGRO_ALIGN_LEFT, "Acertar Divisão: 2pts");
	al_draw_textf(fonte, cor, 55, 95, ALLEGRO_ALIGN_LEFT, "Destruir Inimigo: 5pts");
	al_draw_textf(fonte, cor, 55, 110, ALLEGRO_ALIGN_LEFT, "Errar Divisão: -2pts");
	al_draw_line(55, 130, 200, 130, cor, 2);

	al_draw_filled_rectangle(495, 80, 950, 120, al_map_rgba(0, 0, 0, 220));
	al_draw_textf(fonte, cor, 500, 80, ALLEGRO_ALIGN_LEFT, "Acerte os inimigos sem errar as divisões para aumentar sua corrente");
	al_draw_textf(fonte, cor, 500, 95, ALLEGRO_ALIGN_LEFT, "Cada 7 acertos em sequência recuperam um pouco de sua munição!");
	al_draw_line(500, 115, 945, 115, cor, 2);

	al_draw_filled_rectangle(155, (ALT / 2) - 50, 375, (ALT / 2) - 10, al_map_rgba(0, 0, 0, 220));
	al_draw_textf(fonte, cor, 160, (ALT / 2) - 50, ALLEGRO_ALIGN_LEFT, "Acerte os inimigos com numeros");
	al_draw_textf(fonte, cor, 160, (ALT / 2) - 35, ALLEGRO_ALIGN_LEFT, "divisíveis para destruí-los");
	al_draw_line(160, (ALT / 2) - 15, 370, (ALT / 2) - 15, cor, 2);

	al_draw_filled_rectangle((LARG / 2) - 25, (ALT / 2) + 80, (LARG / 2) + 210, (ALT / 2) + 165, al_map_rgba(0, 0, 0, 220));
	al_draw_textf(fonte, cor, (LARG / 2) - 20, (ALT / 2) + 80, ALLEGRO_ALIGN_LEFT, "Mouse: Mirar");
	al_draw_textf(fonte, cor, (LARG / 2) - 20, (ALT / 2) + 95, ALLEGRO_ALIGN_LEFT, "Botão Esquerdo: Atirar");
	al_draw_textf(fonte, cor, (LARG / 2) - 20, (ALT / 2) + 110, ALLEGRO_ALIGN_LEFT, "Rolagem: Selecionar Tiro");
	al_draw_textf(fonte, cor, (LARG / 2) - 20, (ALT / 2) + 125, ALLEGRO_ALIGN_LEFT, "Botões Q/W/E/R/T: Selecionar Tiro");
	al_draw_textf(fonte, cor, (LARG / 2) - 20, (ALT / 2) + 140, ALLEGRO_ALIGN_LEFT, "Escape: Pausar Jogo");
	al_draw_line((LARG / 2) - 20, (ALT / 2) + 160, (LARG / 2) + 205, (ALT / 2) + 160, cor, 2);

  al_draw_filled_rectangle((LARG / 2) - 375, (ALT / 2) + 150, (LARG / 2) - 140, (ALT / 2) + 235, al_map_rgba(0, 0, 0, 220));
  al_draw_textf(fonte, cor, (LARG / 2) - 370, (ALT / 2) + 150, ALLEGRO_ALIGN_LEFT, "Não deixe os inimigos destruirem");
  al_draw_textf(fonte, cor, (LARG / 2) - 370, (ALT / 2) + 165, ALLEGRO_ALIGN_LEFT, "suas torres!");
  al_draw_textf(fonte, cor, (LARG / 2) - 370, (ALT / 2) + 180, ALLEGRO_ALIGN_LEFT, "O jogo termina quando todas as");
  al_draw_textf(fonte, cor, (LARG / 2) - 370, (ALT / 2) + 195, ALLEGRO_ALIGN_LEFT, "torres forem destruidas ou quando");
  al_draw_textf(fonte, cor, (LARG / 2) - 370, (ALT / 2) + 210, ALLEGRO_ALIGN_LEFT, "seus tiros acabarem!");
  al_draw_line((LARG / 2) - 370, (ALT / 2) + 230, (LARG / 2) - 145, (ALT / 2) + 230, cor, 2);
}

void escreveNomeRanking(char *nomeRanking, char digitado, int n)// escreve nome do usuário para ranking
{
  if(n < 6){
    nomeRanking[n] = digitado;
    nomeRanking[n + 1] = '\0';
  }
 
  if(nomeRanking[0] != '\0' && n == 0)
    nomeRanking[0] = (char) (nomeRanking[0] - 32); 
  
}
void envia_ranking(Canhao jogador, char *nome, int *n)// Envia ranking para banco
{
  CURL *url = curl_easy_init();
  
  char pontos[200];
  snprintf(pontos, 200, "http://www.betovieira.url.ph/obelus/inserePontos.php?nome=%s&pontos=%d&streak=%d", nome, jogador.pontos, jogador.corrente_max);

  curl_easy_setopt(url, CURLOPT_URL, pontos);
  curl_easy_perform(url);

  free(url);
  system("google-chrome http://betovieira.url.ph/obelus/");

  nome[0] = '\0';
  *n = 0;
}
