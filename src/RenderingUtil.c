#include "RenderingUtil.h"

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

	float xStep = (float) dx / (float) steps;
	float yStep = (float) dy / (float) steps;
	
	float x = x1;
	float y = y1;

	for (int i = 0; i < steps; i++){
		x += xStep;
		y += yStep;
		screen[(int) x][(int) y] = *pixel;
	}	
}

void DrawTri(Triangle *triangle, DrawStyle drawStyle)
{
	switch(drawStyle){
		case DOTS:
			screen[triangle->x1][triangle->y1] = *triangle->p1;
			screen[triangle->x2][triangle->y2] = *triangle->p2;
			screen[triangle->x3][triangle->y3] = *triangle->p3;
			
			break;

		case LINES:
			DrawLine(triangle->x1, triangle->y1,
					triangle->x2, triangle->y2, triangle->p1);
			
			DrawLine(triangle->x2, triangle->y2,
					triangle->x3, triangle->y3, triangle->p2);
			
			DrawLine(triangle->x3, triangle->y3,
					triangle->x1, triangle->y1, triangle->p3);
			break;
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
