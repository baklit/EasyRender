
output: main.o
	gcc main.o -o EasyRender -lSDL2
	./EasyRender

main.o: main.c
	gcc -c main.c

clean:
	rm *.o
