retroGame: main.o projectile.o player.o map.o 
	gcc -Wall -Wextra -g -o retroGame main.o map.o player.o projectile.o -lraylib -lm

main.o: main.c projectile.h player.h map.h
	gcc -Wall -Wextra -c -g main.c

projectile.o: projectile.c projectile.h player.h map.h
	gcc -Wall -Wextra -c -g projectile.c

player.o: player.c player.h map.h
	gcc -Wall -Wextra -c -g player.c

map.o: map.c map.h
	gcc -Wall -Wextra -c -g map.c

clean:
	rm -f *.o retroGame