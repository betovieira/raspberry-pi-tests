//+-----------------------------------------------------------------------------------
//| Funções Relacionadas ao Casas do jogador
//+-----------------------------------------------------------------------------------
void inicia_casas(Casa *notas, int tam)// Inicializa valores da casa do jogador
{
   int deslocamento = 100;
   for(int i = 0; i < tam; i++)
   {
      notas[i].x = deslocamento;
      notas[i].y = ALT - 25;
      notas[i].ativo = true;
      notas[i].bound_x = 18;
      notas[i].bound_y = 25;

      if(i == 2)
         deslocamento += 300;

         deslocamento += 100;
   }
}
void desenha_casas(Casa *notas, int tam, ALLEGRO_BITMAP *torre)// Desenha casas na tela
{
   for(int i = 0; i < tam; i++)
   {
      if(notas[i].ativo)// Verifica se casa está ativa
      	al_draw_bitmap(torre, notas[i].x - al_get_bitmap_width(torre) / 2, notas[i].y - al_get_bitmap_height(torre) + 25, 0);
      	// al_draw_filled_rectangle(notas[i].x - notas[i].bound_x, notas[i].y - notas[i].bound_y - 25, notas[i].x + notas[i].bound_x, notas[i].y + notas[i].bound_y, al_map_rgba(255, 255, 0, 10));
         
   }
}