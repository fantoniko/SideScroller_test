#pragma once
#include "SDL.h"
#include <vector>
#include "base.h"

class Enemy:public baseclass
{
	SDL_Rect box;
	int xvel, yvel;
	SDL_Texture* image;
	bool ground;
	SDL_Rect clips[2];
	double frame;
public:
	Enemy(SDL_Texture* img, int x, int y, int xvel, int yvel);
	void Move(std::vector< std::vector<int> >& vec);
	void Show(SDL_Renderer* renderer);
	SDL_Rect* GetRect();
};

