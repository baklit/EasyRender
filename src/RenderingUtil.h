#pragma once
#include "Vector.h"
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct Pixel_Struct{
	float r;
	float g;
	float b;
	float d;
} Pixel;

typedef struct Triangle_Struct{
	int x1;
	int x2;
	int x3;
	int y1;
	int y2;
	int y3;
	Pixel *p1;
	Pixel *p2;
	Pixel *p3;
} Triangle;

typedef enum{
	DOTS,
	LINES,
	FILL
} DrawStyle;

extern Pixel screen[WIDTH][HEIGHT];
extern SDL_Renderer *renderer;

Pixel Blend(Pixel *p1, Pixel *p2, float alpha);

void DrawLine(int x1, int y1, int x2, int y2, Pixel *p1, Pixel *p2, int *min, int *max);
void DrawTri(Triangle *triangle, DrawStyle drawStyle);
void Draw3DTri(Vec3 *v1, Vec3 *v2, Vec3 *v3, Pixel *p1, Pixel *p2, Pixel *p3, DrawStyle drawstyle);
void PushOutput();
void ClearOutput(Pixel *pixel);
