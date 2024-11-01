build:
	gcc src/*.c -Wall -std=c99 -lSDL2 -lm -o renderer
debug:
	gcc src/*.c -Wall -std=c99 -lSDL2 -lm -o renderer
run:
	./renderer
buildrun:
	gcc src/*.c -Wall -std=c99 -lSDL2 -lm -o renderer
	./renderer
clean:
	rm renderer
