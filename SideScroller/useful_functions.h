#pragma once
#include <iostream>
#include <string>
#include "SDL.h"

std::string getResourcePath(const std::string &subDir);

SDL_Texture* SurfToTexture(SDL_Renderer* renderer, const char* filename);