#pragma once
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char d;
} Pixel;

extern Pixel screen[WIDTH][HEIGHT];
extern SDL_Renderer *renderer;

void DrawPixel(int x, int y);
void DrawLine(int x1, int y1, int x2, int y2, Pixel *pixel);
void PushOutput();
void ClearOutput(Pixel *pixel);
