/*Declaração de todas as bibliotecas*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <curl/curl.h>

/*Inicialização das constantes de largura e altura de tela*/
const int LARG = 1000;
const int ALT = 700;

/*Inicialização da constante PI*/
const double PI = 3.14159265358979323846;

/*Váriaveis ENUM para melhor identificação dos eventos e mudanças de tela*/
enum TECLAS{Q, W, E, R, T};
enum ESTADO{tela_titulo, tela_jogo, tela_final};

/*Inclusão das structs e funções de cada objeto da tela*/
#include "objetos.h"
#include "canhao.h"
#include "pelota.h"
#include "inimigo.h"
#include "casa.h"
#include "colisao.h"
#include "telas.h"

/*Define o número máximo de objetos na tela*/
#define NUM_TIROS 5
#define NUM_INIMIGOS 6
#define NUM_CASAS 6

/*Inicializa structs*/
Canhao jogador;
Pelota tiros[NUM_TIROS];
Pelota inimigos[NUM_INIMIGOS];
Casa notas[NUM_CASAS];

/*Começa a função principal*/
int main(void)
{
//Inicialização do ALLEGRO
//+------------------------------------------------------------------------------------------------------------------------
	/*Inicializa variáveis de controle de tela*/
	bool tutorial = false;
	bool creditos = false;
	bool jogo_pausado = false;
	bool jogo_finalizado = false;
	bool renderizar = true;
	const int FPS = 60;
	int estado = tela_titulo;
	
	/*Vetor para nome do jogador*/
	char nomeranking[40];
	int n = 0;
	nomeranking[0] = '\0';
	bool ranking_enviado = false;

	/*Define posição do mouse ao iniciar o jogo*/
	float mouse_x = (LARG / 2);
	float mouse_y = (ALT / 2);
	float mouse_z = 0;

	/*Inicializa o tiro que começa selecionado*/
	int tiro_selecionado = 2;

	/*Declara as variaveis ALLEGRO*/
	ALLEGRO_DISPLAY *janela = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *fila_de_eventos = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *imagem_inimigo = NULL;
	ALLEGRO_BITMAP *imagem_alvo = NULL;
	ALLEGRO_BITMAP *imagem_base = NULL;
	ALLEGRO_BITMAP *imagem_selecao = NULL;
	ALLEGRO_BITMAP *imagem_tiro = NULL;
	ALLEGRO_BITMAP *imagem_fundo = NULL;
	ALLEGRO_BITMAP *imagem_fundo_inicio = NULL;
	ALLEGRO_BITMAP *imagem_canhao = NULL;
	ALLEGRO_BITMAP *imagem_canhao_base = NULL;
	ALLEGRO_BITMAP *imagem_torre = NULL;
	ALLEGRO_BITMAP *imagem_tutorial = NULL;
	ALLEGRO_FONT *fonte08 = NULL;
	ALLEGRO_FONT *fonte12 = NULL;
	ALLEGRO_FONT *fonte14 = NULL;
	ALLEGRO_FONT *fonte22 = NULL;
	ALLEGRO_FONT *fonte32 = NULL;
	ALLEGRO_FONT *fontetitulo = NULL;
	ALLEGRO_FONT *fontetitulosmall = NULL;
	ALLEGRO_COLOR cinza;
	ALLEGRO_COLOR preto;
	ALLEGRO_SAMPLE *tiro = NULL;
	ALLEGRO_SAMPLE *explosao = NULL;
	ALLEGRO_SAMPLE *destruicao = NULL;

	/*Inicializa ALLEGRO*/
	if (!al_init())
	{
		fprintf(stderr, "Falha ao carregar allegro5!\n");
		return EXIT_FAILURE;
	}

	/*Cria janela de jogo*/
	al_get_display_mode(0, &disp_data);
	janela = al_create_display(LARG, ALT);
	if (!janela)
	{
		fprintf(stderr, "Falha ao criar janela!\n");
		return EXIT_FAILURE;
	}
	al_set_window_position(janela, (disp_data.width - LARG) / 2, (disp_data.height - ALT) / 2);
	al_set_window_title(janela, "OBELUS");

	/*Instala addons do ALLEGRO que serão utilizados*/
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_init_acodec_addon();

//Inicialização das Variáveis ALLEGRO
//+------------------------------------------------------------------------------------------------------------------------
	/*Cria fila de eventos*/
	fila_de_eventos = al_create_event_queue();
	if (!fila_de_eventos)
	{
		fprintf(stderr, "Falha ao criar fila de eventos!\n");
		return EXIT_FAILURE;
	}
	
	/*Cria timer de controle*/
	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		fprintf(stderr, "Falha ao criar timer!\n");
		return EXIT_FAILURE;
	}

	/*Carrega Imagens do Jogo*/
	imagem_canhao = al_load_bitmap("design/canhao.png");
	if (!imagem_canhao)
	{
		fprintf(stderr, "Falha ao carregar imagem 'canhao.png'\n");
		return EXIT_FAILURE;
	}
	imagem_inimigo = al_load_bitmap("design/meteoro.png");
	if (!imagem_inimigo)
	{
		fprintf(stderr, "Falha ao carregar imagem 'meteoro.png'\n");
		return EXIT_FAILURE;
	}
	imagem_alvo = al_load_bitmap("design/alvo.png");
	if (!imagem_alvo)
	{
		fprintf(stderr, "Falha ao carregar imagem 'alvo.png'\n");
		return EXIT_FAILURE;
	}
	imagem_base = al_load_bitmap("design/basecentro.png");
	if (!imagem_base)
	{
		fprintf(stderr, "Falha ao carregar imagem 'basecentro.png'\n");
		return EXIT_FAILURE;
	}
	imagem_selecao = al_load_bitmap("design/valorselecionado.png");
	if (!imagem_selecao)
	{
		fprintf(stderr, "Falha ao carregar imagem 'valorselecionado.png'\n");
		return EXIT_FAILURE;
	}
	imagem_tiro = al_load_bitmap("design/tirodebaladecanhaomatadora.png");
	if (!imagem_tiro)
	{
		fprintf(stderr, "Falha ao carregar imagem 'tirodebaladecanhaomatadora.png'\n");
		return EXIT_FAILURE;
	}
	imagem_fundo = al_load_bitmap("design/background.jpg");
	if (!imagem_fundo)
	{
		fprintf(stderr, "Falha ao carregar imagem 'background.jpg'\n");
		return EXIT_FAILURE;
	}
	imagem_fundo_inicio = al_load_bitmap("design/fundoinicio.jpg");
	if (!imagem_fundo_inicio)
	{
		fprintf(stderr, "Falha ao carregar imagem 'fundoinicio.jpg'\n");
		return EXIT_FAILURE;
	}
	imagem_canhao_base = al_load_bitmap("design/canhaobase.png");
	if (!imagem_canhao_base)
	{
		fprintf(stderr, "Falha ao carregar imagem 'canhaobase.png'\n");
		return EXIT_FAILURE;
	}
	imagem_torre = al_load_bitmap("design/torre.png");
	if (!imagem_torre)
	{
		fprintf(stderr, "Falha ao carregar imagem 'torre.png'\n");
		return EXIT_FAILURE;
	}
	imagem_tutorial = al_load_bitmap("design/tutorial.jpg");
	if (!imagem_tutorial)
	{
		fprintf(stderr, "Falha ao carregar imagem 'tutorial.jpg'\n");
		return EXIT_FAILURE;
	}

	/*Carrega Fontes Utilizadas*/
	fonte08 = al_load_font("georgiab.ttf", 8, 0);
	if (!fonte08)
	{
		fprintf(stderr, "Falha ao carregar a fonte 'georgia.ttf'\n");
		return EXIT_FAILURE;
	}
	fonte12 = al_load_font("georgiab.ttf", 12, 0);
	if (!fonte12)
	{
		fprintf(stderr, "Falha ao carregar a fonte 'georgia.ttf'\n");
		return EXIT_FAILURE;
	}
	fonte14 = al_load_font("georgiab.ttf", 14, 0);
	if (!fonte14)
	{
		fprintf(stderr, "Falha ao carregar a fonte 'georgia.ttf'\n");
		return EXIT_FAILURE;
	}
		fonte22 = al_load_font("georgiab.ttf", 22, 0);
	if (!fonte22)
	{
		fprintf(stderr, "Falha ao carregar a fonte 'georgia.ttf'\n");
		return EXIT_FAILURE;
	}
	fonte32 = al_load_font("georgiab.ttf", 32, 0);
	if (!fonte32)
	{
		fprintf(stderr, "Falha ao carregar a fonte 'georgia.ttf'\n");
		return EXIT_FAILURE;
	}
	fontetitulo = al_load_font("A Gothique Time .ttf", 250, 0);
	if (!fontetitulo)
	{
		fprintf(stderr, "Falha ao carregar a fonte 'A Gothique Time .ttf'\n");
		return EXIT_FAILURE;
	}
	fontetitulosmall = al_load_font("A Gothique Time .ttf", 100, 0);
	if (!fontetitulosmall)
	{
		fprintf(stderr, "Falha ao carregar a fonte 'A Gothique Time .ttf'\n");
		return EXIT_FAILURE;
	}

	/*Cria define cores utilizadas*/
	cinza = al_map_rgb(190, 190, 190);
	preto = al_map_rgb(0, 0, 0);

	/*Reserva canais de som*/
	al_reserve_samples(10);

	/*Carrega efeitos sonoros*/
	tiro = al_load_sample("sons/Tiro.wav");
	if (!tiro)
	{
		fprintf(stderr, "Falha ao carregar o som 'Tiro.wav'\n");
		return EXIT_FAILURE;
	}
	explosao = al_load_sample("sons/Explosion1.wav");
	if (!explosao)
	{
		fprintf(stderr, "Falha ao carregar o som 'Explosion1.wav'\n");
		return EXIT_FAILURE;
	}
	destruicao = al_load_sample("sons/Explosion2.wav");
	if (!destruicao)
	{
		fprintf(stderr, "Falha ao carregar o som 'Explosion2.wav'\n");
		return EXIT_FAILURE;
	}

