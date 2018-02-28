#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>
#include "useful_functions.h"
#include "base.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game:public baseclass
{
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_Texture* background, *block, *bullet, *enemy;
	SDL_Rect camera;
	Player* player1;
	std::vector< std::vector<int> > map;
	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;

	bool running;
	bool direction[2];

	SDL_Texture* LoadImage(const char* filename);
	void LoadMap(const char* filename);
	void ShowMap();
	void HandleEvents();
	
	
public:
	Game();
	~Game();
	void Start();
};
