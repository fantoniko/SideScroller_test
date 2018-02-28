#include "Game.h"

SDL_Rect baseclass::coord;

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("SideScroller", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
	block = LoadImage("block.bmp");
	background = LoadImage("background.bmp");
	bullet = LoadImage("bullet.bmp");
	enemy = LoadImage("enemy.bmp");

	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// check if not working
	baseclass::coord = camera;
	direction[0] = direction[1] = 0;
	running = true;
	player1 = new Player(LoadImage("player.bmp"));
	enemies.push_back(new Enemy(enemy, 30, 40, 1, 0));
}


Game::~Game()
{
	delete player1;
	SDL_DestroyTexture(block);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(bullet);
	for (int i = 0; i < bullets.size(); i++)
		delete bullets[i];
	for (int i = 0; i < enemies.size(); i++)
		delete enemies[i];
	SDL_Quit();
}

SDL_Texture* Game::LoadImage(const char* filename)
{
	SDL_Surface* surf = SDL_LoadBMP(getResourcePath(filename).c_str());
	if (surf == NULL)
		std::cout << "Problem with loading image" << std::endl;
	//SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0x00, 0xFF, 0xFF));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surf);
	SDL_FreeSurface(surf);
	return texture;
}

void Game::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			return;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				direction[0] = 1;
				player1->SetMoving(true);
				break;
			case SDLK_RIGHT:
				direction[1] = 1;
				player1->SetMoving(true);
				break;
			case SDLK_SPACE:
				player1->Jump();
				break;
			case SDLK_f:
				bullets.push_back(new Bullet(bullet, player1->GetRect()->x + player1->GetRect()->w,
					player1->GetRect()->y + 1, 5, 0));

				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				direction[0] = 0;
				player1->SetMoving(false);
				break;
			case SDLK_RIGHT:
				direction[1] = 0;
				player1->SetMoving(false);
				break;
			}
			break;
		}
}

void Game::ShowMap() 
{
	int start, end;
	start = (baseclass::coord.x - (baseclass::coord.x 
		% baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
	end = (baseclass::coord.x + baseclass::coord.w 
		+ (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w) 
			% baseclass::TILE_SIZE)) / 50;
	if (start < 0)
		start = 0;
	if (end > map[0].size())
		end = map[0].size();
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = start; j < end; j++)
		{
			if (map[i][j] != 0)
			{
				SDL_Rect blockRect = { (map[i][j] - 1)*baseclass::TILE_SIZE, 0,
					baseclass::TILE_SIZE, baseclass::TILE_SIZE };
				SDL_Rect dstRect = { j * baseclass::TILE_SIZE - baseclass::coord.x, i * baseclass::TILE_SIZE,
					baseclass::TILE_SIZE, baseclass::TILE_SIZE };
				SDL_RenderCopy(renderer, block, &blockRect, &dstRect);
			}
		}
	}
}

void Game::Start() 
{
	const int fps = 60;
	Uint32 start;
	LoadMap("map.map");

	while (running)
	{
		start = SDL_GetTicks();
		HandleEvents();

		//logic
		if (direction[0])
		{
			player1->SetDirection('l');
			if (player1->GetRect()->x > 0)
				player1->SetXvel(-1);
			else
			{
				player1->SetXvel(0);
				camera.x--;
				baseclass::coord.x--;
			}
			if (camera.x < 0)
				camera.x = 2000 - SCREEN_WIDTH;
		}
		else if (direction[1])
		{
			player1->SetDirection('r');
			if (player1->GetRect()->x < 80)
				player1->SetXvel(1);
			else
			{
				player1->SetXvel(0);
				camera.x++;
				baseclass::coord.x++;
			}

			if (camera.x >= 2000 - SCREEN_WIDTH)
				camera.x = 0;
		}
		else
			player1->SetXvel(0);

		int str, end;
		str = (baseclass::coord.x - (baseclass::coord.x
			% baseclass::TILE_SIZE)) / baseclass::TILE_SIZE;
		end = (baseclass::coord.x + baseclass::coord.w
			+ (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w)
				% baseclass::TILE_SIZE)) / 50;
		if (str < 0)
			str = 0;
		if (end > map[0].size())
			end = map[0].size();

		for (int i = 0; i<map.size(); i++)
			for (int j = str; j < end; j++)
			{
				if (map[i][j] == 0)
					continue;
				SDL_Rect destrect = { j * 50 - baseclass::coord.x, i * 50, 50, 100 };
				for (int g = 0; g < bullets.size(); g++)
				{
					if (collision(bullets[g]->GetRect(), &destrect))
					{
						delete bullets[g];
						bullets.erase(bullets.begin() + g);
					}
				}
			}

		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->GetRect()->x >= SCREEN_WIDTH ||
				bullets[i]->GetRect()->x + bullets[i]->GetRect()->w <= 0)
			{
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
		}

		for (int i = 0; i<bullets.size(); i++)
			for (int j = 0; j < enemies.size(); j++)
			{
				SDL_Rect tmprect = {enemies[i]->GetRect()->x, };
			}

		player1->Move(map);
		for (int i = 0; i < bullets.size(); i++)
			bullets[i]->Move();
		for (int i = 0; i < enemies.size(); i++)
			enemies[i]->Move(map);


			
		SDL_RenderCopy(renderer, background, &camera, NULL);
		ShowMap();
		player1->Show(renderer);
		for (int i = 0; i < bullets.size(); i++)
			bullets[i]->Show(renderer);
		for (int i = 0; i < enemies.size(); i++)
			enemies[i]->Show(renderer);


		SDL_RenderPresent(renderer);

		if (1000 / fps > (SDL_GetTicks() - start))
			SDL_Delay(1000 / fps - (SDL_GetTicks() - start));
	}	
}

void Game::LoadMap(const char* filename)
{
	std::ifstream in(getResourcePath(filename).c_str());
	if (!in.is_open())
	{
		std::cout << "Problem with loading the file" << std::endl;
		return;
	}

	int width, height;
	in >> width;
	in >> height;
	int current;
	for (int i = 0; i < height; i++)
	{
		std::vector<int> vec;
		for (int j = 0; j < width; j++)
		{
			if (in.eof())
			{
				std::cout << "File end reached too soon" << std::endl;
				return;
			}
			in >> current;
			if (current >= 0 && current <= 1)
				vec.push_back(current);
			else
				vec.push_back(0);
		}
		map.push_back(vec);
	}
	in.close();
}