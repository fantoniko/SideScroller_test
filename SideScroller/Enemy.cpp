#include "Enemy.h"

Enemy::Enemy(SDL_Texture* img, int x, int y, int xvel, int yvel)
{
	image = img;
	box.x = x;
	box.y = y;
	box.w = 70;
	box.h = 70;
	this->xvel = xvel;
	this->yvel = yvel;
	ground = false;
	for (int i = 0; i < 2; i++)
	{
		clips[i].x = i * 70;
		clips[i].y = 0;
		clips[i].w = clips[i].h = 70;
	}
	frame = 0.0;
}

void Enemy::Show(SDL_Renderer* renderer)
{
	SDL_Rect tmp = {box.x-coord.x, box.y, 70, 70};
	SDL_RenderCopy(renderer, image, &clips[int(frame+0.5)], &tmp);
}

SDL_Rect* Enemy::GetRect()
{
	return &box;
}

void Enemy::Move(std::vector< std::vector<int> > &map)
{
	/*int start, end;
	start = (baseclass::coord.x - (baseclass::coord.x
		% baseclass::TILE_SIZE)) / baseclass::TILE_SIZE - 2;
	end = (baseclass::coord.x + baseclass::coord.w
		+ (baseclass::TILE_SIZE - (baseclass::coord.x + baseclass::coord.w)
			% baseclass::TILE_SIZE)) / 50 + 2;
	if (start < 0)
		start = 0;
	if (end > map[0].size())
		end = map[0].size();*/

	bool nc = false;

	for (int i = 0; i<map.size(); i++)
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == 0)
				continue;
			SDL_Rect destrect = { j * 50, i * 50, 50, 100 };
			if (collision(&box, &destrect))
			{
				if (destrect.y >= box.y + box.h - 11)
				{
					ground = true;
					yvel = 0;
					nc = 1;
				}

				if ((box.x + box.w >= destrect.x - 5 || box.x <= destrect.x + 5)
					&& box.y + box.h >= destrect.y + 6)
				{
					xvel = -xvel;
				}
			}
		}

	if (!nc)
		yvel = 5;

	box.x += xvel;
	box.y += yvel;

	frame += 0.05;
	if (frame >= 1.4)
		frame = 0.0;
}