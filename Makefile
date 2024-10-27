build:
	gcc src/*.c -Wall -std=c99 -lSDL2 -o renderer
run:
	./renderer
buildrun:
	gcc src/*.c -Wall -std=c99 -lSDL2 -o renderer
	./renderer
clean:
	rm renderer
