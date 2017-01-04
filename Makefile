
output: src/main.o src/RenderingUtil.o src/Vector.o
	gcc -Wall src/main.o src/RenderingUtil.o src/Vector.o -o EasyRender -lSDL2 -lm
	./EasyRender

src/main.o: src/main.c
	gcc -c src/main.c -o src/main.o

src/RenderingUtil.o: src/RenderingUtil.c
	gcc -c src/RenderingUtil.c -o src/RenderingUtil.o

src/Vector.o: src/Vector.c
	gcc -c src/Vector.c -o src/Vector.o

clean:
	rm src/*.o
