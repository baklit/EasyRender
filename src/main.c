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

	Pixel clearPixel = {0, 0, 0, 0};
	ClearOutput(&clearPixel);

	Pixel redPixel = {255, 0, 0, 0};
	DrawLine(500, 100, 400, 200, &redPixel);

	PushOutput();

	SDL_Delay(2000);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
