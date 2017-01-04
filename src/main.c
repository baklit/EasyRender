#include "RenderingUtil.h"
#include "Vector.h"
#include <SDL2/SDL.h>
#include <math.h>

SDL_Window *window;
SDL_Renderer *renderer;
Pixel screen[WIDTH][HEIGHT];

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("EasyRender", 50, 50, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	ClearOutput(&(Pixel) {0, 0, 0, 0});

	Vec3 v1 = (Vec3) {-0.5, -0.5, 1};
	Vec3 v2 = (Vec3) {0, 0.5, 1};
	Vec3 v3 = (Vec3) {0.5, -0.5, 1};

	Pixel p1 = (Pixel) {255, 0, 0, 1};
	Pixel p2 = (Pixel) {0, 255, 0, 1};
	Pixel p3 = (Pixel) {0, 0, 255, 1};

	Draw3DTri(&v1, &v2, &v3, &p1, &p2, &p3, DOTS);

	PushOutput();

	for (int i = 1; i < 5000; i++){
		v1 = (Vec3) {0.5*sin(SDL_GetTicks() * 0.001), -0.5, 1 + 0.5*cos(SDL_GetTicks() * 0.001)};
		v3 = (Vec3) {-v1.x, v1.y, 2 - v1.z};
		ClearOutput(&(Pixel) {0, 0, 0, 0});
		Draw3DTri(&v1, &v2, &v3, &p1, &p2, &p3, FILL);
		PushOutput();
	}

	SDL_Delay(1000);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
