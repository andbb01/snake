#include "snake.h"

#define STDELAY 100
#define SNAKESURF "images/snake.png"
#define UPSURF "images/up.png"
#define MAXLEN 10
#define BASE 10

int main(int argc, char *argv[]){
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Event event;
	SDL_Texture *sntext; /* Texture parti serpente */
	SDL_Surface *sur;
	SDL_Texture *uptext; /* Texture up */
	TTF_Font *font;
	char poichar[MAXLEN + 1]; /* Stringa per scrittura punti*/
	SDL_Color black = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE}; /* Colore per il testo */
	int game, randpos, punteggio;
	int delay;
	snake_t *player = NULL; /* Testa di lista del serpente */
	SDL_Rect up = {0, 0, SIZE, SIZE}; /* Casella up */
	SDL_Rect poibox; /* Casella punti*/
	SDL_Texture *poitex; /* Texture punti */

	TTF_Init();
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	
	SDL_CreateWindowAndRenderer(DIM, DIM, 0, &win, &ren);
	
	/* Creazione texture serpente (sntext) e texture up (uptext) */
	sur = IMG_Load(SNAKESURF);
	sntext = SDL_CreateTextureFromSurface(ren, sur);
	
	SDL_FreeSurface(sur);
	
	sur = IMG_Load(UPSURF);
	uptext = SDL_CreateTextureFromSurface(ren, sur);	
	
	SDL_FreeSurface(sur);
	
	/* Apre Font */
	font = TTF_OpenFont(FONTNAME, FONTDIM);
	
	/* Inizializzazione posizione up (casuale)*/
	srand(time(NULL));
	randpos = rand() % (DIM / SIZE);
	up.x = randpos * SIZE;
	randpos = rand() % ((DIM - 2 * FONTDIM)/ SIZE);
	up.y = randpos  * SIZE;
	
	/* Inizializa il serpente alla lunghezza minima di 3*/
	player = expand(player);
	player = expand(player);
	player = expand(player);
	
	poibox.x = FONTDIM/4;
	poibox.y = DIM - 2*FONTDIM;
	poibox.h = 2*FONTDIM;
	
	punteggio = 0;
	game = 1;
	delay = STDELAY;
	while(game != 2){
		game = Menu(ren);
		while(game == 1){
			SDL_PollEvent(&event);
		
			/* Grafica */
		
			Move(player);
		
			SDL_SetRenderDrawColor(ren, 0x00, 0x99, 0x02, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(ren);
		
			Draw(player, ren, sntext);
		
			SDL_RenderCopy(ren, uptext, NULL, &up);
		
			sprintf(poichar, "%d", punteggio);
			
			
			sur = TTF_RenderText_Solid(font, poichar, black);
			poitex = SDL_CreateTextureFromSurface(ren, sur);
			
			SDL_FreeSurface(sur);
			
			poibox.w = strlen(poichar) * FONTDIM;
		
			SDL_RenderCopy(ren, poitex, NULL, &poibox);
		
			SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
			
			SDL_RenderDrawLine(ren, 0, DIM - FONTDIM*2, DIM, DIM - FONTDIM*2);
		
			SDL_RenderPresent(ren);
		
		
			/* Cambia direzione testa serpente */
		
			if (KeyPressed(SDL_SCANCODE_UP) && player->dir != DOWN){
				player->dir = UP;
			} else if (KeyPressed(SDL_SCANCODE_DOWN) && player->dir != UP){
				player->dir = DOWN;
			} else if (KeyPressed(SDL_SCANCODE_RIGHT) && player->dir != LEFT){
				player->dir = RIGHT;
			} else if (KeyPressed(SDL_SCANCODE_LEFT) && player->dir != RIGHT){
				player->dir = LEFT;
			}
		
		
			/* Mangia up aumenta lunghezza e punteggio */
			if (player->pos.x == up.x && player->pos.y == up.y){
				srand(time(NULL));
				randpos = rand() % (DIM / SIZE);
				up.x = randpos * SIZE;
				randpos = rand() % ((DIM - 2 * FONTDIM)/ SIZE);
				up.y = randpos  * SIZE;
				punteggio++;
				delay = STDELAY - punteggio;
				player = expand(player);
			}	
			SDL_Delay(delay);	
		
			/* Morte o uscita */
			if (Sucide(player)){
				game = 0;
				punteggio = 0;
				player = killSnake(player);
				player = expand(player);
				player = expand(player);
				player = expand(player);
				SDL_Delay(2000);
			} else if (event.type == SDL_QUIT || KeyPressed(SDL_SCANCODE_ESCAPE))
				game = 0;
		}
	}

	SDL_Quit();

	return 0;
}


/* Funzione controllo input da tastiera */
int KeyPressed(int key){
	const Uint8 *KeyState = SDL_GetKeyboardState(NULL);
	if (KeyState[key])
		return 1;
	else return 0;
}
