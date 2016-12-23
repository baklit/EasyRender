#pragma once
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct Pixel_Struct{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char d;
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

void DrawLine(int x1, int y1, int x2, int y2, Pixel *pixel);
void DrawTri(Triangle *triangle, DrawStyle drawSyle);
void PushOutput();
void ClearOutput(Pixel *pixel);
