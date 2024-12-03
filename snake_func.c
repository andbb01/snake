#include "snake.h"

/* Aggiunge elemento alla lista (allunga il serpente) */
/* Simile ad append */
snake_t *expand(snake_t *head){
	snake_t *tmp;
	snake_t *nw;
	int len;
	
	if (nw = malloc(sizeof(snake_t))){
		nw->next = NULL;
		nw->pos.w = SIZE;
		nw->pos.h = SIZE;

		if (head != NULL){
			len = 0;
			for (tmp = head; tmp->next != NULL; tmp = tmp->next)
				len++;
			if (len == 0)
				len++;	
			nw->dir = tmp->dir;
			if (tmp->dir == DOWN){
				nw->pos.x = tmp->pos.x;
				nw->pos.y = tmp->pos.y - SIZE;
			} else if (tmp->dir == UP){
				nw->pos.x = tmp->pos.x;
				nw->pos.y = tmp->pos.y + SIZE;
			} else if (tmp->dir == LEFT){
				nw->pos.x = tmp->pos.x + SIZE;
				nw->pos.y = tmp->pos.y;		
			}else if (tmp->dir == RIGHT){
				nw->pos.x = tmp->pos.x - SIZE;
				nw->pos.y = tmp->pos.y;
			}
			tmp->next = nw;
		} else{
			head = nw;
			nw->pos.x = DIM/2;
			nw->pos.y = DIM/2;
			head->dir = UP;
		}
	}
	
	return head;
}


/* Muove il serpente muovendo singolarmente ogni casella (elemento della lista) */
void Move(snake_t *head){
	snake_t *tmp;
	int prevdir, tmpdir;
	
	if (head != NULL){
		/*
			Ad ogni singolo elemento viene data la direzione dell'elemento precedente
			e viene salvata la direzione (prevdir) per essere successivamente dato all'elemento successivo 
		*/
		prevdir = head->dir;
		for (tmp = head; tmp != NULL; tmp = tmp->next){
			if (tmp->dir == RIGHT){
				tmp->pos.x += SIZE;
				tmpdir = tmp->dir;
				tmp->dir = prevdir;
				prevdir = tmpdir;
			} else if (tmp->dir == LEFT){
				tmp->pos.x -= SIZE;
				tmpdir = tmp->dir;
				tmp->dir = prevdir;
				prevdir = tmpdir;
			} else if (tmp->dir == UP){
				tmp->pos.y -= SIZE;
				tmpdir = tmp->dir;
				tmp->dir = prevdir;
				prevdir = tmpdir;
			} else {
				tmp->pos.y += SIZE;
				tmpdir = tmp->dir;
				tmp->dir = prevdir;
				prevdir = tmpdir;
			}
			
			if (tmp->pos.x >= DIM){
				tmp->pos.x = 0;
			} else if (tmp->pos.x < 0) {
				tmp->pos.x = DIM -  SIZE;
			}
			
			if (tmp->pos.y < 0)
				tmp->pos.y = DIM - (2 * FONTDIM) - SIZE;
			else if (tmp->pos.y >= DIM - (2 * FONTDIM))
				tmp->pos.y = 0;
		}
	}
	return;
}




#define PSIZE 16
#define NPART 4
#define TESTA 3
#define CORPO 2
#define CURVA 1
#define CODA 0

/* Disegna ogni singola casella del serpente */
void Draw(snake_t *head, SDL_Renderer *ren, SDL_Texture *sntex){
	SDL_Rect snakePart[NPART]; /* Coda 0, curva 1, corpo 2, testa 3 */
	int i; 
	snake_t *tmp;
	
	for (i = 0; i < NPART; i++){
		snakePart[i].x = i*PSIZE;
		snakePart[i].y = 0;
		snakePart[i].h = PSIZE;
		snakePart[i].w = PSIZE;
	}
	
	/* Nessuno sa come funziona questa parte, necessario trovare un algoritmo per la rotazione della curva */
	SDL_RenderCopyEx(ren, sntex, &snakePart[TESTA], &head->pos, head->dir, NULL, 0);
	for (tmp = head->next; tmp->next != NULL; tmp = tmp->next){
		if (tmp->next->dir == tmp->dir)
			SDL_RenderCopyEx(ren, sntex, &snakePart[CORPO], &tmp->pos, tmp->dir, NULL, 0);
		else if ((tmp->dir == RIGHT && tmp->next->dir == UP) || (tmp->dir == DOWN && tmp->next->dir == LEFT))
			SDL_RenderCopyEx(ren, sntex, &snakePart[CURVA], &tmp->pos, 0, NULL, 0);
		else if ((tmp->dir == RIGHT && tmp->next->dir == DOWN) || (tmp->dir == UP && tmp->next->dir == LEFT))
			SDL_RenderCopyEx(ren, sntex, &snakePart[CURVA], &tmp->pos, -90, NULL, 0);
		else if ((tmp->dir == UP && tmp->next->dir == RIGHT) || (tmp->dir == LEFT && tmp->next->dir == DOWN))
			SDL_RenderCopyEx(ren, sntex, &snakePart[CURVA], &tmp->pos, 180, NULL, 0);
		else if ((tmp->dir == DOWN && tmp->next->dir == RIGHT) || (tmp->dir == LEFT && tmp->next->dir == UP))
			SDL_RenderCopyEx(ren, sntex, &snakePart[CURVA], &tmp->pos, 90, NULL, 0);
	}		
	SDL_RenderCopyEx(ren, sntex, &snakePart[CODA], &tmp->pos, tmp->dir, NULL, 0);
	
	return;
}



snake_t *killSnake(snake_t *head){
	if (head != NULL){
		head = killSnake(head->next);
		free(head);
	}
	return head;
}





/* Controlla se il serpente si mangia da solo (due elementi sono nella stessa posizione) */
int Sucide(snake_t *head){
	int autoeat;
	snake_t *tmp;

	autoeat = 0;
	if (head != NULL){
		for (tmp = head->next;tmp != NULL && !autoeat; tmp = tmp->next)
			if (tmp->pos.x == head->pos.x && tmp->pos.y == head->pos.y)
				autoeat = 1;
	}
	return autoeat;
}
