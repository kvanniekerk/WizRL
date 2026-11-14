make:
	mkdir bin
	gcc main.c include/game_math.c -o bin/main -lncurses
run:
	bin/main
clean:
	rm -r bin
prerequisites:
	sudo pacman -S ncurses
test:
	gcc test.c include/game_math.c -o bin/test
	bin/test