//Ultimas Inicializacões
//+------------------------------------------------------------------------------------------------------------------------
	/*Fornece semente para função rand()*/
	srand(time(NULL));

	/*Inicializa os valores das structs*/
	inicia_canhao(&jogador, imagem_canhao);
	inicia_tiros(tiros, NUM_TIROS);
	inicia_inimigos(inimigos, NUM_INIMIGOS, imagem_inimigo);
	inicia_casas(notas, NUM_CASAS);

	/*Registra as fontes de eventos na fila de eventos*/
	al_register_event_source(fila_de_eventos, al_get_keyboard_event_source());
	al_register_event_source(fila_de_eventos, al_get_display_event_source(janela));
	al_register_event_source(fila_de_eventos, al_get_timer_event_source(timer));
	al_register_event_source(fila_de_eventos, al_get_mouse_event_source());
	
	/*Esconde o mouse*/
	al_hide_mouse_cursor(janela);
	
	/*Inicializa o timer*/
	al_start_timer(timer);

//Loop Principal
//+------------------------------------------------------------------------------------------------------------------------
	/*Começa o loop principal do jogo*/
	while (!jogo_finalizado)
	{
		/*inicializa variavel de evento*/
		ALLEGRO_EVENT evento;
		al_wait_for_event(fila_de_eventos, &evento);

		//Atualização de tela
		//+------------------------------------------------------------------------------------------------------------------
		/*Verifica Evento do Timer*/
		if (evento.type == ALLEGRO_EVENT_TIMER)
		{
			/*Permite Renderização da tela*/
			renderizar = true;

			/*Enquanto estiver na tela de jogo atualiza os valores das structs e verifica se houve colisão*/
			if(estado == tela_jogo)
			{
				/*Impede atualização do jogo caso esteja pausado*/
				if (!jogo_pausado)
				{
					atualiza_canhao(&jogador, mouse_x, mouse_y);
					atualiza_tiros(tiros, NUM_TIROS);
					cria_inimigo(inimigos, NUM_INIMIGOS, tiros, notas, &jogador);
					atualiza_inimigos(inimigos, NUM_INIMIGOS);
					colisao_tiros(tiros, NUM_TIROS, inimigos, NUM_INIMIGOS, &jogador, explosao);
					colisao_casas(notas, NUM_CASAS, inimigos, NUM_INIMIGOS, &jogador, destruicao);					
				}

				/*Verifica se as vidas ou munição acabaram e termina o jogo*/
				if(jogador.vidas <= 0 || (tiros[0].municao <= 0 && tiros[1].municao <= 0 && 
					tiros[2].municao <= 0 && tiros[3].municao <= 0 && tiros[4].municao <= 0))
				{
					estado = tela_final;
				}
			}
		}

		//Verificação de Input
		//+------------------------------------------------------------------------------------------------------------------
		/*Verifica fechamento da janela*/
		else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			jogo_finalizado = true;
		}
		/*Verifica pressionamento de tecla do teclado*/
		else if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			/*Verifica qual tecla foi pressionada*/
		 	switch (evento.keyboard.keycode)
		 	{
				/*Pausa jogo ou finaliza, dependendo da tela atual*/
				case ALLEGRO_KEY_ESCAPE:
					if (estado == tela_jogo)
					{
						jogo_pausado = !jogo_pausado;

						if (jogo_pausado)
							reseta_numeros(inimigos, tiros, NUM_INIMIGOS);
					}
					else if(!creditos && !tutorial)
						jogo_finalizado = true;
					break;
				/*Muda o valor do tiro selecionado a partir das teclas do teclado*/
				case ALLEGRO_KEY_Q:
					if (!jogo_pausado)
						tiro_selecionado = Q;
					break;
				case ALLEGRO_KEY_W:
					if (!jogo_pausado)
						tiro_selecionado = W;
					break;
				case ALLEGRO_KEY_E:
					if (!jogo_pausado)
						tiro_selecionado = E;
					break;
				case ALLEGRO_KEY_R:
					if (!jogo_pausado)
						tiro_selecionado = R;
					break;
				case ALLEGRO_KEY_T:
					if (!jogo_pausado)
						tiro_selecionado = T;
					break;
				case ALLEGRO_KEY_ENTER:
					if (estado == tela_final)
					{
						envia_ranking(jogador, nomeranking, &n);
						ranking_enviado = true;
					}
					break;
		 	}

		 	if(evento.keyboard.keycode >= ALLEGRO_KEY_A && evento.keyboard.keycode <= ALLEGRO_KEY_Z && estado == tela_final && !ranking_enviado)
			{
				if(n < 6)
					escreveNomeRanking(nomeranking, (char) evento.keyboard.keycode + 96, n++);
			}
			else if(evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) 
			{
				if(n > 0)
					escreveNomeRanking(nomeranking, '\0', --n);
			}	
		}
		/*Verifica pressionamento de tecla do mouse*/
		else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			/*Atira Pelota*/
			if ((evento.mouse.button & 1 || evento.mouse.button & 2) && !jogo_pausado && estado == tela_jogo)
				atira(tiros, tiro_selecionado, jogador, tiro);

			/*Verifica pressionamento de botões da tela principal*/
			if (estado == tela_titulo)
			{
				if (!creditos && !tutorial)
				{
					if (evento.mouse.x >= (LARG / 2) - 105 && evento.mouse.x <= (LARG / 2) + 105 &&
	                evento.mouse.y >= (ALT / 2) + 18 && evento.mouse.y <= (ALT / 2) + 58) 
					{
		            estado = tela_jogo;
		            ranking_enviado = false;
	            }
	            else if (evento.mouse.x >= (LARG / 2) - 110 && evento.mouse.x <= (LARG / 2) + 110 &&
               	 		evento.mouse.y >= (ALT / 2) + 78 && evento.mouse.y <= (ALT / 2) + 118) 
					{
						tutorial = true;
					}
	            else if (evento.mouse.x >= (LARG / 2) - 70 && evento.mouse.x <= (LARG / 2) + 70 &&
	                		evento.mouse.y >= (ALT / 2) + 138 && evento.mouse.y <= (ALT / 2) + 178) 
					{
						creditos = true;
	            }
					else if (evento.mouse.x >= (LARG / 2) - 100 && evento.mouse.x <= (LARG / 2) + 100 &&
	                		evento.mouse.y >= (ALT / 2) + 198 && evento.mouse.y <= (ALT / 2) + 242) 
					{
		            jogo_finalizado = true;
	            }
				}
				else 
				{
					if (evento.mouse.x >= 10 && evento.mouse.x <= 90 &&
	                evento.mouse.y >= 10 && evento.mouse.y <= 40) 
					{
		            creditos = false;
		            tutorial = false;
	            }
				}				
			}
			/*Verifica pressionamento de botões da tela final*/
			else if (estado == tela_final)
			{
				if (evento.mouse.x >= (LARG / 2) - 300 && evento.mouse.x <= (LARG / 2) - 90 &&
                evento.mouse.y >= (ALT / 2) + 200 && evento.mouse.y <= (ALT / 2) + 242) 
				{
	            estado = tela_titulo;
	            inicia_canhao(&jogador, imagem_canhao);
					inicia_tiros(tiros, NUM_TIROS);
					inicia_inimigos(inimigos, NUM_INIMIGOS, imagem_inimigo);
					inicia_casas(notas, NUM_CASAS);
            }
            else if (evento.mouse.x >= (LARG / 2) + 100 && evento.mouse.x <= (LARG / 2) + 300 &&
                		evento.mouse.y >= (ALT / 2) + 200 && evento.mouse.y <= (ALT / 2) + 242) 
				{
					jogo_finalizado = true;
            } 
            else if(evento.mouse.x >= LARG / 2 + 50 && evento.mouse.x <= LARG / 2 + 220 &&
						evento.mouse.y >= (ALT / 2) + 105 && evento.mouse.y <= (ALT / 2) + 130)
				{
					if (!ranking_enviado)
					{
						envia_ranking(jogador, nomeranking, &n);
						ranking_enviado = true;
					}
				}

			}
			/*Verifica pressionamento de botões da tela de pausa*/
			else if (jogo_pausado)
			{
				if (evento.mouse.x >= (LARG / 2) - 115 && evento.mouse.x <= (LARG / 2) + 115 &&
                evento.mouse.y >= (ALT / 2) - 142 && evento.mouse.y <= (ALT / 2) - 102) 
				{
	            estado = tela_titulo;
	            inicia_canhao(&jogador, imagem_canhao);
					inicia_tiros(tiros, NUM_TIROS);
					inicia_inimigos(inimigos, NUM_INIMIGOS, imagem_inimigo);
					inicia_casas(notas, NUM_CASAS);
					jogo_pausado = false;
            }
            else if (evento.mouse.x >= (LARG / 2) - 80 && evento.mouse.x <= (LARG / 2) + 80 &&
                		evento.mouse.y >= (ALT / 2) - 52 && evento.mouse.y <= (ALT / 2) - 12) 
				{
	            inicia_canhao(&jogador, imagem_canhao);
					inicia_tiros(tiros, NUM_TIROS);
					inicia_inimigos(inimigos, NUM_INIMIGOS, imagem_inimigo);
					inicia_casas(notas, NUM_CASAS);
					jogo_pausado = false;
            }
				else if (evento.mouse.x >= (LARG / 2) - 100 && evento.mouse.x <= (LARG / 2) + 100 &&
                		evento.mouse.y >= (ALT / 2) + 38 && evento.mouse.y <= (ALT / 2) + 82) 
				{
	            jogo_finalizado = true;
            }
			}
		}
		/*Verifica posição do mouse*/
		else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouse_x = evento.mouse.x;
			mouse_y = evento.mouse.y;

			/*Permite selecão de tiro pela roda de rolagem do mouse*/
			if (estado == tela_jogo && !jogo_pausado)
			{
				if (evento.mouse.z > mouse_z)
				{
					tiro_selecionado++;
					if (tiro_selecionado > 4)
						tiro_selecionado = 4;				
				}
				else if (evento.mouse.z < mouse_z)
				{
					tiro_selecionado--;
					if (tiro_selecionado < 0)
						tiro_selecionado = 0;
				}

				mouse_z = evento.mouse.z;
			}
		}

		//Renderização de Tela
		//+------------------------------------------------------------------------------------------------------------------
		if(renderizar && al_is_event_queue_empty(fila_de_eventos))
		{
			renderizar = false;

			/*Desenha tela de título*/
			if(estado == tela_titulo)
			{
				al_draw_bitmap(imagem_fundo_inicio, 0, 0, 0);

				al_draw_filled_rectangle((LARG / 2) - 190, (ALT / 2) - 150, (LARG / 2) + 190, (ALT / 2) - 120, al_map_rgba(0, 0, 0, 20));
				al_draw_filled_circle(LARG / 2, (ALT / 2) - 260, 35, al_map_rgba(0, 0, 0, 20));
				al_draw_filled_circle(LARG / 2, (ALT / 2) - 10, 35, al_map_rgba(0, 0, 0, 20));

				al_draw_textf(fontetitulo, al_map_rgb(0, 0, 0), LARG / 2, (ALT / 2) - 250, ALLEGRO_ALIGN_CENTRE,
								"Obelus");
				al_draw_textf(fonte32, al_map_rgb(0, 0, 0), LARG / 2, (ALT / 2) + 20, ALLEGRO_ALIGN_CENTRE,
								"Iniciar Jogo");
				al_draw_textf(fonte32, al_map_rgb(0, 0, 0), LARG / 2, (ALT / 2) + 80, ALLEGRO_ALIGN_CENTRE,
								"Como Jogar");
				al_draw_textf(fonte32, al_map_rgb(0, 0, 0), LARG / 2, (ALT / 2) + 140, ALLEGRO_ALIGN_CENTRE,
								"Créditos");
				al_draw_textf(fonte32, al_map_rgb(0, 0, 0), LARG / 2, (ALT / 2) + 200, ALLEGRO_ALIGN_CENTRE,
								"Sair do Jogo");

				if (tutorial)
				{
					desenha_tutorial(imagem_tutorial, fonte12, cinza);

					al_draw_textf(fonte22, cinza, 13, 13, ALLEGRO_ALIGN_LEFT,
								"Voltar");
					if (mouse_x >= 10 && mouse_x <= 90 &&
	                mouse_y >= 10 && mouse_y <= 40) 
					   al_draw_line(12, 40, 90, 40, cinza, 3);
				}
				else if (creditos)
				{
					desenha_creditos(fontetitulosmall, fonte22, fonte32, cinza);

					al_draw_textf(fonte22, cinza, 13, 13, ALLEGRO_ALIGN_LEFT,
								"Voltar");
					if (mouse_x >= 10 && mouse_x <= 90 &&
	                mouse_y >= 10 && mouse_y <= 40) 
					   al_draw_line(12, 40, 90, 40, cinza, 3);
				}
				else
				{
					if (mouse_x >= (LARG / 2) - 105 && mouse_x <= (LARG / 2) + 105 &&
               	 mouse_y >= (ALT / 2) + 18 && mouse_y <= (ALT / 2) + 58) 
					{
						desenha_icone((LARG / 2) + 110, (ALT / 2) + 40, preto);
					}
					else if (mouse_x >= (LARG / 2) - 110 && mouse_x <= (LARG / 2) + 110 &&
               	 		mouse_y >= (ALT / 2) + 78 && mouse_y <= (ALT / 2) + 118) 
					{
						desenha_icone((LARG / 2) + 110, (ALT / 2) + 100, preto);
					}
					else if (mouse_x >= (LARG / 2) - 70 && mouse_x <= (LARG / 2) + 70 &&
               	 		mouse_y >= (ALT / 2) + 138 && mouse_y <= (ALT / 2) + 178) 
					{
						desenha_icone((LARG / 2) + 80, (ALT / 2) + 160, preto);
					}
					else if (mouse_x >= (LARG / 2) - 100 && mouse_x <= (LARG / 2) + 100 &&
               	 		mouse_y >= (ALT / 2) + 198 && mouse_y <= (ALT / 2) + 242) 
					{
						desenha_icone((LARG / 2) + 110, (ALT / 2) + 220, preto);
					}
				}

				desenha_alvo(mouse_x, mouse_y, imagem_alvo, tiros, tiro_selecionado, fonte14, estado);
			}
			/*Desenha tela de jogo*/
			else if(estado == tela_jogo)
			{
				al_draw_bitmap(imagem_fundo, -180, 0, 0);
				desenha_tiros(tiros, NUM_TIROS, fonte14, imagem_tiro);
				desenha_inimigos(inimigos, NUM_INIMIGOS, fonte12, jogo_pausado);
				desenha_canhao(jogador, imagem_canhao_base);
				desenha_numeros_disponiveis(tiros, tiro_selecionado, fonte22, fonte12, imagem_base, imagem_selecao);
				desenha_casas(notas, NUM_CASAS, imagem_torre);
				desenha_municao(tiros, imagem_selecao);

				al_draw_filled_rectangle(0, 0, LARG, 50, al_map_rgba(0, 0, 0, 127));
				al_draw_textf(fonte14, al_map_rgb(255, 174, 0), 3, 18, ALLEGRO_ALIGN_LEFT,
								"Pontuação: %i", jogador.pontos);
				al_draw_textf(fonte14, al_map_rgb(255, 174, 0), LARG - 3, 3, ALLEGRO_ALIGN_RIGHT,
								"Corrente: %i", jogador.corrente);
				al_draw_textf(fonte14, al_map_rgb(255, 174, 0), LARG - 3, 28, ALLEGRO_ALIGN_RIGHT,
								"Corrente Máxima: %i", jogador.corrente_max);

				/*Desenha tela de pausa*/
				if (jogo_pausado)
				{
					desenha_pausa(fonte32);

					if (mouse_x >= (LARG / 2) - 115 && mouse_x <= (LARG / 2) + 115 &&
						 mouse_y >= (ALT / 2) - 142 && mouse_y <= (ALT / 2) - 102) 
					{
						desenha_icone((LARG / 2) + 115, (ALT / 2) - 120, cinza);
					}
					else if (mouse_x >= (LARG / 2) - 80 && mouse_x <= (LARG / 2) + 80 &&
							 	mouse_y >= (ALT / 2) - 52 && mouse_y <= (ALT / 2) - 12) 
					{
						desenha_icone((LARG / 2) + 90, (ALT / 2) - 30, cinza);
					}
					else if (mouse_x >= (LARG / 2) - 100 && mouse_x <= (LARG / 2) + 100 &&
							 	mouse_y >= (ALT / 2) + 38 && mouse_y <= (ALT / 2) + 82) 
					{
						desenha_icone((LARG / 2) + 110, (ALT / 2) + 60, cinza);
					}
				}

				desenha_alvo(mouse_x, mouse_y, imagem_alvo, tiros, tiro_selecionado, fonte14, estado);
			}
			/*Desenha tela final*/
			else if(estado == tela_final)
			{  
			 	al_draw_bitmap(imagem_fundo_inicio, 0, 0, 0);
				al_draw_textf(fontetitulo, al_map_rgb(0, 0, 0), LARG / 2, (ALT / 2) - 250, ALLEGRO_ALIGN_CENTRE,
					"Fim de Jogo");
				al_draw_textf(fonte22, al_map_rgb(0, 0, 0), (LARG / 2) - 300, (ALT / 2) + 10, ALLEGRO_ALIGN_LEFT,
					"Pontuação Final: %i", jogador.pontos);
				al_draw_textf(fonte22, al_map_rgb(0, 0, 0), LARG / 2 + 300, (ALT / 2) + 10, ALLEGRO_ALIGN_RIGHT,
					"Corrente Máxima: %i", jogador.corrente_max);

				al_draw_textf(fonte32, al_map_rgb(0, 0, 0), LARG / 2 - 300, (ALT / 2) + 200, ALLEGRO_ALIGN_LEFT,
					"Menu Inicial");
				al_draw_textf(fonte32, al_map_rgb(0, 0, 0), LARG / 2 + 300, (ALT / 2) + 200, ALLEGRO_ALIGN_RIGHT,
					"Sair do Jogo");

				if (mouse_x >= (LARG / 2) - 300 && mouse_x <= (LARG / 2) - 90 &&
                mouse_y >= (ALT / 2) + 200 && mouse_y <= (ALT / 2) + 242) 
				{
					desenha_icone((LARG / 2) - 80, (ALT / 2) + 220, preto);
				}
				else if (mouse_x >= (LARG / 2) + 100 && mouse_x <= (LARG / 2) + 300 &&
                		mouse_y >= (ALT / 2) + 200 && mouse_y <= (ALT / 2) + 242) 
				{
					desenha_icone((LARG / 2) + 310, (ALT / 2) + 220, preto);
				}
				else if(mouse_x >= LARG / 2 + 50 && mouse_x <= LARG / 2 + 220 &&
						  mouse_y >= (ALT / 2) + 105 && mouse_y <= (ALT / 2) + 130)
				{
					if (!ranking_enviado)
						al_draw_line(LARG / 2 + 50, (ALT / 2) + 130, LARG / 2 + 220, (ALT / 2) + 130, al_map_rgb(0, 0, 0), 2);					
				}

				al_draw_textf(fonte32, al_map_rgb(0, 0, 0), LARG / 2 - 300, (ALT / 2) + 100, ALLEGRO_ALIGN_LEFT,
					"Nome: %s", nomeranking);
				al_draw_rectangle(LARG / 2 - 185, (ALT / 2) + 100, LARG / 2 + 35, (ALT / 2) + 140, al_map_rgb(0, 0, 0), 1);

				if (!ranking_enviado)
					al_draw_textf(fonte22, al_map_rgb(0, 0, 0), LARG / 2 + 50 , (ALT / 2) + 105, ALLEGRO_ALIGN_LEFT, "Envia Ranking");
				else
					al_draw_textf(fonte22, al_map_rgb(0, 0, 0), LARG / 2 + 50 , (ALT / 2) + 105, ALLEGRO_ALIGN_LEFT, "Enviado!");

				desenha_alvo(mouse_x, mouse_y, imagem_alvo, tiros, tiro_selecionado, fonte14, estado);
				
			}

			/*Atualiza Tela e limpa buffer secundário*/
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

//Finalização do Programa
//+------------------------------------------------------------------------------------------------------------------------
	/*Destroi as variaves ALLEGRO*/
	al_destroy_sample(explosao);
	al_destroy_sample(tiro);
	al_destroy_sample(destruicao);
	al_destroy_font(fonte08);
	al_destroy_font(fonte12);
	al_destroy_font(fonte14);
	al_destroy_font(fonte22);
	al_destroy_font(fonte32);
	al_destroy_font(fontetitulo);
	al_destroy_font(fontetitulosmall);
	al_destroy_bitmap(imagem_canhao);
	al_destroy_bitmap(imagem_inimigo);
	al_destroy_bitmap(imagem_alvo);
	al_destroy_bitmap(imagem_base);
	al_destroy_bitmap(imagem_selecao);
	al_destroy_bitmap(imagem_tiro);
	al_destroy_bitmap(imagem_fundo);
	al_destroy_bitmap(imagem_fundo_inicio);
	al_destroy_bitmap(imagem_canhao_base);
	al_destroy_bitmap(imagem_torre);
	al_destroy_bitmap(imagem_tutorial);
	al_destroy_event_queue(fila_de_eventos);
	al_destroy_timer(timer);
	al_destroy_display(janela);

	return EXIT_SUCCESS;
}
