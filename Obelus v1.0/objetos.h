typedef struct
{
   int x;
   int y;
   float angulo;
   int vidas;
   int pontos;
   int corrente;
   int corrente_max;

   ALLEGRO_BITMAP *imagem;
}Canhao;

typedef struct
{
   float x;
   float y;
   float velocidade;
   float velocidade_x;
   float velocidade_y;
   int destino;
   bool ativo;
   int valor;
   int bound_x;
   int bound_y;
   int municao;
   float angulo;

   ALLEGRO_BITMAP *imagem;
}Pelota;

typedef struct
{
    int x;
    int y;
    bool ativo;
    int bound_x;
    int bound_y;

    ALLEGRO_BITMAP *imagem;
}Casa;