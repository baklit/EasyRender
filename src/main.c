#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480


int main()
{
	
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("EasyRender", 50, 50, WIDTH, HEIGHT, 0);

	getchar();

	return 0;
}
