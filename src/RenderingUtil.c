#include "RenderingUtil.h"

Pixel Blend(Pixel *p1, Pixel *p2, float alpha)
{
	return (Pixel) {
		p1->r + (p2->r - p1->r)*alpha,
		p1->g + (p2->g - p1->g)*alpha,
		p1->b + (p2->b - p1->b)*alpha,
		p1->d + (p2->d - p1->d)*alpha		
	};
}

//Uses DDA (maybe use bresenham if perf is bad?)
void DrawLine(int x1, int y1, int x2, int y2, Pixel *p1, Pixel *p2, int *min, int *max)
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
		screen[(int) x][(int) y] = Blend(p1, p2, (float) i / (float) steps);
		
		if (min && max){
			if (min[(int) y] > (int) x){
				min[(int) y] = (int) x;
			}
			if (max[(int) y] < (int) x){
				max[(int) y] = (int) x;
			}
		}
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
					triangle->x2, triangle->y2,
				   	triangle->p1, triangle->p2, NULL, NULL);
			
			DrawLine(triangle->x2, triangle->y2,
					triangle->x3, triangle->y3,
				   	triangle->p2, triangle->p3, NULL, NULL);
			
			DrawLine(triangle->x3, triangle->y3,
					triangle->x1, triangle->y1,
				   	triangle->p3, triangle->p1, NULL, NULL);
			break;

		case FILL:;
			int min[HEIGHT];
			int max[HEIGHT] = {0};

			for (int i = 0; i < HEIGHT; i++){
				min[i] = WIDTH;
			}
			
			DrawLine(triangle->x1, triangle->y1,
					triangle->x2, triangle->y2,
				   	triangle->p1, triangle->p2, min, max);
			
			DrawLine(triangle->x2, triangle->y2,
					triangle->x3, triangle->y3,
				   	triangle->p2, triangle->p3, min, max);
			
			DrawLine(triangle->x3, triangle->y3,
					triangle->x1, triangle->y1,
				   	triangle->p3, triangle->p1, min, max);
			
			
			Pixel pix1;
			Pixel pix2;
			for (int y = 0; y < HEIGHT; y++){
				pix1 = screen[min[y]][y];
				pix2 = screen[max[y]][y];
				for (int x = min[y]; x < max[y]; x++){
					screen[x][y] = Blend(&pix1, &pix2, (float) (x - min[y]) / (float) (max[y] - min[y]));
				}
			}	

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
