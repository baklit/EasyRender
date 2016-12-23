
output: src/main.o src/RenderingUtil.o
	gcc src/main.o src/RenderingUtil.o -o EasyRender -lSDL2
	./EasyRender

src/main.o: src/main.c
	gcc -c src/main.c -o src/main.o

src/RenderingUtil.o: src/RenderingUtil.c
	gcc -c src/RenderingUtil.c -o src/RenderingUtil.o

clean:
	rm src/*.o
