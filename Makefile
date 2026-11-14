retroGame: main.o player.o map.o 
	gcc -Wall -Wextra -g -o retroGame main.o map.o player.o -lraylib -lm

main.o: main.c player.h map.h
	gcc -Wall -Wextra -c -g main.c map.o player.o

player.o: player.c player.h map.h
	gcc -Wall -Wextra -c -g player.c

map.o: map.c map.h
	gcc -Wall -Wextra -c -g map.c