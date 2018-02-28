#pragma once
#include "SDL.h"

class baseclass 
{
public:
	static SDL_Rect coord;
	static const int TILE_SIZE = 50;

protected:
	bool collision(SDL_Rect* rec1, SDL_Rect* rec2);
};