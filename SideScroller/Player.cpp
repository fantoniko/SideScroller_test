#include "Player.h"

Player::Player(SDL_Texture* img)
{
	image = img;
	box = { 0, 0, 50, 100 };
	xvel = 0;
	yvel = 0;
	for (int i = 0; i < 4; i++)
	{
		clips[i].x = i * 50;
		clips[i].y = 0;
		clips[i].w = 50;
		clips[i].h = 100;
	}
	ground = false;
	jump = false;
	direction = 'r';
	frame = 0.0;
}

Player::~Player()
{
	SDL_DestroyTexture(image);
}

SDL_Rect* Player::GetRect()
{
	return &box;
}

int Player::GetXvel()
{
	return xvel;
}

void Player::SetXvel(int vel)
{
	xvel = vel;
}

void Player::Show(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, image, &clips[int(frame+0.5)], &box);
}

void Player::SetMoving(bool b)
{
	moving = b;
}

void Player::SetDirection(char c)
{
	if ((c == 'r' || c == 'l') && direction != c)
	{
		direction = c;
		if (direction == 'r')
			frame = 0.0;
		else
			frame = 1.6;
	}
}

void Player::Move(const std::vector<std::vector<int> >& map)
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

	bool nc = false;

	for (int i = 0; i<map.size(); i++)
		for (int j = start; j < end; j++)
		{
			if (map[i][j] == 0)
				continue;
			SDL_Rect destrect = { j * 50 - baseclass::coord.x, i * 50, 50, 100 };
			if (collision(&box, &destrect))
			{
				nc = 1;
				if (destrect.y >= box.y + box.h - 11)
				{
					ground = true;
					yvel = 0;
				}
				else if (destrect.y + destrect.h <= box.y + 11)
				{
					box.x++;
					yvel = 5;
				}

				if (box.x + box.w >= destrect.x - 5 && box.y + box.h >= destrect.y + 6
					&& box.x + box.w <= destrect.x + 20)
				{
					xvel = 0;
					box.x--;
				}
				else if (box.x <= destrect.x + destrect.w && box.y + box.h >= destrect.y + 6)
				{
					xvel = 0;
					box.x++;
				}
			}
		}

	if (!nc && !jump)
	{
		yvel = 5;
	}

	if (jump && yvel < 5)
		yvel++;
	else
		jump = false;

	box.x += xvel;
	box.y += yvel;

	if (moving)
	{
		frame += 0.05;
		if (direction == 'r' && frame >= 1.4)
			frame = 0.0;
		else if (direction == 'l' && frame >= 3.4)
			frame = 1.5;
	}
}

void Player::Jump()
{
	if (ground && !jump)
	{
		jump = true;
		ground = false;
		yvel = -17;
		box.y -= 5;
	}
}

int Player::GetHealth()
{
	return health;
}

void Player::SetHealth(int h)
{
	health = h;
}