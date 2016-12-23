#include "RenderingUtil.h"
#include <SDL2/SDL.h>

SDL_Window *window;
SDL_Renderer *renderer;
Pixel screen[WIDTH][HEIGHT];

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("EasyRender", 50, 50, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);	

	ClearOutput(&(Pixel) {0, 0, 0, 0});

	Triangle tri;
	tri.x1 = 300;
	tri.y1 = 200;
	tri.x2 = 0;
	tri.y2 = 0;
	tri.x3 = 400;
	tri.y3 = 400;
	tri.p1 = &(Pixel) {255, 0, 0, 0};
	tri.p2 = &(Pixel) {0, 255, 0, 0};
	tri.p3 = &(Pixel) {0, 0, 255, 0};
	
	DrawTri(&tri, DOTS);
	DrawTri(&tri, LINES);

	PushOutput();

	SDL_Delay(2000);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
