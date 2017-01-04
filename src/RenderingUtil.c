#include "RenderingUtil.h"
#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)
#define CLAMP(a, l, u) MIN(MAX(a, l), u) 

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
		if (x >=0 && x < WIDTH && y >= 0 && y < HEIGHT){
			screen[(int) x][(int) y] = Blend(p1, p2, (float) i / (float) steps);
		}
		if (min && max && y >= 0 && y < HEIGHT){
			if (min[(int) y] > (int) x){
				min[(int) y] = (int) x;
			}
			if (max[(int) y] < (int) x){
				max[(int) y] = (int) x;
			}
		}
	}	
}

void Draw3DLine(Vec3 *v1, Vec3 *v2, Pixel *p1, Pixel *p2, int *min, int *max, Pixel *minPix, Pixel *maxPix, Vec3 *minVec, Vec3 *maxVec)
{
	float dx = v2->x - v1->x;
	float dy = v2->y - v1->y;
	float dz = v2->z - v1->z;
	float steps;

	if (fabs(v2->x/v2->z - v1->x/v1->z) > fabs(v2->y/v2->z - v1->y/v1->z)){
		steps = fabs(v2->x/v2->z - v1->x/v1->z)*WIDTH;
	}else{
		steps = fabs(v2->y/v2->z - v1->y/v1->z)*HEIGHT;
	}

	float xStep = (float) dx / (float) steps;
	float yStep = (float) dy / (float) steps;
	float zStep = (float) dz / (float) steps;

	float x = v1->x;
	float y = v1->y;
	float z = v1->z;

	for (int i = 0; i < steps; i++){
		x += xStep;
		y += yStep;
		z += zStep;
		
		int newx = (int) ((((x/z)+1)/2) * WIDTH);
		int newy = (int) ((((y/z)+1)/2) * HEIGHT);

		if (newx >= 0 && newx < WIDTH && newy >= 0 && newy < HEIGHT){
			screen[newx][newy] = Blend(p1, p2, (float) i / (float) steps);
		}
		
		screen[newx][newy].d = z;

		if (min && max && minPix && maxPix && newy>=0 && newy<HEIGHT){
			if (min[newy] > newx || min[newy] == 0){
				min[newy] = newx;
				minPix[newy] = screen[newx][newy];
				minVec[newy] = (Vec3) {x, y, z};
			}
			if (max[newy] < newx || max[newy] == 0){
				max[newy] = newx;
				maxPix[newy] = screen[newx][newy];
				maxVec[newy] = (Vec3) {x, y, z};
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
				pix1 = screen[CLAMP(min[y], 0, WIDTH-1)][y];
				pix2 = screen[CLAMP(max[y], 0, WIDTH-1)][y];
				for (int x = CLAMP(min[y], 0, WIDTH-1); (x < max[y]) && (x < WIDTH); x++){
					screen[x][y] = Blend(&pix1, &pix2, (float) (x - min[y]) / (float) (max[y] - min[y]));
				}
			}	

			break;
	}
}

void Draw3DTri(Vec3 *v1, Vec3 *v2, Vec3 *v3, Pixel *p1, Pixel *p2, Pixel *p3, DrawStyle drawStyle)
{
	Vec3 *vn1 = &(Vec3) {WIDTH*(v1->x/v1->z + 1)/2, HEIGHT*(v1->y/v1->z + 1)/2, v1->z};
	Vec3 *vn2 = &(Vec3) {WIDTH*(v2->x/v2->z + 1)/2, HEIGHT*(v2->y/v2->z + 1)/2, v2->z};
	Vec3 *vn3 = &(Vec3) {WIDTH*(v3->x/v3->z + 1)/2, HEIGHT*(v3->y/v3->z + 1)/2, v3->z};

	switch(drawStyle){
		case DOTS:
			screen[(int) vn1->x][(int) vn1->y] = *p1;
			screen[(int) vn2->x][(int) vn2->y] = *p2;
			screen[(int) vn3->x][(int) vn3->y] = *p3;
			break;

		case LINES:
			Draw3DLine(v1, v2, p1, p2, NULL, NULL, NULL, NULL, NULL, NULL);
			Draw3DLine(v2, v3, p2, p3, NULL, NULL, NULL, NULL, NULL, NULL);
			Draw3DLine(v3, v1, p3, p1, NULL, NULL, NULL, NULL, NULL, NULL);
			break;

		case FILL:;
			int min[HEIGHT] = {0};
			int max[HEIGHT] = {0};
			Pixel minPix[HEIGHT];
			Pixel maxPix[HEIGHT];
			Vec3 minVec[HEIGHT];
			Vec3 maxVec[HEIGHT];

			Draw3DLine(v1, v2, p1, p2, min, max, minPix, maxPix, minVec, maxVec);
			Draw3DLine(v2, v3, p2, p3, min, max, minPix, maxPix, minVec, maxVec);
			Draw3DLine(v3, v1, p3, p1, min, max, minPix, maxPix, minVec, maxVec);

			for (int y = 0; y < HEIGHT; y++){
				if (min[y] != 0 && max[y] != 0){
					int minIndex = CLAMP(min[y], 0, WIDTH-1);
					int maxIndex = CLAMP(max[y], 0, WIDTH-1);
					Draw3DLine(&minVec[y], &maxVec[y], &minPix[y], &maxPix[y], NULL, NULL, NULL, NULL, NULL, NULL);
				}
			}			
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
