#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480


int main()
{
	
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("EasyRender", 50, 50, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);	

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Delay(2000);

	return 0;
}
