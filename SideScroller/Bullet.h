#pragma once
#include <iostream>
#include "SDL.h"

class Bullet
{
	const int BULLET_WIDTH = 10;
	const int BULLET_HEIGHT = 10;
	SDL_Rect box;
	int xVel, yVel;
	SDL_Texture* image;
public:
	Bullet(SDL_Texture* img, int x, int y, int xvel, int yvel);
	void Move();
	void Show(SDL_Renderer* renderer);
	SDL_Rect* GetRect();
};