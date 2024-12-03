#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define DIM 640
#define SIZE 20

#define RIGHT 360
#define LEFT 180
#define UP -90
#define DOWN 90

#define FONTNAME "font/Ticketing.ttf"
#define FONTDIM 20

/* Tipo snake_t (lista) per la gestione del serpente */
typedef struct block_s{
	SDL_Rect pos; /* Posizione e dimensione singola cella da passare ad SDL_RenderFillRect*/
	int dir; /*direzione moviento singola cella*/
	struct block_s *next; /* Puntatore a prossimo elemento della lista */
}snake_t;

int KeyPressed(int );
snake_t *expand(snake_t *);
void Move(snake_t *);
void Draw(snake_t *, SDL_Renderer *, SDL_Texture *);
int Sucide(snake_t *);

snake_t *killSnake(snake_t *);

int Menu(SDL_Renderer *);
