files = snake.h menu_func.c snake_func.c main.c
libraries = -lSDL2 -lSDL2_image -lSDL2_ttf
compiler = gcc
exec_name = snake

compile:
	$(compiler) $(files) $(libraries) -o snake
	rm *.gch

debug:
	$(compiler) $(files) $(libraries) -D GAME_MAIN -D DEBUG
