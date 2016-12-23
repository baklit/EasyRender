
output: src/main.o
	gcc src/main.o -o EasyRender -lSDL2
	./EasyRender

src/main.o: src/main.c
	gcc -c src/main.c -o src/main.o

clean:
	rm src/*.o
