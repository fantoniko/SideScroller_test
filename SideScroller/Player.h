#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "base.h"

class Player:baseclass
{
	SDL_Rect box;
	SDL_Texture* image;
	int xvel, yvel;
	SDL_Rect clips[4];
	bool ground;
	bool jump;
	bool moving;
	char direction;
	double frame;
	int health;
	
public:
	Player(SDL_Texture* img);
	~Player();
	SDL_Rect* GetRect();
	void SetXvel(int vel);
	int GetXvel();
	void Show(SDL_Renderer* renderer);
	void Move(const std::vector<std::vector<int> > &map);
	void Jump();
	void SetMoving(bool b);
	void SetDirection(char c);
	int GetHealth();
	void SetHealth(int h);
};
