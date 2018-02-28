#include "Bullet.h"

Bullet::Bullet(SDL_Texture* img, int x, int y, int xvel, int yvel)
{
	box.x = x;
	box.y = y;
	image = img;
	box.w = BULLET_WIDTH;
	box.h = BULLET_HEIGHT;
	xVel = xvel;
	yVel = yvel;
}

void Bullet::Move()
{
	box.x += xVel;
	box.y += yVel;
}

void Bullet::Show(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, image, NULL, &box);
}

SDL_Rect* Bullet::GetRect()
{
	return &box;
}