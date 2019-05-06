#include <iostream>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "labirinto.h"

using namespace std;

#define LARGURA 500
#define ALTURA 500

int main(int argc, char const *argv[])
{

	ALLEGRO_DISPLAY *display;

	const float FPS = 10.0;

	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL, "Não pode iniciar o Allegro", NULL, 0);
		return -1;		
	}

	// Setando tipo de janela a ser criada
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	display = al_create_display(LARGURA, ALTURA);
	al_set_window_title(display, "Labirinto");
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

	if (!display) {
		al_show_native_message_box(display, "Olá", "Opções do display", "Mensage,", NULL, 0);
		return -1;
	}


	al_init_primitives_addon();
	al_install_keyboard();

	// ****** PRIMITIVAS ******
	ALLEGRO_COLOR azul = al_map_rgb(0, 0, 255);
	ALLEGRO_COLOR verde = al_map_rgb(0, 255, 0);
	ALLEGRO_COLOR vermelho = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR preto = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR branco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR cinza = al_map_rgb(192, 192, 192);


	ALLEGRO_TIMER *timer = al_create_timer(1 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	int a = 0, a2 = 0, b = 0, b2 = 0;

	ALLEGRO_KEYBOARD_STATE keyboard_state;

	al_start_timer(timer);

	Labirinto lab[10][10] = {{'O','O','|','O','O','O','O','O','O','O'},{'O','O','|','|','|','O','O','O','O','O'},{'O','|','|','O','O','O','O','O','O','O'},{'O','|','|','O','O','O','O','O','O','O'},{'O','O','O','O','|','|','|','O','O','O'},{'|','|','O','O','|','|','O','O','|','O'},{'O','O','O','|','O','|','|','O','|','|'},{'|','O','|','O','O','|','O','O','O','O'},{'|','O','O','O','|','O','O','|','O','|'},{'|','|','|','O','O','|','|','|','O','O'}}; 

	//Variaveis de saida do laço
	char resultado = 'a';
	int pode_jogar = 0;
	
	//Matriz auxiliar para marcar onde ja passou e onde eh parede
	char aux[10][10]; 
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if(lab[i][j].get() == '|')
				aux[i][j] = 'T';
			else
				aux[i][j] = 'F';
		}
	}

	//Setando valores de inicio e fim
	int x = 0; int y = 0;
	lab[x][y].set('1'); lab[9][9].set('?');


	while(pode_jogar == 0)
	{

		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
	

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					pode_jogar = 1;
					break;
				}
		}

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_RIGHT:
				if(x>=0 && x<10 && y>=0 && y+1<10 && lab[x][y+1].get() != '|' && lab[x][y+1].get() != '*')
				{
					lab[x][y].set('*');

					aux[x][y] = 'T';
					y++;
					if(lab[x][y].get() == '?')
					{
						pode_jogar = 1; resultado = 'G';
					}
					lab[x][y].set('1');
					aux[x][y] = '1';
				}
				break;
			}
		}
		
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_LEFT:
					if(x>=0 && x<10 && y-1>=0 && y<10 && lab[x][y-1].get() != '|' && lab[x][y-1].get() != '*')
					{
						lab[x][y].set('*');
						
						aux[x][y] = 'T';
						y--;
						if(lab[x][y].get() == '?')
						{
							pode_jogar = 1; resultado = 'G';
						}
						lab[x][y].set('1');
						aux[x][y] = '1';
					}
					break;
				}
			}

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					if(x-1>=0 && x<10 && y>=0 && y<10 && lab[x-1][y].get() != '|' && lab[x-1][y].get() != '*')
					{
						lab[x][y].set('*');
						
						aux[x][y] = 'T';
						x--;
						if(lab[x][y].get() == '?')
						{
							pode_jogar = 1; resultado = 'G';
						}
						lab[x][y].set('1');
					}
					break;
				}
			}
		

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_DOWN:
					if(x>=0 && x+1<10 && y>=0 && y<10 && lab[x+1][y].get() != '|' && lab[x+1][y].get() != '*')
					{
						lab[x][y].set('*');
						aux[x][y] = '1';
						aux[x][y] = 'T';
						x++;
						if(lab[x][y].get() == '?')
						{
							pode_jogar = 1; resultado = 'G';
						}
						lab[x][y].set('1');
						aux[x][y] = '1';
					}
					break;
				}
			}


		if((aux[x+1][y] == 'T' && aux[x][y+1] == 'T' && aux[x-1][y] == 'T' && aux[x][y-1] == 'T') || (aux[x+1][y] == 'T' && aux[x][y+1] == 'T' && x-1<0 && aux[x][y-1] == 'T') || (x+1>9 && aux[x][y+1] == 'T' && aux[x-1][y] == 'T' && aux[x][y-1] == 'T') || (aux[x+1][y] == 'T' && y+1>9 && aux[x-1][y] == 'T' && aux[x][y-1] == 'T') || (aux[x+1][y] == 'T' && aux[x][y+1] == 'T' && aux[x-1][y] == 'T' && y-1<0))
		{
			pode_jogar = 1;		
		}

		for (int i = 0; i < 10; ++i)
		{	
			for (int j = 0; j < 10; ++j)
			{
				a = 50*j;
				a2+=a+50; 
				b = 50*i; 
				b2+=b+50; 

				if(lab[i][j].get() == 'O'){
					al_draw_filled_rectangle(a, b, a2, b2, branco);
					al_draw_rectangle(a, b, a2, b2, preto,2);
				}
				
				if(lab[i][j].get() == '|'){
					al_draw_filled_rectangle(a, b, a2, b2, vermelho);
					al_draw_rectangle(a, b, a2, b2, preto,2);
				}


				if(lab[i][j].get() == '1'){
					al_draw_filled_rectangle(a, b, a2, b2, preto);
					al_draw_rectangle(a, b, a2, b2, preto,2);
				}
				
				if(lab[i][j].get() == '?'){
					al_draw_filled_rectangle(a, b, a2, b2, azul);
					al_draw_rectangle(a, b, a2, b2, preto,2);
				}

				if(lab[i][j].get() == '*'){
					al_draw_filled_rectangle(a, b, a2, b2, cinza);
					al_draw_rectangle(a, b, a2, b2,preto,2);
				}
				b+=50;
			}
		}
	
		al_flip_display();	

		al_clear_to_color(al_map_rgb(0,0,0));
		
	}

	if(resultado == 'G')
	{
		al_show_native_message_box(display, "Labirinto", "Resultado:","GANHOU!!!", NULL, 0);
	}
	else
	{
		al_show_native_message_box(display, "Labirinto", "Resultado:","PERDEU!!!", NULL, 0);
	
	}
	
	return 0;
}