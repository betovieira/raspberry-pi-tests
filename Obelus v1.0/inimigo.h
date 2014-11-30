//+-----------------------------------------------------------------------------------
//| Funções Relacionadas aos Inimigos
//+-----------------------------------------------------------------------------------
void inicia_inimigos(Pelota inimigos[], int tamanho, ALLEGRO_BITMAP *imagem)// Inicializa valores dos inimigos
{
   for (int i = 0; i < tamanho; i++)
   {
      inimigos[i].velocidade = 0.5;
      inimigos[i].ativo = false;
      inimigos[i].bound_x = 22;
      inimigos[i].bound_y = 22;
      inimigos[i].imagem = imagem;
   }
}
void cria_inimigo(Pelota inimigos[], int tamanho, Pelota tiros[], Casa notas[], Canhao *jogador)// Cria inimigos na tela
{
   int max_inimigos = 4 + jogador->pontos / 80;// Determina numero máximo de inimigos na tela de acordo com pontuacao do jogador
   if (max_inimigos > tamanho)
      max_inimigos = tamanho;

   for (int i = 0; i < max_inimigos; i++)
   {
      if (jogador->pontos > 100)// Aumenta velocidade dos inimigos de acordo com pontuacao do jogador
         inimigos[i].velocidade = 0.75;
      if (jogador->pontos > 300)
         inimigos[i].velocidade = 1;
      if (jogador->pontos > 500)
         inimigos[i].velocidade = 1.25;
      if (jogador->pontos > 700)
         inimigos[i].velocidade = 1.5;

      if (!inimigos[i].ativo)// Verifica se inimigo ainda não foi criado
      {
         if (rand() % 500 == 0)// Tenta criar inimigo atraves de um numero aleatório
         {

            inimigos[i].y = 0;
            inimigos[i].ativo = true;

            inimigos[i].x = 30 + rand() % (LARG - 30);// Sorteia posição inicial do inimigo

            int destino;// Sorteia destino do inimigo
            do {
				destino = rand() % 6;
            }while (!notas[destino].ativo);

            switch (destino)// 
            {
				case 0:
					inimigos[i].destino = 100;
					break;
				case 1:
					inimigos[i].destino = 200;
					break;
				case 2:
					inimigos[i].destino = 300;
					break;
				case 3:
					inimigos[i].destino = 700;
					break;
				case 4:
					inimigos[i].destino = 800;
					break;
				case 5:
					inimigos[i].destino = 900;
					break;
            }

            int distX = inimigos[i].destino - inimigos[i].x;// calcula angulo da imagem do inimigo
            int distY = (ALT - 50) - inimigos[i].y;
            float angulo = atan2(distY, distX); 
            inimigos[i].angulo = angulo;

            inimigos[i].velocidade_x = cos(angulo) * inimigos[i].velocidade;// calcula velocidade de deslocamento do inimigo
            inimigos[i].velocidade_y = sin(angulo) * inimigos[i].velocidade;

            /*Calcula o angulo que a imagem vai ficar*/

            inimigos[i].valor = 1;// calcula valor do inimigo
            int vezes = 2 + rand() % 2;
            for (int j = 0; j < vezes; j++)
            {
               int posicao;
               posicao = rand() % 5;
               inimigos[i].valor *= tiros[posicao].valor;
            }
         }
      }
   }
}
void atualiza_inimigos(Pelota inimigos[], int tamanho)// Atualiza posição do inimigo na tela
{
   for (int i = 0; i < tamanho; i++)
   {
      if (inimigos[i].ativo)
      {
         inimigos[i].x += inimigos[i].velocidade_x;
         inimigos[i].y += inimigos[i].velocidade_y;

         if (inimigos[i].y > ALT)// detroi inimigo quando ele alcança o limite inferior da tela
            inimigos[i].ativo = false;
      }
   }
}
void desenha_inimigos(Pelota inimigos[], int tamanho, ALLEGRO_FONT *fonte, bool jogo_pausado)// desenha inimigo na tela
{
   for (int i = 0; i < tamanho; i++)
   {
      if (inimigos[i].ativo)
      {
         al_draw_rotated_bitmap(inimigos[i].imagem, 75, 70, inimigos[i].x, inimigos[i].y, 
            inimigos[i].angulo * PI/5.5, 0);
         // al_draw_filled_rectangle(inimigos[i].x - inimigos[i].bound_x, inimigos[i].y - inimigos[i].bound_y, inimigos[i].x + inimigos[i].bound_x, inimigos[i].y + inimigos[i].bound_y, al_map_rgb(255, 255, 0));

         if (!jogo_pausado)// esconde valor do inimigo caso o jogo esteja pausado
            al_draw_textf(fonte, al_map_rgb(255, 255, 255), inimigos[i].x, inimigos[i].y - 7, ALLEGRO_ALIGN_CENTRE, "%i", inimigos[i].valor);
         else
            al_draw_textf(fonte, al_map_rgb(255, 255, 255), inimigos[i].x, inimigos[i].y - 7, ALLEGRO_ALIGN_CENTRE, "?");
      }
   }
}
void reseta_numeros(Pelota inimigos[], Pelota tiros[], int tamanho)// redefine valores dos inimigos quando o jogo é pausado
{
   for (int i = 0; i < tamanho; i++)
   {
      if (inimigos[i].ativo)
      {
         inimigos[i].valor = 1;
         int vezes = 2 + rand() % 2;
         for (int j = 0; j < vezes; j++)
         {
            int posicao;
            posicao = rand() % 5;
            inimigos[i].valor *= tiros[posicao].valor;
         }
      }
   }
}