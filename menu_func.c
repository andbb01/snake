#include "snake.h"

#define FILENAME "files/menuEntry.dat"
#define MENENTRY 2
#define MAXLEN 20

int Menu(SDL_Renderer *ren){
	TTF_Font *font;
	SDL_Color black = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};
	SDL_Surface *sur;
	SDL_Texture *tmen[MENENTRY];
	char menEntry[MAXLEN + 1];
	FILE *fp;
	int i;
	SDL_Rect box[MENENTRY];
	int dim, scelta;
	SDL_Event event;
	
	if (fp = fopen(FILENAME, "r")){
		font = TTF_OpenFont(FONTNAME, FONTDIM);
		for (i = 0; i < MENENTRY; i++){
			fgets(menEntry, MAXLEN + 1, fp);
			dim = strlen(menEntry);
			menEntry[dim - 1] = '\0';
			dim *= FONTDIM;
			box[i].y = DIM/4 + i*FONTDIM + i*FONTDIM/2;
			box[i].h = (2*FONTDIM);
			box[i].w = dim;
			box[i].x = DIM/2 - dim/2;
			sur = TTF_RenderText_Solid(font, menEntry, black);
			tmen[i] = SDL_CreateTextureFromSurface(ren, sur);
		}
		TTF_CloseFont(font);
		fclose(fp);
		
		scelta = 0;
		while (scelta == 0){
			SDL_PollEvent(&event);
			SDL_SetRenderDrawColor(ren, 0x00, 0x99, 0x02, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(ren);
		
			for (i = 0; i < MENENTRY; i++){
				SDL_RenderCopy(ren, tmen[i], NULL, &box[i]);
			}
			SDL_RenderPresent(ren);
			
			if (KeyPressed(SDL_SCANCODE_1))
				scelta = 1;
			else if (KeyPressed(SDL_SCANCODE_2) || event.type == SDL_QUIT)
				scelta = 2;
			SDL_Delay(120);			
		}
	}



	return scelta;
}
