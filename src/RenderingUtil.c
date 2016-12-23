#include "RenderingUtil.h"

void DrawPixel(int x, int y)
{
	
}

//Uses DDA (maybe use bresenham if perf is bad?)
void DrawLine(int x1, int y1, int x2, int y2, Pixel *pixel)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int steps;
	
	if (abs(dx) > abs(dy)){
		steps = abs(dx);
	}else{
		steps = abs(dy);		
	}

	float xStep = dx / steps;
	float yStep = dy / steps;

	float x = x1;
	float y = y1;
	for (int i = 0; i < steps; i++){
		x += xStep;
		y += yStep;
		screen[(int) x][(int) y] = *pixel;
	}	
}


void PushOutput()
{	
	Pixel pixel;

	for (int x = 0; x < WIDTH; x++){
		for (int y = 0; y < HEIGHT; y++){
			pixel = screen[x][y];
			SDL_SetRenderDrawColor(renderer, pixel.r, pixel.g, pixel.b, 0xFF);
			SDL_RenderDrawPoint(renderer, x, HEIGHT - y);		
		}
	}

	SDL_RenderPresent(renderer);	
}

void ClearOutput(Pixel *pixel)
{
	SDL_RenderClear(renderer);

	for (int x = 0; x < WIDTH; x++){
		for (int y = 0; y < HEIGHT; y++){
			screen[x][y] = *pixel;
		}			
	}
}
