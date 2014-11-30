//+-----------------------------------------------------------------------------------
//| Funções Relacionadas à identificação de colisão
//+-----------------------------------------------------------------------------------

void troca(Pelota vetor[], int i, int j)// Sort para identificação dos números com menos munição
{
	Pelota aux = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = aux;
}// Fim da função troca()
void bubble_sort(Pelota vetor[], int tamanho)
{
	for (int i = (tamanho - 2); i >= 0; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			if (vetor[j].municao > vetor[j + 1].municao)
				troca(vetor, j, j + 1);
		}// Fim do for menor
	}// Fim do for maior
}// Fim da função bubble_sort()

void colisao_tiros(Pelota tiros[], int tam_tiros, Pelota inimigos[], int tam_inim, Canhao *jogador, ALLEGRO_SAMPLE *explosao)// Verifica colisão do tiro com o inimigo
{
   for (int i = 0; i < tam_tiros; i++)
   {
      if (tiros[i].ativo)// verifica se o tiro está ativo
      {
         for (int j = 0; j < tam_inim; j++)
         {
            if (inimigos[j].ativo)// verifica se o inimigo está ativo
            {
               if (tiros[i].x - tiros[i].bound_x < inimigos[j].x + inimigos[j].bound_x &&
                   tiros[i].x + tiros[i].bound_x > inimigos[j].x - inimigos[j].bound_x &&
                   tiros[i].y - tiros[i].bound_y < inimigos[j].y + inimigos[j].bound_y &&
                   tiros[i].y + tiros[i].bound_y > inimigos[j].y - inimigos[j].bound_y)// verifica se houve colisao
               {
                  al_play_sample(explosao, 1, 0, 1.2, ALLEGRO_PLAYMODE_ONCE, 0);

                  tiros[i].ativo = false;

                  if (inimigos[j].valor % tiros[i].valor == 0)// verifica se os numeros são divisiveis
                  {
                    inimigos[j].valor /= tiros[i].valor;// atualiza valor do inimigo
                    jogador->pontos += 2;// fornece pontuacao ao jogador

                    jogador->corrente++;// aumenta corrente
                    if (jogador->corrente > jogador->corrente_max)
                    	jogador->corrente_max = jogador->corrente;

                    if (jogador->corrente % 7 == 0 && jogador->corrente != 0)// verifica se corrente é multiplo de 7 e recarrega municao caso seja
                    {
                    		Pelota v[5] = {tiros[0], tiros[1], tiros[2], tiros[3], tiros[4]};
                    		bubble_sort(v, 5);

      							for (int k = 0; k < tam_tiros; k++)
      							{
      								if (tiros[k].municao == v[0].municao)
      										tiros[k].municao += 3;
      								else if (tiros[k].municao == v[1].municao)
      										tiros[k].municao += 2;
      								else if (tiros[k].municao == v[2].municao)
      										tiros[k].municao += 2;
      								else if (tiros[k].municao == v[3].municao)
      										tiros[k].municao += 1;
      								else if (tiros[k].municao == v[4].municao)
      										tiros[k].municao += 1;

      								if (tiros[k].municao > 15)
      								  tiros[k].municao = 15;
      							}
                    }
                  }
                  else// reduz pontos do jogador caso numeros não sejam divisiveis
                  {
                    jogador->pontos -= 2;
                    jogador->corrente = 0;
                  }

                  if (inimigos[j].valor == 1)// verifica se jogador destruiu o inimigo
                  {
                    inimigos[j].ativo = false;
                    jogador->pontos += 3;
                  }
               }
            }
         }
      }
   }
}
void colisao_casas(Casa notas[], int tam_notas, Pelota inimigos[], int tam_inimigo, Canhao *jogador, ALLEGRO_SAMPLE *destruicao)// Verifica colisãa entre inimigo e casa
{
    for(int i = 0; i < tam_notas; i++)
    {
        if(notas[i].ativo)// verifica se a casa está ativa
        {
            for(int j = 0; j < tam_inimigo; j++)
            {
                if(inimigos[j].ativo)// verifica se inimigo está ativo
                {
                    if(notas[i].x - notas[i].bound_x < inimigos[j].x + inimigos[j].bound_x &&
                        notas[i].x + notas[i].bound_x > inimigos[j].x - inimigos[j].bound_x &&
                        notas[i].y - notas[i].bound_y - 25 < inimigos[j].y + inimigos[j].bound_y &&
                        notas[i].y + notas[i].bound_y > inimigos[j].y - inimigos[j].bound_y)// verifica se houve colisao
                    {
                        al_play_sample(destruicao, 1, 0, 1.2, ALLEGRO_PLAYMODE_ONCE, 0);

                        notas[i].ativo = false;
                        inimigos[j].ativo = false;
                        jogador->vidas--;
                    }
                }
            }
        }
    }
}